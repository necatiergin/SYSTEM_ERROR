#include <system_error>
#include <string>

inline void throw_system_error(std::error_code ec, std::string_view ctx = {}) 
{
    if (!ec) 
        return;
    if (ctx.empty()) 
        throw std::system_error(ec);
    
    throw std::system_error(ec, std::string{ ctx });
}
