#include <string>
#include <fstream>
#include "Baggage.h"
#include "SupportiveFunctions.h"

bool operator== (const Baggage& left, const Baggage& right)
{
	return (left.passangerLastName == right.passangerLastName &&
			//left.flightNumber == right.flightNumber &&
			left.destination == right.destination &&
			left.flightDateAndTime == right.flightDateAndTime &&
			left.placeForBaggage == right.placeForBaggage &&
			abs(left.baggageWeight - right.baggageWeight) < WEIGHT_EPSILON);
}

bool operator!= (const Baggage& left, const Baggage& right)
{
	return !(left == right);
}

void Baggage::Serialize(std::ofstream& ofs)
{
	int stringSize = passangerLastName.size();
	ofs.write((char*)& stringSize, sizeof(int));
	for (int i = 0; i < stringSize; ++i)
	{
		char c = passangerLastName[i];
		ofs.write(&c, sizeof(char));
	}

	int stringSize = destination.size();
	ofs.write((char*)& stringSize, sizeof(int));
	for (int i = 0; i < stringSize; ++i)
	{
		char c = destination[i];
		ofs.write(&c, sizeof(char));
	}
	
	ofs.write((char*)& flightDateAndTime.day, sizeof(int));
	ofs.write((char*)& flightDateAndTime.month, sizeof(int));
	ofs.write((char*)& flightDateAndTime.year, sizeof(int));
	ofs.write((char*)& flightDateAndTime.hour, sizeof(int));
	ofs.write((char*)& flightDateAndTime.minute, sizeof(int));
	ofs.write((char*)& placeForBaggage, sizeof(int));
	ofs.write((char*)& baggageWeight, sizeof(double));
}

void Baggage::Deserialize(std::ifstream& ifs) 
{
	int stringSize;
	ifs.read((char*)& stringSize, sizeof(int));
	std::string s;
	for (int i = 0; i < stringSize; ++i) 
	{
		char c;
		ifs.read(&c, sizeof(char));
		s += c;
	}
	passangerLastName = s;
	
	s = "";
	for (int i = 0; i < stringSize; ++i)
	{
		char c;
		ifs.read(&c, sizeof(char));
		s += c;
	}
	destination = s;

	ifs.read((char*)& flightDateAndTime.day, sizeof(int));
	ifs.read((char*)& flightDateAndTime.month, sizeof(int));
	ifs.read((char*)& flightDateAndTime.year, sizeof(int));
	ifs.read((char*)& flightDateAndTime.hour, sizeof(int));
	ifs.read((char*)& flightDateAndTime.minute, sizeof(int));
	ifs.read((char*)& placeForBaggage, sizeof(int));
	ifs.read((char*)& baggageWeight, sizeof(double));
}

std::ostream& operator<< (std::ostream& out, const Baggage& baggage)
{
	if (&out == &std::cout)
	{
		out << "������� ���������: " << baggage.passangerLastName << std::endl
			//<< "����� �����: " << baggage.flightNumber << std::endl
			<< "����� ����������: " << baggage.destination << std::endl
			<< "���� � ����� ������: " << baggage.flightDateAndTime << std::endl
			<< "���������� ���� ������: " << baggage.placeForBaggage << std::endl
			<< "��� ������: " << baggage.baggageWeight << std::endl;
	}
	else
	{
		out //<< baggage.flightNumber << std::endl
			<< baggage.passangerLastName << std::endl
			<< baggage.destination << std::endl
			<< baggage.flightDateAndTime.day << " " << baggage.flightDateAndTime.month << " " << baggage.flightDateAndTime.year << " " << baggage.flightDateAndTime.hour << " " << baggage.flightDateAndTime.minute << std::endl
			<< baggage.placeForBaggage << std::endl
			<< baggage.baggageWeight;
	}

	return out;
}

std::istream& operator>> (std::istream& in, Baggage& baggage)
{
	if (&in == &std::cin)
	{
		std::cout << "������� ������� ��������� ������: ";
		in >> baggage.passangerLastName;
		std::cout << "������� ����� �����: ";
		//in >> baggage.flightNumber;
		//std::cout << "������� ����� ����������: ";
		in >> baggage.destination;
		std::cout << "������� ���: ";
		in >> baggage.flightDateAndTime.year;
		std::cout << "������� ����� ������: ";
		in >> baggage.flightDateAndTime.month;
		std::cout << "������� ����: ";
		in >> baggage.flightDateAndTime.day;
		std::cout << "������� ���: ";
		in >> baggage.flightDateAndTime.hour;
		std::cout << "������� ������: ";
		in >> baggage.flightDateAndTime.minute;
		std::cout << "������� ���������� ���� ������: ";
		in >> baggage.placeForBaggage;
		std::cout << "������� ��� ������: ";
		in >> baggage.baggageWeight;
	}
	else
	{
		char buf[50];
		//in >> baggage.flightNumber;

		//in.ignore();
		in.getline(buf, 50);
		baggage.passangerLastName = CharArrayToString(buf);
		
		in.getline(buf, 50);
		baggage.destination = CharArrayToString(buf);

		in >> baggage.flightDateAndTime.day;
		in >> baggage.flightDateAndTime.month;
		in >> baggage.flightDateAndTime.year;
		in >> baggage.flightDateAndTime.hour;
		in >> baggage.flightDateAndTime.minute;
		in >> baggage.placeForBaggage;
		in >> baggage.baggageWeight;

		in.ignore();
	}
	
	return in;
}