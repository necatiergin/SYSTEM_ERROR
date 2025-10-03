<!--
// Amaç: Kendi enum class hata sabitlerinizi, std::error_code/std::error_condition ekosistemine entegre etmek.
// bunun için 2 ayrı yol olabilir
// error_code yolu: “Somut hata kaynağı” (OS, kütüphane, modül) temsil edilir. Bir category (türetilmiş std::error_category) gerekir.
// error_condition yolu: “Taşınabilir, soyut sınıflandırma” (permission_denied, not_found vb.) için condition kategorisi ve default_error_condition eşlemesi yapılır.
// Gerekli parçalar:
// Hata sabitleri için bir enum / enum class.
// Tekil (singleton) bir error_category türevi.
// std::make_error_code(MyErr) (veya std::make_error_condition(MyCond)) overload’ı.
// std::is_error_code_enum<MyErr> (veya std::is_error_condition_enum<MyCond>) trait explicit specializaton.
// (opsiyonel) error_category::default_error_condition ile code→condition eşlemesi.

//kendi error enumaration türümüzü oluşturuyoruz:

//başlık dosyamız
// 
// 
enum class MyErr {
    Ok = 0,
    NotInitialized = 1,
    Timeout = 2,
    BadInput = 3,
    IoFailure = 4,
};

// singleton category nesnesine erişim fonksiyon için bildirim yapıyoruz
const std::error_category& my_category() noexcept;

// enum türümüzden std::erroe_code türüne dönüştürecek olan make_error_code overload'u bildirimi
std::error_code make_error_code(MyErr e) noexcept;

// Myerr enum türü error_code amaçlı oluşturulan bir türdür. (SFINAE için gerekli)
namespace std {
    template<> struct is_error_code_enum<MyErr> : true_type {};
}

// implementasyon dosyamız : myerrors.cpp

#include "my_errors.h"

// kendi singleton error_category sınıfımızı implemente ediyoruz:

class my_error_category : public std::error_category {
public:
    const char* name() const noexcept override {
        return "my_category";
    }

    std::string message(int ev) const override {
        // Never throw here, must be noexcept
        switch (static_cast<MyErr>(ev)) {
        case MyErr::Ok:             return "ok";
        case MyErr::NotInitialized: return "not initialized";
        case MyErr::Timeout:        return "timeout";
        case MyErr::BadInput:       return "bad input";
        case MyErr::IoFailure:      return "I/O failure";
        default:                    return "unknown my_category error";
        }
    }


// seçime bağlı error code'larını taşınabilir error_condtion değerlerine map ediyor
    std::error_condition default_error_condition(int ev) const noexcept override 
    {
        // Example: classify a subset into generic conditions
        using std::errc;
        switch (static_cast<MyErr>(ev)) {
        case MyErr::Timeout:   return std::make_error_condition(errc::timed_out);
        case MyErr::BadInput:  return std::make_error_condition(errc::invalid_argument);
        default:
            return std::error_condition(ev, *this); // fall back to same category
        }
    }
};

// make_error_code fabrika fonksiyonu overload'u
std::error_code make_error_code(MyErr e) noexcept 
{
    return { static_cast<int>(e), my_category() };
}

// kullanım örneği
// client.cpp

#include <system_error>
#include "myerrors.h"
#include <iostream>

int main() 
{
    std::error_code ec = MyErr::Timeout; 
    std::cout << ec.message() << " | cat=" << ec.category().name() << '\n';

    if (ec == std::errc::timed_out) {
        std::cout << "timed outn";
    }
}

/*
std::error_code ec = MyErr::Timeout;
burada tam olarak ne oluyor

sadece std::is_error_code_enum<ErrorCodeEnum> == true ise etkin ise 
aşağıdaki template ctor devreye giriyor

template<class ErrorCodeEnum>
error_code(ErrorCodeEnum e) noexcept;      

Bu ctor, ErrorCodeEnum için std::is_error_code_enum özelleştirmesi true olduğu durumda etkin (SFINAE). 
MyErr için:

namespace std {
    template<> struct is_error_code_enum<MyErr> : true_type {};
}

yaptığın için, error_code(MyErr) kurucusu uygun hale gelir ve seçilir.

Not: std::error_code’da “tek argümanlı int alan bir ctor” yoktur; mevcut doğrudan ctor:
error_code(int value, const error_category& cat) noexcept
Dolayısıyla MyErr → int dönüştürüp bunu çağırmak diye bir yol yok.

Bu ctor içinde ne oluyor?
Standart kütüphane bu ctor’u tipik olarak şöyle uygular (öz olarak):

template<class ErrorCodeEnum>
error_code::error_code(ErrorCodeEnum e) noexcept 
{
    *this = make_error_code(e);   // ADL ile doğru make_error_code bulunur
}

Yani kurucu, ADL (argument-dependent lookup) sayesinde senin tanımladığın:

std::error_code make_error_code(MyErr e) noexcept;

3) make_error_code(MyErr) ne döndürüyor?

Senin yazdığın fabrika fonksiyonu tipik olarak şunu yapar:

std::error_code make_error_code(MyErr e) noexcept {
    return { static_cast<int>(e), my_category() };
}

Burada std::error_code’un (int, const error_category&) alan kurucusu çağrılır ve:

value = static_cast<int>(MyErr::Timeout)

category = my_category() (senin std::error_category türevin)

ile bir geçici std::error_code oluşturulur; sonra o geçici, *this’e atanır.

4) Kısa akış özeti

Atama ifadesi std::error_code ec = MyErr::Timeout;

Uygun kurucu: template<class E> error_code(E) noexcept (E = MyErr), çünkü is_error_code_enum<MyErr> == true.

Kurucu içinde make_error_code(MyErr::Timeout) çağrılır (ADL).

make_error_code → error_code(int, category) ile bir error_code döndürür.

Bu değer ec’ye atanır.

5) “Peki is_error_code_enum<MyErr> olmasaydı?”

Şablon kurucu etkin olmazdı (SFINAE).

Geriye uygun başka ctor kalmadığı için (tek argümanlı) kod derlenmezdi.

Bu da özelleştirmenin (trait + make_error_code) neden zorunlu olduğunu gösterir.

Özetle: O tek satır, std::error_code’un ErrorCodeEnum-ilişkili kurucusunu tetikliyor; 
bu kurucu da ADL ile senin make_error_code(MyErr) fonksiyonunu bulup çağırıyor ve en sonunda (int, category) kurucusuna dayanarak error_code nesnesini inşa ediyor.
*/


-->
