// throwing std::system_error with std::error_code

#include <system_error>

int main()
{
	// ...
	std::error_code ec = std::make_error_code(std::errc::permission_denied);
	throw std::system_error(ec, "read_file"); 
	// ...
}
