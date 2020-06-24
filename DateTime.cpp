#include "DateTime.h"
#include "HelpUtils.h"

DateTime::DateTime()
{
	day = 1; month = 1; year = 1900;
	hour = 0; minute = 0;
}

DateTime::DateTime(int d, int mo, int y, int h, int mi)
{	
	if (IsInRange(y, 1900, 2030) && IsInRange(mo, 1, 12) && IsInRange(d, 1, daysInMonths[mo]) && IsInRange(mi, 0, 59) && IsInRange(h, 0, 23))
	{
		day = d; month = mo; year = y;
		hour = h; minute = mi;
	}
	else
	{
		day = 1; month = 1; year = 1900;
		hour = 0; minute = 0;
	}
}

std::ostream& operator<< (std::ostream& out, const DateTime& dateTime)
{
	if (&out == &std::cout)
	{
		out << (dateTime.day < 10 ? "0" : "") << std::to_string(dateTime.day) << "."
			<< (dateTime.month < 10 ? "0" : "") << std::to_string(dateTime.month) << "."
			<< std::to_string(dateTime.year) << " "
			<< (dateTime.hour < 10 ? "0" : "") << std::to_string(dateTime.hour) << ":"
			<< (dateTime.minute < 10 ? "0" : "") << std::to_string(dateTime.minute);
	}
	else
	{
		out << dateTime.day << " " << dateTime.month << " " << dateTime.year << " "
			<< dateTime.hour << " " << dateTime.minute << std::endl;
	}
	return out;
}

std::istream& operator>> (std::istream& in, DateTime& dateTime)
{
	if (&in == &std::cin)
	{
		dateTime.year = InputUnsigned("¬ведите год: ", 1900, 2030);
		dateTime.month = InputUnsigned("¬ведите мес€ц: ", 1, 12);
		dateTime.day = InputUnsigned("¬ведите день: ", 1, daysInMonths[dateTime.month]);
		dateTime.hour = InputUnsigned("¬ведите час: ", 0, 23);
		dateTime.minute = InputUnsigned("¬ведите минуты: ", 0, 59);
	}
	else
	{
		in >> dateTime.day;
		in >> dateTime.month;
		in >> dateTime.year;
		in >> dateTime.hour;
		in >> dateTime.minute;
	}

	return in;
}

bool operator== (const DateTime& left, const DateTime& right)
{
	return (left.year == right.year &&
		left.month == right.month &&
		left.day == right.day &&
		left.hour == right.hour &&
		left.minute == right.minute);
}

bool operator!= (const DateTime& left, const DateTime& right)
{
	return !(left == right);
}

bool operator< (const DateTime& left, const DateTime& right)
{
	if (left.year < right.year)
		return true;
	else if (left.year > right.year)
		return false;

	return left.month * 2592000 + left.day * 86400 + left.hour * 3600 + left.minute * 60 
		< right.month * 2592000 + right.day * 86400 + right.hour * 3600 + right.minute * 60;
}

bool operator<= (const DateTime& left, const DateTime& right)
{
	if (left.year < right.year)
		return true;
	else if (left.year > right.year)
		return false;

	return left.month * 2592000 + left.day * 86400 + left.hour * 3600 + left.minute * 60
		<= right.month * 2592000 + right.day * 86400 + right.hour * 3600 + right.minute * 60;
}

bool operator> (const DateTime& left, const DateTime& right)
{
	return !(left <= right);
}

bool operator>= (const DateTime& left, const DateTime& right)
{
	return !(left < right);
}

