#include <system_error>
#include <string>
#include <expected>
#include <utility>

template <class F, class... Args>
auto to_expected(F&& f, Args&&... args)
-> std::expected<decltype(std::forward<F>(f)(std::forward<Args>(args)...)), std::error_code>
{
    try {
        return std::forward<F>(f)(std::forward<Args>(args)...); // throwing call
    }
    catch (const std::system_error& e) {
        return std::unexpected(e.code());
    }
}
