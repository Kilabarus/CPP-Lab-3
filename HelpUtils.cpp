#include <string>
#include <istream>
#include <iostream>
#include <cstring>
#include "HelpUtils.h"

unsigned InputUnsigned(std::string msg, unsigned min, unsigned max)
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

bool IsInRange(int number, int low, int max)
{
	return number >= low && number <= max;
}

std::string InputString(std::string msg)
{
	std::string s;

	if (!msg.empty())
		std::cout << msg << std::endl;
	
	std::cin >> s;

	return s;
}

double InputDouble(std::string msg, double min, double max)
{
	double d;
	
	if (!msg.empty())
		std::cout << msg << std::endl;
	
	std::cin >> d;
	while (d < min || d > max)
	{
		std::cout << "¬ведено неверное значение, повторите ввод: " << std::endl;
		std::cin >> d;
	}
	
	return d;
}