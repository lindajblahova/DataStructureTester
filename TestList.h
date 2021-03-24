#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "structures/list/list.h"
#include "Scenarios.h"

using namespace std;

template<typename T>
class TestList
{
public:

	TestList();
	void test(Scenarios* scenario);
	~TestList();

private:

	virtual List<T>* newStructure() = 0;
	virtual const char* getFileName() = 0;

	void insertFirst(const T& data, List<T>* list);
	T deleteFirst(List<T>* list);
	void insertLast(const T& data, List<T>* list);
	T deleteLast(List<T>* list);
	void insertAtIndex(const int index, const T& data, List<T>* list);
	T deleteAtIndex(const int index, List<T>* list);
	T getData(const int index, List<T>* list);
	void setData(const int index, const T& data, List<T>* list);
	int getIndexOf(const T& data, List<T>* list);


};

template<typename T>
inline TestList<T>::TestList()
{
}

template<typename T>
inline void TestList<T>::test(Scenarios* scenario)
{
	List<T>* list;
	list = newStructure();
	const char* fileName = getFileName();
	int invalidOperations = 0;
	bool validOperation;
	chrono::high_resolution_clock::time_point startTime, endTime;

	ofstream newfile;
	newfile.open(fileName);


	int operations = scenario->getOperationsSize();
	for (int i = 0; i < operations; i++)
	{
		bool validOperation = true;
		int generatedIndex = -1;
		if (!list->isEmpty()) 
		{
			generatedIndex = rand() % list->size();
		}
		T generatedValue = static_cast<T>(rand());

		switch (scenario->getOperation(i))
		{
		case 0:
			switch (rand() % 3)
			{
			case 0:
				startTime = chrono::high_resolution_clock::now();
				//insertFirst(generatedValue, list);
				list->insert(generatedValue, 0);
				endTime = chrono::high_resolution_clock::now();
				break;
			case 1:
				if (generatedIndex == 0 && list->isEmpty()) 
				{
					startTime = chrono::high_resolution_clock::now();
					//insertAtIndex(generatedIndex, generatedValue, list);
					list->insert(generatedValue, generatedIndex);
					endTime = chrono::high_resolution_clock::now();
				}
				else
				{
					if (!list->isEmpty())
					{
						startTime = chrono::high_resolution_clock::now();
						//insertAtIndex(generatedIndex, generatedValue, list);
						list->insert(generatedValue, generatedIndex);
						endTime = chrono::high_resolution_clock::now();
					}
					else
					{
						validOperation = false;
					}
				}				
				break;

			case 2:
				if (!list->isEmpty())
				{
					startTime = chrono::high_resolution_clock::now();
					//insertLast(generatedValue, list);
					list->insert(generatedValue, list->size() - 1);
					endTime = chrono::high_resolution_clock::now();
				}
				else
				{
					validOperation = false;
				}
				
				break;

			default:
				// ???
				break;
			}
			break;
		case 1:
			if (!list->isEmpty()) 
			{
				switch (rand() % 3)
				{

				case 0:
					startTime = chrono::high_resolution_clock::now();
					//deleteFirst(list);
					list->removeAt(0);
					endTime = chrono::high_resolution_clock::now();
					break;
				case 1:
					startTime = chrono::high_resolution_clock::now();
					//deleteAtIndex(generatedIndex, list);
					list->removeAt(generatedIndex);
					endTime = chrono::high_resolution_clock::now();
					break;
				case 2:
					startTime = chrono::high_resolution_clock::now();
					//deleteLast(list);
					list->removeAt(list->size() - 1);
					endTime = chrono::high_resolution_clock::now();
					break;

				default:
					break;
				}
			}
			else
			{
				validOperation = false;
			}
			break;

		case 2:
			if (!list->isEmpty())
			{
				switch (rand() % 2)
				{
				case 1:
					startTime = chrono::high_resolution_clock::now();
					//getData(generatedIndex, list);
					(*list)[generatedIndex];
					endTime = chrono::high_resolution_clock::now();
					break;
				case 2:
					startTime = chrono::high_resolution_clock::now();
					//setData(generatedIndex, generatedValue, list);
					(*list)[generatedIndex] = generatedValue;
					endTime = chrono::high_resolution_clock::now();
					break;

				default:
					break;
				}
			}
			else
			{
				validOperation = false;
			}
			break;

		case 3:
			if (!list->isEmpty()) 
			{
				T value = (*list)[generatedIndex];
				startTime = chrono::high_resolution_clock::now();
				//getIndexOf(value, list);
				list->getIndexOf(value);
				endTime = chrono::high_resolution_clock::now();
			}
			else
			{
				validOperation = false;
			}
			break;

		default:
			break;
		}

		if (validOperation) 
		{
		
			newfile << scenario->getOperation(i) << ",";
			newfile << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << ",";
			newfile << list->size();
			newfile << endl;
		}
		else 
		{
			invalidOperations++;
		}

	}
	newfile << endl;
	newfile << invalidOperations;
	newfile << endl;

	newfile.close();

	cout << "Vysledky testu su ulozene v subore: " << fileName << endl;
	delete list;

}

template<typename T>
inline TestList<T>::~TestList()
{
}


template<typename T>
inline void TestList<T>::insertFirst(const T& data, List<T>* list)
{
	list->insert(data, 0);
}

template<typename T>
inline T TestList<T>::deleteFirst(List<T>* list)
{
	return list->removeAt(0);
}

template<typename T>
inline void TestList<T>::insertLast(const T& data, List<T>* list)
{
	list->insert(data, list->size() - 1);
}

template<typename T>
inline T TestList<T>::deleteLast(List<T>* list)
{
	return list->removeAt(list->size() - 1);
}

template<typename T>
inline void TestList<T>::insertAtIndex(const int index, const T& data, List<T>* list)
{
	list->insert(data, index);
}

template<typename T>
inline T TestList<T>::deleteAtIndex(const int index, List<T>* list)
{
	return list->removeAt(index);
}

template<typename T>
inline T TestList<T>::getData(const int index, List<T>* list)
{
	return (*list)[index];
}

template<typename T>
inline void TestList<T>::setData(const int index, const T& data, List<T>* list)
{
	(*list)[index] = data;
}

template<typename T>
inline int TestList<T>::getIndexOf(const T& data, List<T>* list)
{
	return list->getIndexOf(data);
}
