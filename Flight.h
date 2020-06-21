#include "Baggage.h"
#include "VectorOperations.h"


#pragma once

class Flight
{
public:
	int flightNumber;
	VectorOperations<Baggage> baggages;

	void Serialize(std::string fileName);
	void Deserialize(std::string fileName);
};

