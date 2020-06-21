#include "DateAndTime.h"

std::ostream& operator<< (std::ostream& out, const DateAndTime& dateAndTime)
{
	out << (dateAndTime.day < 10 ? "0" : "") << std::to_string(dateAndTime.day) << "." << (dateAndTime.month < 10 ? "0" : "") << std::to_string(dateAndTime.month) << "." << std::to_string(dateAndTime.year) << " "
		<< (dateAndTime.hour < 10 ? "0" : "") << std::to_string(dateAndTime.hour) << ":" << (dateAndTime.minute < 10 ? "0" : "") << std::to_string(dateAndTime.minute);

	return out;
}

std::istream& operator>> (std::istream& in, DateAndTime& dateAndTime)
{
	std::cout << "¬ведите год: ";
	in >> dateAndTime.year;
	std::cout << std::endl << "¬ведите мес€ц: ";
	in >> dateAndTime.month;
	std::cout << std::endl << "¬ведите день: ";
	in >> dateAndTime.day;
	std::cout << std::endl << "¬ведите час: ";
	in >> dateAndTime.hour;
	std::cout << std::endl << "¬ведите минуты: ";
	in >> dateAndTime.minute;

	return in;
}

bool operator== (const DateAndTime& left, const DateAndTime& right)
{
	return (left.year == right.year &&
		left.month == right.month &&
		left.day == right.day &&
		left.hour == right.hour &&
		left.minute == right.minute);
}

bool operator!= (const DateAndTime& left, const DateAndTime& right)
{
	return !(left == right);
}

bool operator< (const DateAndTime& left, const DateAndTime& right)
{
	if (left.year < right.year)
		return true;
	else if (left.year > right.year)
		return false;
	
	int secondsl, secondsr;
	secondsl = left.month * 2592000 + left.day * 86400 + left.hour * 3600 + left.minute * 60;
	secondsr = right.month * 2592000 + right.day * 86400 + right.hour * 3600 + right.minute * 60;

	return secondsl < secondsr;
}

bool operator<= (const DateAndTime& left, const DateAndTime& right)
{
	if (left.year < right.year)
		return true;
	else if (left.year > right.year)
		return false;

	int secondsl, secondsr;
	secondsl = left.month * 2592000 + left.day * 86400 + left.hour * 3600 + left.minute * 60;
	secondsr = right.month * 2592000 + right.day * 86400 + right.hour * 3600 + right.minute * 60;

	return secondsl <= secondsr;
}

bool operator> (const DateAndTime& left, const DateAndTime& right)
{
	return !(left <= right);
}

bool operator>= (const DateAndTime& left, const DateAndTime& right)
{
	return !(left < right);
}