#include <filesystem>
#include <system_error>
#include <iostream>

void fs_demo()
{
    namespace fs = std::filesystem;

    std::error_code ec;
    fs::create_directory("data", ec);     // noexcept overload
    if (ec) {
        std::cerr << "create_directory: " << ec.message() << "\n";
        if (ec == std::errc::file_exists) {
            std::cerr << "Directory already exists\n";
        }
    }

    auto s = fs::status("missing.txt", ec);
    if (ec) {
        if (ec == std::errc::no_such_file_or_directory) {
            std::cerr << "File not found\n";
        }
    }
}
