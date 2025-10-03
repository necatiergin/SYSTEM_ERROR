//std::errc enumaratör türünden error_condition türüne dönüşüm

// std::error_condition make_error_condition(std::errc e) noexcept;

#include <iostream>
#include <string>
#include <system_error>

int main()
{
    auto err = std::make_error_condition(std::errc::invalid_argument);
    std::cout << err.message() << '\n';
}
