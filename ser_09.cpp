#include <system_error>

int main()
{
	//...
	throw std::system_error(13, std::generic_category(), "open"); // 13 ≈ EACCES
}
