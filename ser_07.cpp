// custom error category implementation

#include <system_error>
#include <string>

enum class file_errc {
    ok = 0, 
    open_failed = 1, 
    read_failed = 2 };

// 2) Kategori sınıfınız (singleton)
class file_category : public std::error_category {
public:
    const char* name() const noexcept override 
    {
        return "file";
    }
    
    std::string message(int ev) const override 
    {
        switch (static_cast<file_errc>(ev)) {
            case file_errc::ok:          return "ok";
            case file_errc::open_failed: return "open failed";
            case file_errc::read_failed: return "read failed";
        }
        return "unknown file error";
    }
    
    std::error_condition default_error_condition(int ev) const noexcept override 
    {
        switch (static_cast<file_errc>(ev)) {
        case file_errc::open_failed: return std::make_error_condition(std::errc::no_such_file_or_directory);
        case file_errc::read_failed: return std::make_error_condition(std::errc::io_error);
        default:                     return std::error_condition(ev, *this);
        }
    }
};

inline const std::error_category& file_category_v() 
{
    static file_category inst;          
    return inst;
}


inline std::error_code make_error_code(file_errc e) 
{
    return { static_cast<int>(e), file_category_v() };
}

namespace std {
    template<> struct is_error_code_enum<file_errc> : true_type {};
}
