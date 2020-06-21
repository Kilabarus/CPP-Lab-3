#include <string>
#include <istream>
#include <iostream>
#include <cstring>
#include "DateAndTime.h"

unsigned InputUnsigned(std::string msg, unsigned min = 0, unsigned max = UINT_MAX)
{
	unsigned u;
	if (!msg.empty())
		std::cout << msg << std::endl;
	std::cin >> u;
	while (u < min || u > max)
	{
		std::cout << "¬ведено неверное значение, повторите ввод: " << std::endl;
		std::cin >> u;
	}
	return u;
}

std::string InputString(std::string msg)
{
	std::string s;
	if (!msg.empty())
		std::cout << msg << std::endl;
	std::cin >> s;
	return s;
}

std::string CharArrayToString(char* a)
{
	std::string s = "";
	for (int i = 0; i < std::strlen(a) && a[i] != '\0'; ++i) 
	{
		s += a[i];
	}
	return s;
}
