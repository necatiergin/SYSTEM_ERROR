#include <iostream>
#include <system_error>
#include <thread>

int main()
{
    try
    {
        std::thread().join(); // attempt to join a non-thread
    }
    catch (const std::system_error& e)
    {
        std::cout << "Caught system_error with code "
            "[" << e.code() << "] meaning "
            "[" << e.what() << "]\n";
    }
}
