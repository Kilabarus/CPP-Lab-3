#include "FlightsVector.h"

#pragma once

void FlightsVector::Serialize(std::string fileName)
{
	std::ofstream ofs(fileName);
	
	int numOfFlights = flights.GetSize();
	ofs << numOfFlights << std::endl << std::endl;

	for (int i = 0; i < numOfFlights; ++i)
	{
		ofs << flights[i];
	}

	ofs.close();
}

void FlightsVector::Deserialize(std::string fileName)
{
	std::ifstream ifs(fileName);

	int numOfFlights;
	ifs >> numOfFlights;

	for (int i = 0; i < numOfFlights; ++i)
	{
		Flight flight;
		ifs >> flight;
		flights.AddElement(flight);
	}

	ifs.close();
}