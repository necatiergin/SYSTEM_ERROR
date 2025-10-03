#include <system_error>
#include <iostream>

int main() 
{
    std::error_code ec(13, std::system_category()); // örn. EACCES: permission denied

    std::error_condition cond = std::make_error_condition(std::errc::permission_denied);

    if (ec == cond)
        std::cout << "Permission denied.\n";
    else
        std::cout << "Another error.\n";
}
