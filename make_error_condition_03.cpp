#include <system_error>
#include <iostream>

int main() 
{
    std::error_code ec(13, std::system_category());

    // Dolaylı olarak make_error_condition çağrılır
    if (ec == std::errc::permission_denied) {
        std::cout << "Permission denied (short syntax).\n";
    }
}
