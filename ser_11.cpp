#include <system_error>
#include <iostream>

int main()
{
    try {
        // ...
    }
    catch (const std::system_error& e) {
        std::cerr << "system_error: " << e.what() << '\n';
        const auto& ec = e.code();
        std::cerr << "code: " << ec.value()
            << ", category: " << ec.category().name()
            << ", message: " << ec.message() << '\n';

        if (ec == std::errc::permission_denied) {
            // portable comparison
        }
    }
    catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << '\n';
    }
}
