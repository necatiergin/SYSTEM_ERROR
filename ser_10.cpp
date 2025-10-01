// errmo to std::error_code conversion

#include <system_error>
#include <cerrno>
#include <iostream>

int main()
{
    //...
    int e = errno; 
    std::error_code ec(e, std::generic_category());   

    if (ec) { 
        std::cerr << "OS error: " << ec.message() << '\n';
    }
}
