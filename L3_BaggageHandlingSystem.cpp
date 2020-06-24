#include <iostream>
#include "Baggage.h"
#include "DateTime.h"
#include "Flight.h"
#include "FlightsVector.h"
#include "HelpUtils.h"
#include "MyVector.h"

/*

Лабораторная 10:	

	Реализовать систему управления багажом. 

	Реализовать управление списком авиарейсов с багажами: 
		добавление, редактирование, удаление и просмотр содержания всех авиарейсов. 

	Реализовать управление выбранным авиарейсом: 
		добавление, редактирование, удаление и просмотр багажей на авиарейсе. 

	Реализовать функционал перемещения багажей, выбранных по заданному критерию, между авиарейсами.

	Предусмотреть вывод списка багажей выбранного авиарейса с фильтрацией по всем возможным полям. 

	Предусмотреть вывод списка авиарейсов с фильтрацией по всем возможным полям.

	Предусмотреть вывод сводного отчета по авиарейсам: 
		количество пассажиров на авиарейсе, количество нужного места для багажа, суммарный вес багажа.

Данильченко Роман, 9 гр.

*/

using namespace std;

// Файл, где будут храниться сведения об авиарейсах
const string FLIGHTS_DATA_FILE = "Flights_Data.txt";

function<bool(const Flight&)> GetFunctionWithFlightCriteria()
{
	cout << "Выберите критерий, по которому будут отобраны авиарейсы:" << endl
		<< "1 - Номер авиарейса" << endl
		<< "2 - Пункт вылета" << endl
		<< "3 - Пункт назначения" << endl
		<< "4 - Дата вылета" << endl
		<< "5 - Количество багажей" << endl
		<< "--> ";

	switch (InputUnsigned("", 1, 5))
	{
	case 1:
		cout << "Выберите, какие авиарейсы будут отобраны:" << endl
			<< "1 - Авиарейсы с номером больше нужного" << endl
			<< "2 - Авиарейсы с номером меньше нужного" << endl
			<< "3 - Авиарейсы с номером больше одного, но меньше другого" << endl;

		switch (InputUnsigned("", 1, 3))
		{
		case 1:
		{
			int flightNumberLeft = InputUnsigned("Введите нужный номер авиарейса: ");

			return [flightNumberLeft](const Flight& flight) { return flight.flightNumber > flightNumberLeft; };
		}
		case 2:
		{
			int flightNumberRight = InputUnsigned("Введите нужный номер авиарейса: ");

			return [flightNumberRight](const Flight& flight) { return flight.flightNumber < flightNumberRight; };
		}
		case 3:
		{
			int flightNumberLeft = InputUnsigned("Введите первый номер авиарейса: ");
			int flightNumberRight = InputUnsigned("Введите второй номер авиарейса: ");

			return [flightNumberLeft, flightNumberRight](const Flight& flight) { return flight.flightNumber > flightNumberLeft && flight.flightNumber < flightNumberRight; };
		}
		}
	case 2:
	{
		string departurePoint = InputString("Введите нужный пункт вылета: ");

		return [departurePoint](const Flight& flight) { return flight.departurePoint == departurePoint; };
	}
	case 3:
	{
		string arrivalPoint = InputString("Введите нужный пункт вылета: ");

		return [arrivalPoint](const Flight& flight) { return flight.arrivalPoint == arrivalPoint; };
	}
	case 4:
		cout << "Выберите, какие авиарейсы будут отобраны:" << endl
			<< "1 - Авиарейсы с датой вылета позднее нужной" << endl
			<< "2 - Авиарейсы с датой вылета раньше нужной" << endl
			<< "3 - Авиарейсы с датой вылета между двумя датами" << endl;

		switch (InputUnsigned("", 1, 3))
		{
		case 1:
		{
			DateTime flightDateTimeLeft;
			
			cout << "Введите нужную дату: " << endl;
			cin >> flightDateTimeLeft;

			return [flightDateTimeLeft](const Flight& flight) { return flight.flightDateTime > flightDateTimeLeft; };
		}
		case 2:
		{
			DateTime flightDateTimeRight;

			cout << "Введите нужную дату: " << endl;
			cin >> flightDateTimeRight;

			return [flightDateTimeRight](const Flight& flight) { return flight.flightDateTime < flightDateTimeRight; };
		}
		case 3:
		{
			DateTime flightDateTimeLeft;
			DateTime flightDateTimeRight;			

			cout << "Введите первую дату: " << endl;
			cin >> flightDateTimeLeft;

			cout << "Введите вторую дату: " << endl;
			cin >> flightDateTimeRight;			

			return [flightDateTimeLeft, flightDateTimeRight](const Flight& flight) { return flight.flightDateTime > flightDateTimeLeft && flight.flightDateTime < flightDateTimeRight; };
		}
		}
	case 5:
		cout << "Выберите, какие авиарейсы будут отобраны:" << endl
			<< "1 - Авиарейсы с количеством багажей больше нужного" << endl
			<< "2 - Авиарейсы с количеством багажей меньше нужного" << endl
			<< "3 - Авиарейсы с количеством багажей больше одного количества, но меньше другого" << endl;

		switch (InputUnsigned("", 1, 3))
		{
		case 1:
		{
			int numOfBaggagesLeft = InputUnsigned("Введите нужное количество багажа: ");

			return [numOfBaggagesLeft](const Flight& flight) { return flight.baggages.GetSize() > numOfBaggagesLeft; };
		}
		case 2:
		{
			int numOfBaggagesRight = InputUnsigned("Введите нужное количество багажа: ");

			return [numOfBaggagesRight](const Flight& flight) { return flight.baggages.GetSize() < numOfBaggagesRight; };
		}
		case 3:
		{
			int numOfBaggagesLeft = InputUnsigned("Введите первое количество багажа: ");
			int numOfBaggagesRight = InputUnsigned("Введите второе количество багажа: ");

			return [numOfBaggagesLeft, numOfBaggagesRight](const Flight& flight) { return flight.baggages.GetSize() > numOfBaggagesLeft && flight.baggages.GetSize() < numOfBaggagesRight; };
		}
		}
	}
}

