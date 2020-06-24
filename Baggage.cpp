#include "Baggage.h"
#include "HelpUtils.h"

Baggage::Baggage(int bNumber, std::string pLastName, int pForBaggage, double bWeight)
{
	if (IsInRange(bNumber, 1, 999) && IsInRange(pForBaggage, 1, 9) && bWeight > 0 && bWeight < 30)
	{
		baggageNumber = bNumber;
		passangerLastName = pLastName;
		placeForBaggage = pForBaggage;
		baggageWeight = bWeight;
	}
	else
	{
		baggageNumber = 0;
		passangerLastName = "";
		placeForBaggage = 0;
		baggageWeight = 0;
	}
}

bool operator== (const Baggage& left, const Baggage& right)
{
	return 
		left.baggageNumber == right.baggageNumber &&
		left.passangerLastName == right.passangerLastName &&		
		left.placeForBaggage == right.placeForBaggage &&
		abs(left.baggageWeight - right.baggageWeight) < WEIGHT_EPSILON;
}

bool operator!= (const Baggage& left, const Baggage& right)
{
	return !(left == right);
}

std::ostream& operator<< (std::ostream& out, const Baggage& baggage)
{
	if (&out == &std::cout)
	{
		out << "Номер багажа: " << baggage.baggageNumber << std::endl
			<< "Фамилия владельца: " << baggage.passangerLastName << std::endl
			<< "Количество мест багажа: " << baggage.placeForBaggage << std::endl
			<< "Вес багажа: " << baggage.baggageWeight << std::endl;
	}
	else
	{
		out << baggage.baggageNumber << std::endl
			<< baggage.passangerLastName << std::endl			
			<< baggage.placeForBaggage << std::endl
			<< baggage.baggageWeight;
	}

	return out;
}

std::istream& operator>> (std::istream& in, Baggage& baggage)
{
	if (&in == &std::cin)
	{
		baggage.baggageNumber = InputUnsigned("Введите номер багажа: ", 0, 999);
		baggage.passangerLastName = InputString("Введите фамилию владельца: ");
		baggage.placeForBaggage = InputUnsigned("Введите количество мест багажа: ", 1, 9);
		baggage.baggageWeight = InputDouble("Введите вес багажа: ", 0, 30);
	}
	else
	{
		in >> baggage.baggageNumber;

		char buf[50];
		in.ignore();				
		in.getline(buf, 50);
		baggage.passangerLastName = std::string(buf);

		in >> baggage.placeForBaggage;
		in >> baggage.baggageWeight;		
	}

	return in;
}