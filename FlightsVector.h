#include "MyVector.h"
#include "Flight.h"
#include "Baggage.h"

#pragma once

class FlightsVector
{
public:
	MyVector<Flight> flights;

	void Serialize(std::string fileName);
	void Deserialize(std::string fileName);
};