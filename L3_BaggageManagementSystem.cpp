#include <iostream>
#include "Baggage.h"
#include "DateAndTime.h"
#include "Flight.h"
#include "FlightsVector.h"
#include "SupportiveFunctions.h"
#include "VectorOperations.h"

using namespace std;

void BaggagesMenu(VectorOperations<Baggage> baggages)
{

}

void FlightsMenu(FlightsVector& flights)
{
	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Добавить авиарейс" << endl
			<< "2 - Редактировать авиарейс" << endl
			<< "3 - Удалить авиарейс" << endl
			<< "4 - Просмотреть содержание всех авиарейсов" << endl
			<< "0 - Выйти из программы" << endl
			<< "--> ";

		switch (InputUnsigned("", 0, 4))
		{
		case 1:
		{
			Flight flight;
			flight.flightNumber = InputUnsigned("Введите номер авиарейса");

			if (flights.fVector.FindElementLinear([flight](const Flight& fl) { return flight.flightNumber == fl.flightNumber; }) == flights.fVector.GetEndIter)
				cout << "Авиарейс с введенным номером уже существует" << endl;
			else
			{
				cout << "Выберите вид добавления:" << endl
					<< "1 - В конец контейнера" << endl
					<< "2 - По индексу" << endl
					<< "--> ";

				if (InputUnsigned("", 1, 2) == 1)
					flights.fVector.AddElement(flight);
				else
				{
					int index = InputUnsigned("Введите индекс", 0, flights.fVector.GetSize());
					flights.fVector.AddElementAt(index, flight);
				}
			}
			break;					
		}
		case 2:
		{			
			int flightNumber = InputUnsigned("Введите номер авиарейса, который нужно отредактировать");

			VectorOperations<Flight>::iterator_t flightIt = flights.fVector.FindElementLinear([flightNumber](const Flight& flight) { return flightNumber == flight.flightNumber; });
			if (flightIt != flights.fVector.GetEndIter)
				BaggagesMenu((*flightIt).baggages);
			else
				cout << "Авиарейса с введенным номером нет в списке" << endl;
			break;
		}
		case 3:
		{
			int flightNumber = InputUnsigned("Введите номер авиарейса, который нужно удаи");

			VectorOperations<Flight>::iterator_t flightIt = flights.fVector.FindElementLinear([flightNumber](const Flight& flight) { return flightNumber == flight.flightNumber; });
			if (flightIt != flights.fVector.GetEndIter)
				flights.fVector.RemoveElementAt(flightIt);
			else
				cout << "Авиарейса с введенным номером нет в списке" << endl;

			break;
		}
		case 4:
		{

		}
		}
	}
}

void StartMenu()
{
	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Создать список c авиарейсами" << endl
			<< "2 - Считать существующий список из файла" << endl
			<< "0 - Выйти из программы" << endl
			<< "--> ";

		switch (InputUnsigned("", 0, 2))
		{
		case 1:
		{
			FlightsVector flights;
			FlightsMenu(flights);
			break;
		}		
		case 2:
		{

			break;
		}			
		default:
		{
			exit(0);
		}			
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	StartMenu();
}