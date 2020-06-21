#include <vector>
#include <iterator>
#include <functional>
#include <fstream>
#include <algorithm>
#include "SupportiveFunctions.h"

#pragma once

template <class T>
class VectorOperations
{
private:
	std::vector<T> _vector;

	// Проверка на выход индекса за пределы контейнера
	bool IsIndexOk(const int& index);

public:
	typedef typename std::vector<T>::iterator iterator_t;

	VectorOperations()
	{
		std::vector<T> _vector;
	}

	int GetSize();	

	iterator_t GetEndIter();

	T& operator[] (const int& index);

	// 1.1 Операции добавления элемента
	iterator_t AddElement(const T& item);
	iterator_t AddElementAt(const int& index, const T& item);
	iterator_t AddElementAt(const iterator_t& it, const T& item);

	// 1.2 Операции изменения элемента
	iterator_t ReplaceElementWith(const int& index, const T& item);
	iterator_t ReplaceElementWith(iterator_t& it, const T& item);

	iterator_t ModifyElement(const int& index, std::function<void(T&)> modify);

	// 1.3 Операции удаления элемента
	iterator_t RemoveElement(const T& item);
	iterator_t RemoveElementAt(const int& index);
	iterator_t RemoveElementAt(const iterator_t& it);

	// "Обертка" std::for_each (В частном случае можно найти суммарный вес багажа)
	void ForEach(std::function<void(T&)> f);

	// 2.1 Ввод элементов контейнера
	void ReadFromConsole(); 
	void ReadFromFile(std::string fileName);

	// 2.2 Вывод элементов контейнера
	void PrintToConsole() const;
	void PrintToFile(std::string fileName) const;

	// 3.1 Поиск элементов по критериям
	iterator_t FindElementLinear(std::function<bool(const T&)> pred);
	iterator_t FindElementBinary(std::function<bool(const T&, const T&)> comp, std::function<int(const T&)> pred);

	// 3.2 Поиск выборки по критериям
	void SelectElements(std::function<bool(const T&)> pred);

	void Serialize(std::ofstream& ofs);
	void Deserialize(std::ifstream& ifs);
};

template<class T>
bool VectorOperations<T>::IsIndexOk(const int& index)
{
	if (index < 0 || index > _vector.size())		
		return false;
	return true;
}

