#include <iostream>
#include "LNumber.hpp"

//Support for negative numbers
//Fix addition of sums
//test


int main()
{
	LNumber num1("5245872934");
	LNumber num2 ("2313427365270532658");

	LNumber num3 = num1 * num2;

	std::cout << num3;

	return 0;
}
