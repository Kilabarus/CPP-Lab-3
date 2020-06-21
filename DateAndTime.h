#include <string>
#include <iostream>
#pragma once

class DateAndTime
{
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;

	DateAndTime()
	{
		year = 1900;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
	}

	DateAndTime(int y, int mo, int d, int h, int mi)
	{
		year = y;
		month = mo;
		day = d;
		hour = h;
		minute = mi;
	}

	DateAndTime& operator= (const DateAndTime& dateAndTime)
	{
		if (this == &dateAndTime)
			return *this;

		year = dateAndTime.year;
		month = dateAndTime.month;
		day = dateAndTime.day;
		hour = dateAndTime.hour;
		minute = dateAndTime.minute;

		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, const DateAndTime& dateAndTime);
	friend std::istream& operator>> (std::istream& in, DateAndTime& dateAndTime);

	friend bool operator== (const DateAndTime& left, const DateAndTime& right);
	friend bool operator!= (const DateAndTime& left, const DateAndTime& right);

	friend bool operator< (const DateAndTime& left, const DateAndTime& right);
	friend bool operator<= (const DateAndTime& left, const DateAndTime& right);

	friend bool operator> (const DateAndTime& left, const DateAndTime& right);
	friend bool operator>= (const DateAndTime& left, const DateAndTime& right);
};