function<bool(const Baggage&)> GetFunctionWithBaggageCriteria()
{
	cout << "Выберите критерий, по которому будут отобраны багажи авиарейса:" << endl
		<< "1 - Номер багажа" << endl
		<< "2 - Фамилия пассажира" << endl
		<< "3 - Количество места для багажа" << endl
		<< "4 - Вес багажа" << endl			
		<< "--> ";

	switch (InputUnsigned("", 1, 4))
	{
	case 1:
		cout << "Выберите, какие багажи будут отобраны:" << endl
			<< "1 - Багажи с номером больше нужного" << endl
			<< "2 - Багажи с номером меньше нужного" << endl
			<< "3 - Багажи с номером больше одного, но меньше другого" << endl;
		 
		switch (InputUnsigned("", 1, 3))
		{
		case 1: 
		{
			int baggageNumberLeft = InputUnsigned("Введите нужный номер багажа: ");

			return [baggageNumberLeft](const Baggage& baggage) { return baggage.baggageNumber > baggageNumberLeft; };
		}
		case 2:
		{
			int baggageNumberRight = InputUnsigned("Введите нужный номер багажа: ");

			return [baggageNumberRight](const Baggage& baggage) { return baggage.baggageNumber < baggageNumberRight; };
		}
		case 3:
		{
			int baggageNumberLeft = InputUnsigned("Введите первый номер багажа: ");
			int baggageNumberRight = InputUnsigned("Введите второй номер багажа: ");

			return [baggageNumberLeft, baggageNumberRight](const Baggage& baggage) { return baggage.baggageNumber > baggageNumberLeft && baggage.baggageNumber < baggageNumberRight; };
		}
		}		
	case 2:
	{
		string passangerLastName = InputString("Введите нужную фамилию пассажира: ");

		return [passangerLastName](const Baggage& baggage) { return baggage.passangerLastName == passangerLastName; };
	}
	case 3:
		cout << "Выберите, какие багажи будут отобраны:" << endl
			<< "1 - Багажи с количеством мест для них больше нужного" << endl
			<< "2 - Багажи с количеством мест для них меньше нужного" << endl
			<< "3 - Багажи с количеством мест для них больше одного, но меньше другого" << endl;

		switch (InputUnsigned("", 1, 3))
		{
		case 1:
		{
			int placeForBaggageLeft = InputUnsigned("Введите нужное количество мест для багажа: ");

			return [placeForBaggageLeft](const Baggage& baggage) { return baggage.placeForBaggage > placeForBaggageLeft; };
		}
		case 2:
		{
			int placeForBaggageRight = InputUnsigned("Введите нужное количество мест для багажа: ");

			return [placeForBaggageRight](const Baggage& baggage) { return baggage.placeForBaggage < placeForBaggageRight; };
		}
		case 3:
		{
			int placeForBaggageLeft = InputUnsigned("Введите первое количество мест для багажа: ");
			int placeForBaggageRight = InputUnsigned("Введите второе количество мест для багажа: ");

			return [placeForBaggageLeft, placeForBaggageRight](const Baggage& baggage) { return baggage.placeForBaggage > placeForBaggageLeft && baggage.baggageNumber < placeForBaggageRight; };
		}
		}
	case 4:
		cout << "Выберите, какие багажи будут отобраны:" << endl
			<< "1 - Багажи с весом больше нужного" << endl
			<< "2 - Багажи с весом меньше нужного" << endl
			<< "3 - Багажи с весом больше одного, но меньше другого" << endl;

		switch (InputUnsigned("", 1, 3))
		{
		case 1:
		{
			int baggageWeightLeft = InputUnsigned("Введите нужный вес багажа: ");

			return [baggageWeightLeft](const Baggage& baggage) { return baggage.baggageWeight > baggageWeightLeft; };
		}
		case 2:
		{
			int baggageWeightRight = InputUnsigned("Введите нужный вес багажа: ");

			return [baggageWeightRight](const Baggage& baggage) { return baggage.baggageWeight < baggageWeightRight; };
		}
		case 3:
		{
			int baggageWeightLeft = InputUnsigned("Введите первый вес багажа: ");
			int baggageWeightRight = InputUnsigned("Введите второй вес багажа: ");

			return [baggageWeightLeft, baggageWeightRight](const Baggage& baggage) { return baggage.baggageWeight > baggageWeightLeft && baggage.baggageWeight < baggageWeightRight; };
		}
		}
	}	
}

