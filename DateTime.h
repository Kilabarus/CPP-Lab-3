#include <string>
#include <iostream>
#pragma once

const int daysInMonths[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class DateTime
{
public:
	int day, month, year, minute, hour;	

	DateTime();

	DateTime(int d, int mo, int y, int h, int mi);	

	DateTime& operator= (const DateTime& dateTime)
	{
		if (this == &dateTime)
			return *this;

		day = dateTime.day; month = dateTime.month; year = dateTime.year;
		hour = dateTime.hour; minute = dateTime.minute;

		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, const DateTime& dateAndTime);
	friend std::istream& operator>> (std::istream& in, DateTime& dateAndTime);

	friend bool operator== (const DateTime& left, const DateTime& right);
	friend bool operator!= (const DateTime& left, const DateTime& right);

	friend bool operator< (const DateTime& left, const DateTime& right);
	friend bool operator<= (const DateTime& left, const DateTime& right);

	friend bool operator> (const DateTime& left, const DateTime& right);
	friend bool operator>= (const DateTime& left, const DateTime& right);
};


