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
