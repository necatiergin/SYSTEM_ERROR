#include <string>
#include <system_error>

// Throwing API:
std::string read_file(const std::string& path); // throws std::system_error

// No-throw API:
std::string read_file(const std::string& path, std::error_code& ec) noexcept;