void BaggageMenu(FlightsVector& flightsData, Flight& flight, Baggage& baggage)
{
	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Изменить всю информацию о багаже" << endl
			<< "2 - Изменить номер багажа" << endl
			<< "3 - Изменить фамилию пассажира" << endl
			<< "4 - Изменить количество места для багажа" << endl
			<< "5 - Изменить вес багажа" << endl
			<< "0 - Вернуться в предыдущее меню" << endl
			<< "--> ";

		switch (InputUnsigned("", 1, 5))
		{
		case 1:
			std::cout << "Введите новый багаж: " << endl;
			cin >> baggage;
			flightsData.Serialize(FLIGHTS_DATA_FILE);
			break;
		case 2:
		{
			int newBaggageNumber = InputUnsigned("Введите новый номер багажа: ");

			int i = flight.baggages.FindElementLinear([newBaggageNumber](const Baggage& baggage) { return baggage.baggageNumber == newBaggageNumber; });
			if (i != -1)
				cout << "Багаж с введенным номером уже находится в списке" << endl;
			else
			{
				baggage.baggageNumber = newBaggageNumber;
				flightsData.Serialize(FLIGHTS_DATA_FILE);
			}				
			
			break;
		}
		case 3:
			baggage.passangerLastName = InputString("Введите новую фамилию пассажира: ");
			flightsData.Serialize(FLIGHTS_DATA_FILE);
			break;

		case 4:
			baggage.placeForBaggage = InputUnsigned("Введите новое количество места для багажа: ");
			flightsData.Serialize(FLIGHTS_DATA_FILE);
			break;
		case 5:
			baggage.baggageWeight = InputDouble("Введите новый вес багажа: ");
			flightsData.Serialize(FLIGHTS_DATA_FILE);
			break;
		case 0:
			return;
		}
	}	
}

