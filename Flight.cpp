#include <fstream>
#include <string>
#include "Flight.h"

void Flight::Serialize(std::string fileName)
{
	std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
	ofs.write((char*)& flightNumber, sizeof(int));
	baggages.Serialize(ofs);
	ofs.close();
}

void Flight::Deserialize(std::string fileName)
{
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	ifs.read((char*)& flightNumber, sizeof(int));
	baggages.Deserialize(ifs);
	ifs.close();
}

std::ostream& operator<< (std::ostream& out, const Flight& flight)
{
	if (&out == &std::cout)
	{
		out << "Номер авиарейса: " << flight.flightNumber << std::endl;
		flight.baggages.PrintToConsole();
	}
	else
	{
		out << flight.flightNumber << std::endl;
		flight.baggages.PrintToFile("test.txt");
	}

	return out;
}

std::istream& operator>> (std::istream& in, Flight& flight)
{
	if (&in == &std::cin)
	{
		std::cout << "Введите номер рейса: ";
		in >> flight.flightNumber;

		flight.baggages.ReadFromConsole();
	}
	else
	{
		char buf[50];
		in >> flight.flightNumber;

		in.ignore();
		in.getline(buf, 50);
		flight.baggages.ReadFromFile();

		in.ignore();
	}

	return in;
}