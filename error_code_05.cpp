// typical error_code usage
// file_system library

#include <filesystem>
 
int main()
{
	std::filesystem::path p = "neco.txt";
	std::error_code ec;
	auto sz = std::filesystem::file_size(p, ec); // noexcept
	if (ec) { 
		// ...
	}

}
