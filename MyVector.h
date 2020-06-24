#include <vector>
#include <iterator>
#include <functional>
#include <fstream>
#include <algorithm>
#include "HelpUtils.h"

#pragma once

template <class T>
class MyVector
{
private:
	std::vector<T> _vector;

	// Проверка на выход индекса за пределы контейнера
	bool IsIndexOk(const int& index);

public:

	int GetSize() const;

	T& operator[] (const int& index);

	// 1.1 Операции добавления элемента
	int AddElement(const T& item);
	void AddElementAt(const int& index, const T& item);	

	// 1.2 Операции изменения элемента
	void ReplaceElementWith(const int& index, const T& item);	

	void ModifyElement(const int& index, std::function<void(T&)> modifyFunction);

	// 1.3 Операции удаления элемента
	int RemoveElement(const T& item);
	void RemoveElementAt(const int& index);	

	// "Обертка" std::for_each (В частном случае можно найти суммарный вес багажа)
	void ForEach(std::function<void(T&)> forEachFunction);

	// 2.1 Ввод элементов контейнера
	void ReadFromConsole();
	void ReadFromFile(std::string fileName);
	void ReadFromFile(std::istream& is, int numOfObjects);

	// 2.2 Вывод элементов контейнера
	void PrintToConsole() const;
	void PrintToFile(std::string fileName) const;
	void PrintToFile(std::ostream& os) const;

	// 3.1 Поиск элементов по критериям
	int FindElementLinear(std::function<bool(const T&)> pred);
	int FindElementBinary(std::function<bool(const T&, const T&)> comp, std::function<int(const T&)> pred);

	// 3.2 Поиск выборки по критериям
	MyVector<T> SelectElements(std::function<bool(const T&)> pred, bool DeleteSelected = false);
};

template<class T>
bool MyVector<T>::IsIndexOk(const int& index)
{
	return index >= 0 && index < _vector.size();
}

template<class T>
int MyVector<T>::GetSize() const
{
	return _vector.size();
}

template<class T>
T& MyVector<T>::operator[] (const int& index)
{
	return _vector[index];
}

template<class T>
int MyVector<T>::AddElement(const T& item)
{
	_vector.push_back(item);
	return _vector.size() - 1;
}

template<class T>
void MyVector<T>::AddElementAt(const int& index, const T& item)
{
	if (IsIndexOk(index))
		_vector.emplace(_vector.begin() + index, item);
	else
		std::cout << "Индекс выходит за пределы контейнера" << std::endl;	
}

template<class T>
void MyVector<T>::ReplaceElementWith(const int& index, const T& item)
{
	if (IsIndexOk(index))
		_vector.at(index) = item;
	else
		std::cout << "Индекс выходит за пределы контейнера" << std::endl;	
}

template<class T>
void MyVector<T>::ModifyElement(const int& index, std::function<void(T&)> modifyFunction)
{
	if (IsIndexOk(index))
		modifyFunction(_vector.at(index));
	else
		std::cout << "Индекс выходит за пределы контейнера" << std::endl;
}

template<class T>
int MyVector<T>::RemoveElement(const T& item)
{
	typename std::vector<T>::iterator it = std::find(_vector.begin(), _vector.end(), item);
	if (it == _vector.end())
		return -1;
		
	return std::distance(_vector.begin(), _vector.erase(it));
}

template<class T>
void MyVector<T>::RemoveElementAt(const int& index)
{
	if (IsIndexOk(index))
		_vector.erase(_vector.begin() + index);
	else
		std::cout << "Индекс выходит за пределы контейнера" << std::endl;
}

template<class T>
void MyVector<T>::ForEach(std::function<void(T&)> forEachFunction)
{
	std::for_each(_vector.begin(), _vector.end(), forEachFunction);
}

template<class T>
void MyVector<T>::ReadFromConsole()
{	
	_vector.clear();

	std::istream_iterator<T> eos;
	std::istream_iterator<T> is_it(std::cin);

	while (is_it != eos)
	{
		_vector.push_back(*is_it);	
		std::cout << "Ещё? (y/n)" << std::endl;
		switch (std::cin.get())
		{
		case 'y':
		case 'Y':
		case 'н':
		case 'Н':
			++is_it;
			break;
		default:
			is_it = eos;
			break;
		}		
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


template<class T>
void MyVector<T>::ReadFromFile(std::string fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs)
	{
		std::cout << "Введенного файла не существует";
		return;
	}
	
	_vector.clear();
	
	std::istream_iterator<T> eof;
	std::istream_iterator<T> is_it(ifs);

	while (is_it != eof)
	{
		_vector.push_back(*is_it);
		++is_it;
	}

	ifs.close();
}


template<class T>
void MyVector<T>::ReadFromFile(std::istream& is, int numOfObjects)
{
	_vector.clear();

	std::istream_iterator<T> is_it(is);
	_vector.push_back(*is_it);

	while (--numOfObjects > 0)
	{
		++is_it;
		_vector.push_back(*is_it);
	}
}

template<class T>
void MyVector<T>::PrintToConsole() const
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return;
	}

	std::ostream_iterator<T> os_it(std::cout, "\n\r");
	std::copy(_vector.begin(), _vector.end(), os_it);
}

template<class T>
void MyVector<T>::PrintToFile(std::string fileName) const
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return;
	}

	std::ofstream ofs(fileName);

	PrintToFile(ofs);
}

template<class T>
void MyVector<T>::PrintToFile(std::ostream& os) const
{
	std::ostream_iterator<T> os_it(os, "\n\r");
	std::copy(_vector.begin(), _vector.end(), os_it);
}

template<class T>
int MyVector<T>::FindElementLinear(std::function<bool(const T&)> pred)
{
	typename std::vector<T>::iterator it = std::find_if(_vector.begin(), _vector.end(), pred);

	if (it == _vector.end())		
		return -1;
	
	return std::distance(_vector.begin(), it);
}

template<class T>
int MyVector<T>::FindElementBinary(std::function<bool(const T&, const T&)> comp, std::function<int(const T&)> pred)
{
	if (!_vector.size())		
		return -1;
	
	std::sort(_vector.begin(), _vector.end(), comp);

	typename std::vector<T>::iterator itL = _vector.begin();
	typename std::vector<T>::iterator itR = _vector.end() - 1;
	typename std::vector<T>::iterator itM;

	while (itL <= itR)
	{
		itM = itL + std::distance(itL, itR) / 2;
		int p = pred(*itM);

		if (p == 0)
			return std::distance(_vector.begin(), itM);
		else if (p == -1)
			itL = itM + 1;
		else
			itR = itM - 1;
	}
	
	return -1;
}

template<class T>
MyVector<T> MyVector<T>::SelectElements(std::function<bool(const T&)> pred, bool DeleteSelected)
{
	MyVector<T> resVector;

	if (_vector.size())
	{
		typename std::vector<T>::iterator it = _vector.begin();		
		for (; it != _vector.end(); ++it)
		{
			if (pred(*it))
			{
				resVector.AddElement(*it);
				if (DeleteSelected)
					it = --_vector.erase(it);								
			}
		}
	}		

	return resVector;
}