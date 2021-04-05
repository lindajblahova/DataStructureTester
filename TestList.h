#pragma once

#include <iostream>
#include <fstream>

#include <ctime>
#include <ratio>
#include <chrono>

#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "ScenariosOther.h"
#include "Scenarios.h"
#include "Test.h"

using namespace std;

template<typename T>
class TestList : public Test<T>
{
public:

	TestList();
	void test(Scenarios* scenario) override;
	~TestList();

protected:

	virtual List<T>* newStructure() = 0;
	virtual string getFileName() = 0;
	virtual string getName() = 0;

};

template<typename T>
inline TestList<T>::TestList() : Test<T>()
{
}

// vola vytvorenie struktury cez newStructure a dostane jej nasov csv suboru cez getFileName a skratku struktury cez getName
// vykonava testovanie struktury podla scenara (pre celkovy pocet operacii prejde pole operations_ a rozhodne sa kotra skupina sa vykona)
// nahodne sa rozhodne ktora operacia zo skupiny sa vykona
// ak bola operacia platna zapisu sa do suboru udaje
// sign ktory sa vypisuje v cykle je pocitadlo ktore ukazuje % vykonaneho testu
template<typename T>
inline void TestList<T>::test(Scenarios* scenario)
{
	ScenariosOther* scen = dynamic_cast<ScenariosOther*>(scenario);
	List<T>* list;
	list = newStructure();
	string fileName = getFileName();
	const int RATIO = 100;
	const char SIGN = 176;
	bool validOperation;
	string operationType = "";
	int currentSize = 0;

	chrono::high_resolution_clock::time_point startTime, endTime;

	ofstream* newfile = new ofstream();
	newfile->open(fileName);

	cout << "0%\t\t\t\t\t\t50%\t\t\t\t\t\t100%" << endl;

	int operationsSize = scen->getOperationData();
	for (int i = 0; i < operationsSize; i++)
	{
		currentSize = list->size();
		bool validOperation = true;
		int generatedIndex = -1;
		if (!list->isEmpty()) 
		{
			generatedIndex = rand() % list->size();
		}
		T generatedValue = static_cast<T>(rand());

		switch (scen->getOperation(i))
		{
		case 0:
			switch (rand() % 3)
			{
			case 0:
				operationType = "vloz na zaciatok";
				startTime = chrono::high_resolution_clock::now();
				list->insert(generatedValue, 0);
				endTime = chrono::high_resolution_clock::now();
				break;

			case 1:
				operationType = "vloz na index";
				if (generatedIndex == 0 && currentSize == 0 )
				{
					startTime = chrono::high_resolution_clock::now();
					list->insert(generatedValue, generatedIndex);
					endTime = chrono::high_resolution_clock::now();
				}
				else
				{
					if (!list->isEmpty())
					{
						startTime = chrono::high_resolution_clock::now();
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
				operationType = "vloz na koniec";
				if (!list->isEmpty())
				{
					startTime = chrono::high_resolution_clock::now();
					list->add(generatedValue);
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
					operationType = "zmaz na zaciatku";
					startTime = chrono::high_resolution_clock::now();
					list->removeAt(0);
					endTime = chrono::high_resolution_clock::now();
					break;
				case 1:
					operationType = "zmaz na indexe";
					startTime = chrono::high_resolution_clock::now();
					list->removeAt(generatedIndex);
					endTime = chrono::high_resolution_clock::now();
					break;
				case 2:
					operationType = "zmaz na konci";
					startTime = chrono::high_resolution_clock::now();
					list->removeAt(currentSize - 1);
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
				case 0:
					operationType = "spristupni na indexe";
					startTime = chrono::high_resolution_clock::now();
					(*list)[generatedIndex];
					endTime = chrono::high_resolution_clock::now();
					break;
				case 1:
					operationType = "nastav na indexe";
					startTime = chrono::high_resolution_clock::now();
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
			operationType = "index prvku";
			if (!list->isEmpty()) 
			{
				T value = (*list)[generatedIndex];
				startTime = chrono::high_resolution_clock::now();
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

		string groupName = "";

		switch (scen->getOperation(i))
		{
		case 0:
			groupName = "vloz";
			break;
		case 1:
			groupName = "zmaz";
			break;
		case 2:
			groupName = "get/set";
			break;
		case 3:
			groupName = "index";
			break;
		default:
			break;
		}
		if (validOperation) 
		{
			*newfile << getName() << ",";
			*newfile << groupName << ",";
			*newfile << operationType << ",";
			*newfile << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << ",";
			*newfile << currentSize;
			*newfile << endl;
		}

		if (i % (operationsSize/RATIO) == 0)
		{
			cout << SIGN;
		}

	}
	cout << endl;

	newfile->close();

	delete newfile;
	newfile = nullptr;

	cout << "Vysledky testu su ulozene v subore: " << fileName << endl;
	delete list;
	list = nullptr;

}

template<typename T>
inline TestList<T>::~TestList()
{
}
