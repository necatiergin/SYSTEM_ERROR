#include <system_error>
#include <string>

template <class T>
T value_or_throw(std::expected<T, std::error_code> exp, std::string_view ctx = {}) 
{
    if (exp) 
        return std::move(*exp);
    throw_system_error(exp.error(), ctx);
    // unreachable
}
