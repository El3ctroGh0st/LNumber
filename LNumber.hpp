#ifndef CODEWARS_LNUMBER_HPP
#define CODEWARS_LNUMBER_HPP

#include <deque>
#include <string>
#include <iostream>

class LNumber
{
public:
	LNumber() = default;
	LNumber(std::string);
	LNumber(std::deque<short>);
	~LNumber() = default;

	LNumber &operator=(const LNumber &);
	LNumber &operator+=(const LNumber &);
	LNumber &operator-=(const LNumber &);
	LNumber &operator*=(const LNumber &);
	LNumber &operator^=(const int);

	LNumber &operator++();
	LNumber operator++(int);
	LNumber &operator--();
	LNumber operator--(int);

	int operator[](std::size_t n) {return nums.at(n);}

	friend std::ostream &operator<<(std::ostream &, const LNumber &);
	friend std::istream &operator>>(std::istream &, LNumber &);

	friend bool operator>(const LNumber &, const LNumber &);
	friend bool operator<(const LNumber &, const LNumber &);
	friend bool operator==(const LNumber &, const LNumber &);
	friend bool operator>=(const LNumber &, const LNumber &);
	friend bool operator<=(const LNumber &, const LNumber &);

private:
	std::deque<short> nums;
};

LNumber operator+(LNumber, const LNumber &);
LNumber operator+(LNumber, const int &);
LNumber operator-(LNumber, const LNumber &);
LNumber operator-(LNumber, const int &);
LNumber operator*(LNumber, const LNumber &);
//LNumber operator/(LNumber, const LNumber &);

#endif //CODEWARS_LNUMBER_HPP