void FlightMenu(FlightsVector& flightsData, Flight& flight)
{
	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Добавить багаж" << endl
			<< "2 - Редактировать информацию об авиарейсе" << endl
			<< "3 - Редактировать багаж" << endl
			<< "4 - Удалить багаж" << endl
			<< "5 - Просмотреть список багажей выбранного авиарейса" << endl
			<< "6 - Вывести багажи, соответствующие критериям" << endl
			<< "7 - Выбрать багажи по критерию и переместить их на другой авиарейс" << endl
			<< "8 - Вывести сводный отчет по авиарейсу" << endl
			<< "0 - Вернуться в предыдущее меню" << endl
			<< "--> ";

		switch (InputUnsigned("", 0, 8))
		{
		case 1:
		{
			Baggage baggage;
			cin >> baggage;
			flight.baggages.AddElement(baggage);
			flight.Serialize(FLIGHTS_DATA_FILE);

			break;
		}		
		case 2:
		{
			cout << "Выберите действие:" << endl
				<< "1 - Редактировать номер авиарейса" << endl
				<< "2 - Редактировать пункт вылета" << endl
				<< "3 - Редактировать пункт назначения" << endl
				<< "4 - Редактировать дату вылета" << endl
				<< "--> ";

			switch (InputUnsigned("", 0, 4))
			{
			case 1:
			{
				int newFlightNumber = InputUnsigned("Введите новый номер авиарейса: ");

				int i = flightsData.flights.FindElementLinear([newFlightNumber](const Flight& flight) { return flight.flightNumber == newFlightNumber; });
				if (i != -1)
					cout << "Авиарейс с введенным номером уже находится в списке" << endl;
				else
				{
					flight.flightNumber = newFlightNumber;
					flight.Serialize(FLIGHTS_DATA_FILE);
				}					

				break;
			}
			case 2:
				flight.departurePoint = InputString("Введите новый пункт вылета: ");
				flight.Serialize(FLIGHTS_DATA_FILE);

				break;			
			case 3:							
				flight.arrivalPoint = InputString("Введите новый пункт назначения: ");
				flight.Serialize(FLIGHTS_DATA_FILE);

				break;			
			case 4:							
				cout << "Введите новую дату: " << std::endl;				
				cin >> flight.flightDateTime;
				flight.Serialize(FLIGHTS_DATA_FILE);

				break;			
			}

			break;			
		}
		case 3:
		{
			int baggageNumber = InputUnsigned("Введите номер багажа, который требуется отредактировать: ");

			int i = flight.baggages.FindElementLinear([baggageNumber](const Baggage& baggage) { return baggage.baggageNumber == baggageNumber; });
			if (i == -1)
				cout << "Багажа с введенным номером нет в списке" << endl;
			else
				BaggageMenu(flightsData, flight, flight.baggages[i]);			

			break;
		}
		case 4:
		{
			int baggageNumber = InputUnsigned("Введите номер багажа, который требуется удалить: ");			

			int i = flight.baggages.FindElementLinear([baggageNumber](const Baggage& baggage) { return baggage.baggageNumber == baggageNumber; });
			if (i == -1)
				cout << "Багажа с введенным номером нет в списке" << endl;
			else
			{
				flight.baggages.RemoveElementAt(i);
				flightsData.Serialize(FLIGHTS_DATA_FILE);
			}				

			break;
		}
		case 5:
		{
			cout << "Список багажей авиарейса " << flight.flightNumber << ":" << endl << endl;
			flight.baggages.PrintToConsole();

			break;
		}
		case 6:
		{
			MyVector<Baggage> selectedBaggages = flight.baggages.SelectElements(GetFunctionWithBaggageCriteria());
			cout << "Багажи, соответствующие критериям: " << endl;
			selectedBaggages.PrintToConsole();

			break;
		}
		case 7:
		{
			int newFlightNumber = InputUnsigned("Введите номер авиарейса, куда будут перемещены багажи: ");

			if (newFlightNumber == flight.flightNumber)
			{
				cout << "Введенный номер совпадает с выбранным авиарейсом" << endl;
			}
			else
			{
				int i = flightsData.flights.FindElementLinear([newFlightNumber](const Flight& flight) { return flight.flightNumber == newFlightNumber; });
				
				if (i == -1)
					cout << "Авиарейса с введенным номером нет в списке" << endl;
				else
				{
					MyVector<Baggage> selectedBaggages = flight.baggages.SelectElements(GetFunctionWithBaggageCriteria(), true);
					int size = selectedBaggages.GetSize();
					for (int j = 0; j < size; ++j)
						flightsData.flights[i].baggages.AddElement(selectedBaggages[j]);

					cout << "Выбранные багажи были успешно перемещены на новый авиарейс" << endl;
					flight.Serialize(FLIGHTS_DATA_FILE);
				}
			}
						
			break;
		}
		case 8:
		{
			cout << "Выберите действие:" << endl
				<< "1 - Вывести общее количество пассажиров на авиарейсе" << endl
				<< "2 - Вывести количество нужного места для багажа" << endl
				<< "3 - Вывести суммарный вес багажа" << endl				
				<< "--> ";

			switch (InputUnsigned("", 1, 3))
			{
			case 1:
				cout << "Общее количество пассажиров на авиарейсе: " << flight.baggages.GetSize() << endl;
				break;
			case 2:
			{
				int sumPlace = 0;
				flight.baggages.ForEach([&sumPlace](Baggage& baggage) { sumPlace += baggage.placeForBaggage; });

				cout << "Количество нужного места для багажа: " << sumPlace << endl;

				break;
			}
			case 3:
			{
				double sumWeight = 0;
				flight.baggages.ForEach([&sumWeight](Baggage& baggage) { sumWeight += baggage.baggageWeight; });

				cout << "Суммарный вес багажа: " << sumWeight << " кг" << endl;

				break;
			}				
			}

			break;
		}
		case 0:
			return;
		}
	}
}

