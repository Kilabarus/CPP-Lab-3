#include "DateTime.h"
#include "Baggage.h"
#include "MyVector.h"

#pragma once

class Flight
{
public:
	int flightNumber;
	std::string departurePoint, arrivalPoint;
	DateTime flightDateTime;
	MyVector<Baggage> baggages;

	void Serialize(std::string fileName);
	void Deserialize(std::string fileName);

	friend std::ostream& operator<< (std::ostream& out, const Flight& flight);
	friend std::istream& operator>> (std::istream& in, Flight& flight);
};
