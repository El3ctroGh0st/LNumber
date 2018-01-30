#include <iostream>
#include "LNumber.hpp"

//Support for negative numbers
//Fix addition of sums

LNumber operator+(LNumber, const LNumber &);

int main()
{
	//Test
	LNumber num1("230");
	LNumber num2 ("23");

	std::cout << (num1 == num2);

	return 0;
}
