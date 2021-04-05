#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "structures/heap_monitor.h"
#include "structures/priority_queue/priority_queue.h"
#include "structures/priority_queue/priority_queue_two_lists_limited_capacity.h"
#include "Scenarios.h"
#include "ScenariosOther.h"
#include "Test.h"



template<typename T>
class TestPriorityQueue : public Test<T>
{
public:

	TestPriorityQueue();
	void test(Scenarios* scenario) override;
	~TestPriorityQueue();

protected:
	virtual PriorityQueue<T>* newStructure() = 0;
	virtual string getFileName() = 0;
	virtual string getName() = 0;

};

template<typename T>
inline TestPriorityQueue<T>::TestPriorityQueue() : Test<T>()
{
}

// vola vytvorenie struktury cez newStructure a dostane jej nasov csv suboru cez getFileName a skratku struktury cez getName
// vykonava testovanie struktury podla scenara (pre celkovy pocet operacii prejde pole operations_ a rozhodne sa kotra skupina sa vykona)
// ak bola operacia platna zapisu sa do suboru udaje
// sign ktory sa vypisuje v cykle je pocitadlo ktore ukazuje % vykonaneho testu
template<typename T>
inline void TestPriorityQueue<T>::test(Scenarios* scenario)
{
	ScenariosOther* scen = dynamic_cast<ScenariosOther*>(scenario);
	PriorityQueue<T>* priorityQueue;
	priorityQueue = newStructure();

	string fileName = getFileName();
	const int MAX_PRIORITY = 10000;  // maximalna generovana priorita 
	const int RATIO = 100;
	const char SIGN = 176;
	bool validOperation;
	int currentSize = 0;
	chrono::high_resolution_clock::time_point startTime, endTime;

	ofstream* newfile = new ofstream();
	newfile->open(fileName);

	cout << "0%\t\t\t\t\t\t50%\t\t\t\t\t\t100%" << endl;
	int operationsSize = scen->getOperationData();
	for (int i = 0; i < operationsSize; i++)   
	{
		currentSize = priorityQueue->size();
		validOperation = true;
		int generatedPriority = rand() % MAX_PRIORITY;
		T generatedValue = static_cast<T>(rand());
		string operationType = "";

		switch (scen->getOperation(i))
		{
		case 0:
			operationType = "vloz";
			startTime = chrono::high_resolution_clock::now();
			priorityQueue->push(generatedPriority, generatedValue);
			endTime = chrono::high_resolution_clock::now();
			break;

		case 1:
			if (!priorityQueue->isEmpty())
			{
				operationType = "vyber";
				startTime = chrono::high_resolution_clock::now();
				priorityQueue->pop();
				endTime = chrono::high_resolution_clock::now();
			}
			else
			{
				validOperation = false;
			}
			break;

		case 2:
			if (!priorityQueue->isEmpty())
			{
				operationType = "ukaz";
				startTime = chrono::high_resolution_clock::now();
				priorityQueue->peek();
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
			*newfile << getName() << ",";
			*newfile << operationType << ",";
			*newfile << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << ",";
			*newfile << currentSize;
			*newfile << endl;
		}

		if (i % (operationsSize / RATIO) == 0)
		{
			cout << SIGN;
		}

	}

	newfile->close();

	delete newfile;
	newfile = nullptr;

	cout << "Vysledky testu su ulozene v subore: " << fileName << endl;
	delete priorityQueue;
	priorityQueue = nullptr;

}

template<typename T>
inline TestPriorityQueue<T>::~TestPriorityQueue()
{
}
