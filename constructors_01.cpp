#include <system_error>
#include <iostream>
#include <type_traits>

int main()
{
	using namespace std;

	error_code ecode; //default ctor
	cout << "value : " << ecode.value() << '\n';
	cout << "category name : " << ecode.category().name() << '\n';

	error_condition econ; //default ctor
	cout << "value : " << econ.value() << '\n';
	cout << "category name : " << econ.category().name() << '\n';
}
