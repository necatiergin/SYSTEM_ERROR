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

// 
enum class MyErr {
    Ok = 0,
    NotInitialized = 1,
    Timeout = 2,
    BadInput = 3,
    IoFailure = 4,
};
