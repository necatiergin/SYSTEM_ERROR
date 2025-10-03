#include <system_error>
#include <iostream>

int main() 
{
    std::error_code ec = std::make_error_code(std::errc::permission_denied);
    std::error_condition cond = std::make_error_condition(std::errc::permission_denied);

    std::cout << "Error code: " << ec.value() << " - " << ec.message() << '\n';
    std::cout << "Error condition: " << cond.value() << " - " << cond.message() << '\n';

    if (ec == cond)
        std::cout << "Error code matches condition.\n";
}
