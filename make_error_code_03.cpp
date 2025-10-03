//make_* fonksiyonlarının çalışabilmesi için std::errc enum türü için aşağıdaki trait'lerin özelleştirilmiş olması gerekir:

namespace std {
    template <>
    struct is_error_code_enum<std::errc> : true_type {};

    template <>
    struct is_error_condition_enum<std::errc> : true_type {};
}
