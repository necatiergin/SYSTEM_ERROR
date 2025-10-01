#include <iostream>
#include <string>
#include <system_error>

int main()
{
    auto err = std::make_error_condition(std::errc::invalid_argument);
    std::cout << err.message() << '\n';
}
