// Amaç: Kendi enum class hata sabitlerinizi, std::error_code/std::error_condition ekosistemine entegre etmek.
// bunun için 2 ayrı yol olabilir
// error_code yolu: “Somut hata kaynağı” (OS, kütüphane, modül) temsil edilir. Bir category (türetilmiş std::error_category) gerekir.
// error_condition yolu: “Taşınabilir, soyut sınıflandırma” (permission_denied, not_found vb.) için condition kategorisi ve default_error_condition eşlemesi yapılır.
