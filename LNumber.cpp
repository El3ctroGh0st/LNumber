#include <algorithm>
#include <iostream>
#include <vector>
#include "LNumber.hpp"

LNumber::LNumber(std::string str)
{
	while (str.size() > 0 && str.at(0) == '0')
		str = str.substr(1, str.size() - 1);

	if (!(std::all_of(str.begin(), str.end(), ::isdigit)) || str.empty())
		nums.push_back(0);
	else {

		for (int i = 0; i < str.size(); ++i) {
			char a = str.at(i);
			short ia = a - '0';
			nums.push_back(ia);
		}
	}
}
LNumber::LNumber(std::deque<short> deq)
{
	this->nums = deq;
}
LNumber &LNumber::operator=(const LNumber &lnum)
{
	this->nums = lnum.nums;
	return *this;
}
LNumber &LNumber::operator+=(const LNumber &lnum)
{
	std::deque<short> resVector;
	const std::deque<short> *bigVec = nullptr;
	short remainder = 0;

	int vec1Size = this->nums.size();
	int vec2Size = lnum.nums.size();

	int minSize = vec1Size < vec2Size ? vec1Size : vec2Size;
	int maxSize = vec1Size > vec2Size ? vec1Size : vec2Size;

	if (vec1Size != vec2Size)
		bigVec = (vec1Size > vec2Size) ? &(this->nums) : &(lnum.nums);

	for (int i = 1; i <= maxSize; ++i) {
		short sum = 0;
		if (i <= minSize)
			sum = this->nums.at(vec1Size - i) + lnum.nums.at(vec2Size - i) + remainder;
		else
			sum = bigVec->at(maxSize - i) + remainder;

		if (sum >= 10) {
			resVector.push_front(sum % 10);
			remainder = sum / 10;
		}
		else {
			resVector.push_front(sum);
			remainder = 0;
		}
	}

	//First digit
	if (remainder != 0)
		resVector.push_front(remainder);

	this->nums = resVector;
	return *this;
}
LNumber &LNumber::operator-=(const LNumber &lnum)
{
	std::deque<short> resVector;
	LNumber leftNum = lnum;

	//No negative numbers as result
	if(leftNum > *this)
		return *this;

	while(this->nums.size() > leftNum.nums.size())
		leftNum.nums.push_front(0);

	size_t vecSize = this->nums.size();

	for(int i = 0; i < vecSize; ++i)
	{
		short minuend = this->nums.at(vecSize - i - 1);
		short subtrahend = leftNum.nums.at(vecSize - i - 1);
		if(this->nums.at(vecSize - i - 1) < leftNum.nums.at(vecSize - i - 1))
		{
			//Previous element contains zero
			int prevVecPos = vecSize - i - 2;
			if(this->nums.at(prevVecPos) == 0)
			{
				for(; prevVecPos >= 0 && this->nums.at(prevVecPos) != 0; --prevVecPos)
				{
					std::cout << prevVecPos;
					this->nums.at(prevVecPos) = 9;
				}
			}

			//Fix subtraction with zeros
			minuend += 10;
			--this->nums.at(prevVecPos);
		}
		std::cout << minuend - subtrahend << " ";
		resVector.push_front(minuend - subtrahend);
	}

	while(resVector.at(0) == 0)
		 resVector.erase(resVector.begin());

	*this = resVector;
	return *this;
}
LNumber &LNumber::operator*=(const LNumber &lnum)
{
	std::vector<std::deque<short>> sumsVector;
	LNumber resVector;
	short remainder = 0;

	int vec1Size = this->nums.size();
	int vec2Size = lnum.nums.size();

	for (int i = 0; i < vec2Size; ++i) {
		std::deque<short> currSum;
		for (int j = vec1Size - 1; j >= 0; --j) {
			short sum = this->nums.at(j) * lnum.nums.at(i) + remainder;
			if (sum >= 10) {
				currSum.push_front(sum % 10);
				remainder = sum / 10;
			}
			else {
				currSum.push_front(sum);
				remainder = 0;
			}
		}
		//First digit
		if (remainder != 0) {
			currSum.push_front(remainder);
			remainder = 0;
		}

		for(int j = i; j < vec2Size - 1; ++j)
		{
			currSum.push_back(0);
		}
		sumsVector.push_back(currSum);
	}

	//Print all elements
	for(int i = 0; i < sumsVector.size(); ++i)
	{
		resVector += sumsVector.at(i);
	}

	this->nums = resVector.nums;
	return *this;
}
LNumber &LNumber::operator^=(const int exponent)
{
	LNumber origVal = *this;
	for(int i = 2; i <= exponent; ++i)
		*this *= origVal;
	return *this;
}
LNumber &LNumber::operator++()
{
	LNumber num("1");
	*this += num;
	return *this;
}
LNumber LNumber::operator++(int)
{
	LNumber num = *this;
	++*this;
	return num;
}
LNumber &LNumber::operator--()
{
	LNumber num("1");
	*this -= num;
	return *this;
}
LNumber LNumber::operator--(int)
{
	LNumber num = *this;
	--*this;
	return num;
}
LNumber operator+(LNumber lhs, const LNumber &rhs)
{
	lhs += rhs;
	return lhs;
}
LNumber operator+(LNumber lhs, const int &rhs)
{
	LNumber num(std::to_string(rhs));
	lhs += num;
	return lhs;
}
LNumber operator*(LNumber lhs, const LNumber &rhs)
{
	lhs *= rhs;
	return lhs;
}
LNumber operator-(LNumber lhs, const LNumber &rhs)
{
	lhs -= rhs;
	return lhs;
}
LNumber operator-(LNumber lhs, const int &rhs)
{
	LNumber num(std::to_string(rhs));
	lhs -= num;
	return lhs;
}
std::ostream &operator<<(std::ostream &os, const LNumber &lnum)
{
	std::string num;
	for (size_t i = 0; i < lnum.nums.size(); ++i)
		num += std::to_string(lnum.nums.at(i));
	os << num;
	return os;
}
std::istream &operator>>(std::istream &is, LNumber &lnum)
{
	std::string num;
	is >> num;
	lnum = LNumber(num);
	return is;
}
bool operator>(const LNumber &num1, const LNumber &num2)
{
	if (num1.nums.size() > num2.nums.size())
		return true;
	if (num1.nums.size() < num2.nums.size())
		return false;

	for (int i = 0; i < num1.nums.size(); ++i) {
		if (num1.nums.at(i) > num2.nums.at(i))
			return true;
	}
	return false;
}
bool operator<(const LNumber &num1, const LNumber &num2)
{
	if (num1.nums.size() < num2.nums.size())
		return true;
	if (num1.nums.size() > num2.nums.size())
		return false;

	for (int i = 0; i < num1.nums.size(); ++i) {
		if (num1.nums.at(i) < num2.nums.at(i))
			return true;
	}

	return false;
}
bool operator<=(const LNumber &num1, const LNumber &num2)
{
	return !(num1 > num2);
}
bool operator>=(const LNumber &num1, const LNumber &num2)
{
	return !(num1 < num2);
}
bool operator==(const LNumber &num1, const LNumber &num2)
{
	bool equal = true;
	if (num1.nums.size() == num2.nums.size()) {
		for (int i = 0; i < num1.nums.size(); ++i) {
			if (num1.nums.at(i) != num2.nums.at(i))
				equal = false;
		}
	}
	else {
		equal = false;
	}
	return equal;
}