template<class T>
int VectorOperations<T>::GetSize()
{
	return _vector.size();
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::GetEndIter()
{
	return _vector.end();
}

template<class T>
T& VectorOperations<T>::operator[] (const int& index)
{	
	return _vector[index];
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::AddElement(const T& item)
{
	_vector.push_back(item);
	return _vector.end() - 1;
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::AddElementAt(const int& index, const T& item)
{
	if (IsIndexOk(index))
		return _vector.emplace(_vector.begin() + index, item);
	
	std::cout << "Индекс выходит за пределы контейнера" << std::endl;
	return _vector.end();	
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::AddElementAt(const iterator_t& it, const T& item)
{	
	return _vector.emplace(it, item);			
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::ReplaceElementWith(const int& index, const T& item)
{
	if (IsIndexOk(index))
	{
		_vector.at(index) = item;
		return _vector.begin() + index;
	}

	std::cout << "Индекс выходит за пределы контейнера" << std::endl;
	return _vector.end();	
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::ReplaceElementWith(iterator_t& it, const T& item)
{	
	*it = item;
	return it;	
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::ModifyElement(const int& index, std::function<void(T&)> modify)
{
	if (IsIndexOk(index))
	{
		modify(_vector.at(index));
		return _vector.begin() + index;
	}

	return _vector.end();
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::RemoveElement(const T& item)
{
	typename VectorOperations<T>::iterator_t it = std::find(_vector.begin(), _vector.end(), item);
	if (it == _vector.end())
	{
		std::cout << "Удаляемого элемента нет в контейнере" << std::endl;
		return it;
	}

	return _vector.erase(it);
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::RemoveElementAt(const int& index)
{
	if (IsIndexOk(index))
		return _vector.erase(_vector.begin() + index);

	std::cout << "Индекс выходит за пределы контейнера" << std::endl;
	return _vector.end();
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::RemoveElementAt(const iterator_t& it)
{
	return _vector.erase(it);
}

template<class T>
void VectorOperations<T>::ForEach(std::function<void(T&)> f)
{
	std::for_each(_vector.begin(), _vector.end(), f);
}

template<class T>
void VectorOperations<T>::ReadFromConsole()
{
	_vector.clear();

	std::istream_iterator<T> eos;
	std::istream_iterator<T> is_it(std::cin);

	while (is_it != eos)
	{
		_vector.push_back(*is_it);
		std::cout << "Ещё? (y/n)" << std::endl;
		if (InputString("") == "n")
			is_it = eos;
		else
			++is_it;
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<class T>
void VectorOperations<T>::ReadFromFile(std::string fileName)
{
	_vector.clear();

	std::fstream file(fileName, ios::in);
	while (!file)
	{
		fileName = InputString("Файла с введенным именем не существует, повторите ввод");
		file.open(fileName, ios::in);
	}

	file.close();

	std::ifstream ifs(fileName);

	std::istream_iterator<T> eof;
	std::istream_iterator<T> is_it(ifs);

	while (is_it != eof)
	{
		_vector.push_back(*is_it);
		++is_it;
	}
}

template<class T>
void VectorOperations<T>::PrintToConsole() const
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
void VectorOperations<T>::PrintToFile(std::string fileName) const
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return;
	}
	
	std::ofstream ofs(fileName);

	std::ostream_iterator<T> os_it(ofs, "\n\r");
	std::copy(_vector.begin(), _vector.end(), os_it);
}

template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::FindElementLinear(std::function<bool(const T&)> pred)
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return _vector.end();
	}

	typename std::vector<T>::iterator it = _vector.begin();

	while (it != _vector.end())
		if (pred(*(it)))
			return it;
		else
			++it;

	std::cout << "В контейнере отсутствует элемент, отвечающий заданным критериям" << std::endl;
	return _vector.end();
}


template<class T>
typename VectorOperations<T>::iterator_t VectorOperations<T>::FindElementBinary(std::function<bool(const T&, const T&)> comp, std::function<int(const T&)> pred)
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return _vector.end();
	}

	std::sort(_vector.begin(), _vector.end(), comp);

	typename std::vector<T>::iterator itL = _vector.begin();
	typename std::vector<T>::iterator itR = _vector.end() - 1;
	typename std::vector<T>::iterator itM;

	while (itL <= itR)
	{
		itM = itL + std::distance(itL, itR) / 2;
		int p = pred(*itM);

		if (p == 0)
			return itM;
		else if (p == -1)
			itL = itM + 1;
		else
			itR = itM - 1;
	}

	std::cout << "В контейнере отсутствует элемент, отвечающий заданным критериям" << std::endl;
	return _vector.end();
}

template<class T>
void VectorOperations<T>::SelectElements(std::function<bool(const T&)> pred)
{
	if (!_vector.size())
	{
		std::cout << "Контейнер пуст" << std::endl;
		return;
	}

	VectorOperations<T> resVector;

	for (const T& t : _vector)
		if (pred(t))
			resVector.AddElement(t);

	if (!resVector.GetSize())
	{
		std::cout << "В контейнере отсутствуют элементы, отвечающие заданным критериям" << std::endl;
		return;
	}

	std::cout << "Элементы найдены, выберите вид вывода: " << std::endl
		<< "1 - В консоль" << std::endl
		<< "2 - В файл" << std::endl
		<< "--> ";;

	if (InputUnsigned("", 1, 2) == 1)
		resVector.PrintToConsole();
	else
		resVector.PrintToFile(InputString("Введите имя файла: "));
}

template<class T>
void VectorOperations<T>::Serialize(std::ofstream& ofs)
{
	int size = _vector.size();
	ofs.write((char*)& size, sizeof(int));
	for (T t : _vector) {
		t.Serialize(ofs);
	}
}

template<class T>
void VectorOperations<T>::Deserialize(std::ifstream& ifs)
{
	int size;
	ifs.read((char*)& size, sizeof(int));
	for (int i = 0; i < size; ++i) {
		T t;
		t.Deserialize(ifs);
		_vector.push_front(t);
	}
}