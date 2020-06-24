#include <string>
#include "DateTime.h"

#pragma once

static constexpr double WEIGHT_EPSILON = 0.001;

class Baggage
{
public:
	int baggageNumber;
	std::string passangerLastName;
	int placeForBaggage;
	double baggageWeight;

	Baggage()
	{
		baggageNumber = -1;		
		passangerLastName = "";
		placeForBaggage = -1;
		baggageWeight = -1.;
	};

	Baggage(int bNumber, std::string pLastName, int pForBaggage, double baggWeight);

	Baggage& operator= (const Baggage& baggage)
	{
		if (this == &baggage)
			return *this;

		baggageNumber = baggage.baggageNumber;
		passangerLastName = baggage.passangerLastName;
		placeForBaggage = baggage.placeForBaggage;
		baggageWeight = baggage.baggageWeight;

		return *this;
	}

	friend bool operator== (const Baggage& left, const Baggage& right);
	friend bool operator!= (const Baggage& left, const Baggage& right);

	friend std::ostream& operator<< (std::ostream& out, const Baggage& baggage);
	friend std::istream& operator>> (std::istream& in, Baggage& baggage);
};

