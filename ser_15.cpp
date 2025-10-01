// usage with std::expected

#include <expected>
#include <system_error>
#include <string>
#include <fstream>

std::expected<std::string, std::error_code>
read_text_expected(const std::string& path) noexcept
{
    std::ifstream ifs(path);
    if (!ifs) 
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));

    std::string data((std::istreambuf_iterator<char>(ifs)), {});
    if (!ifs.eof() && ifs.fail())
        return std::unexpected(std::make_error_code(std::errc::io_error));

    return data;
}

void use_expected()
{
    auto res = read_text_expected("data.txt");
    if (!res) {
        // res.error() bir std::error_code
        // log + fallback
        return;
    }
    // success: *res ya da res.value()
}
