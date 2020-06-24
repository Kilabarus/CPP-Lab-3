#include <fstream>
#include <string>
#include "Flight.h"

void Flight::Serialize(std::string fileName)
{
	std::ofstream ofs(fileName);
	ofs << this;
	ofs.close();
}

std::ostream& operator<< (std::ostream& out, const Flight& flight)
{
	if (&out == &std::cout)
	{
		out << "����� ���������: " << flight.flightNumber << std::endl
			<< "�������: " << flight.departurePoint << " - " << flight.arrivalPoint << std::endl
			<< "����� ������: " << flight.flightDateTime << std::endl
			<< "���������� ������� �� ���������: " << flight.baggages.GetSize() << std::endl
			<< "������ �������: " << std::endl << std::endl;
		flight.baggages.PrintToConsole();
		out << "-----------------------------------------------" << std::endl;
	}
	else
	{
		out << flight.flightNumber << " "
			<< flight.baggages.GetSize() << std::endl
			<< flight.departurePoint << std::endl
			<< flight.arrivalPoint << std::endl;
		DateTime defaultDateTime;
		if (flight.flightDateTime != defaultDateTime)
			out << flight.flightDateTime << std::endl;
		flight.baggages.PrintToFile(out);
	}

	return out;
}

void Flight::Deserialize(std::string fileName)
{
	std::ifstream ifs(fileName);
	ifs >> *this;
	ifs.close();
}

std::istream& operator>> (std::istream& in, Flight& flight)
{
	if (&in == &std::cin)
	{
		flight.flightNumber = InputUnsigned("������� ����� ���������: ", 0, 9999);
		flight.departurePoint = InputString("������� ����� ������: ");
		flight.arrivalPoint = InputString("������� ����� ����������: ");
		in >> flight.flightDateTime;
		flight.baggages.ReadFromConsole();
	}
	else
	{
		int numOfBaggages;

		in >> flight.flightNumber;
		in >> numOfBaggages;

		if (numOfBaggages)
		{
			char buf[50];
			in.ignore();
			in.getline(buf, 50);
			flight.departurePoint = std::string(buf);

			in.getline(buf, 50);
			flight.arrivalPoint = std::string(buf);

			in >> flight.flightDateTime;
			
			flight.baggages.ReadFromFile(in, numOfBaggages);
		}		
	}

	return in;
}