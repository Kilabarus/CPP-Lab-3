#include <string>
#include "DateAndTime.h"

#pragma once

const double WEIGHT_EPSILON = 0.001;

class Baggage
{
public:
	//int flightNumber;
	DateAndTime flightDateAndTime;

	std::string destination;
	std::string passangerLastName;

	int placeForBaggage;
	double baggageWeight;

	Baggage()
	{
		//flightNumber = -1;
		destination = "";
		passangerLastName = "";
		placeForBaggage = -1;
		baggageWeight = -1.;
	};

	Baggage(/*int flNum, */DateAndTime flDateAndTime, std::string dest, std::string passLastName, int plForBaggage, double baggWeight)
	{
		//flightNumber = flNum;
		flightDateAndTime = flDateAndTime;
		destination = dest;
		passangerLastName = passLastName;
		placeForBaggage = plForBaggage;
		baggageWeight = baggWeight;
	}

	Baggage& operator= (const Baggage& baggage)
	{
		if (this == &baggage)
			return *this;

		//flightNumber = baggage.flightNumber;
		flightDateAndTime = baggage.flightDateAndTime;
		destination = baggage.destination;
		passangerLastName = baggage.passangerLastName;
		placeForBaggage = baggage.placeForBaggage;
		baggageWeight = baggage.baggageWeight;

		return *this;
	}

	void Serialize(std::ofstream& ofs);
	void Deserialize(std::ifstream& ifs);

	friend bool operator== (const Baggage& left, const Baggage& right);
	friend bool operator!= (const Baggage& left, const Baggage& right);

	friend std::ostream& operator<< (std::ostream& out, const Baggage& baggage);
	friend std::istream& operator>> (std::istream& in, Baggage& baggage);
};