void FlightsMenu(FlightsVector& flightsData)
{
	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Добавить авиарейс" << endl
			<< "2 - Редактировать авиарейс" << endl
			<< "3 - Удалить авиарейс" << endl
			<< "4 - Просмотреть содержание всех авиарейсов" << endl
			<< "5 - Вывести авиарейсы, соответствующие критериям" << endl			
			<< "0 - Вернуться в предыдущее меню" << endl
			<< "--> ";

		switch (InputUnsigned("", 0, 4))
		{
		case 1:
		{
			int flightNumber = InputUnsigned("Введите номер нового авиарейса: ");

			int i = flightsData.flights.FindElementLinear([flightNumber](const Flight& flight) { return flight.flightNumber == flightNumber; });
			if (i != -1)
				cout << "Авиарейс с введенным номером уже находится в списке" << endl;
			else
			{
				Flight flight;				
				flight.flightNumber = flightNumber;
				flightsData.flights.AddElement(flight);
				flightsData.Serialize(FLIGHTS_DATA_FILE);
			}

			break;
		}
		case 2:
		{
			int flightNumber = InputUnsigned("Введите номер авиарейса, который требуется отредактировать: ");

			int i = flightsData.flights.FindElementLinear([flightNumber](const Flight& flight) { return flight.flightNumber == flightNumber; });
			if (i == -1)
				cout << "Авиарейса с введенным номером нет в списке" << endl;
			else
				FlightMenu(flightsData, flightsData.flights[i]);

			break;
		}
		case 3:
		{
			int flightNumber = InputUnsigned("Введите номер авиарейса, который требуется удалить: ");

			int i = flightsData.flights.FindElementLinear([flightNumber](const Flight& flight) { return flight.flightNumber == flightNumber; });
			if (i == -1)
				cout << "Авиарейса с введенным номером нет в списке" << endl;
			else
			{
				flightsData.flights.RemoveElementAt(i);
				flightsData.Serialize(FLIGHTS_DATA_FILE);
			}

			break;
		}
		case 4:
			cout << "Количество авиарейсов: " << flightsData.flights.GetSize() << std::endl 
				<< "Список авиарейсов: " << std::endl << std::endl;
			flightsData.flights.PrintToConsole();

			break;
		case 5:
		{
			MyVector<Flight> selectedFlights = flightsData.flights.SelectElements(GetFunctionWithFlightCriteria());
			cout << "Авиарейсы, соответствующие критериям: " << endl;
			selectedFlights.PrintToConsole();

			break;
		}				
		case 0:
			return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	FlightsVector flightsData;
	flightsData.Deserialize(FLIGHTS_DATA_FILE);	

	while (true)
	{
		cout << "Выберите действие:" << endl
			<< "1 - Управление списком авиарейсов" << endl
			<< "2 - Управление выбранным авиарейсом" << endl			
			<< "0 - Выход из программы" << endl
			<< "--> ";

		switch (InputUnsigned("", 0, 3))
		{
		case 1:
			FlightsMenu(flightsData);

			break;
		case 2:
		{
			int flightNumber = InputUnsigned("Введите номер авиарейса, который нужно отредактировать: ");

			int flightIndex = flightsData.flights.FindElementLinear([flightNumber](const Flight& flight) { return flight.flightNumber == flightNumber; });
			if (flightIndex == -1)
				cout << "Авиарейса с введенным номером нет в списке" << endl;
			else
				FlightMenu(flightsData, flightsData.flights[flightIndex]);

			break;
		}
		case 0:
			exit(0);
		}
	}
}
