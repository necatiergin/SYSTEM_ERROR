#include <system_error>
#include <iostream>

int main() 
{

    FILE* f = std::fopen("nonexistent.txt", "r");
    if (!f) {
        std::error_code ec(errno, std::generic_category()); /
        std::cout << "File open failed: " << ec.message() << '\n';

        if (ec == std::errc::no_such_file_or_directory)
            std::cout << "No such file\n";
    }
 }
