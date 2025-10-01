#include <system_error>
#include <cerrno>
#include <iostream>

int main()
{
    std::error_code ec = std::make_error_code(std::errc::permission_denied); // generic_category
    std::cout << ec.value() << " " << ec.category().name()
        << " -> " << ec.message() << '\n';
}
