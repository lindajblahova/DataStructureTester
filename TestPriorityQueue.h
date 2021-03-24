#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "structures/priority_queue/priority_queue.h"
#include "Scenarios.h"



template<typename T>
class TestPriorityQueue
{
public:

	void test(Scenarios* scenario);

private:
	virtual PriorityQueue<T>* create() = 0;
	virtual const char* getFileName() = 0;

	void push(const int priority, const T& data, PriorityQueue<T>* priorityQueue);
	T pop(PriorityQueue<T>* priorityQueue);
	T peek(PriorityQueue<T>* priorityQueue);

};

template<typename T>
inline void TestPriorityQueue<T>::test(Scenarios* scenario)
{
	
	PriorityQueue<T>* priorityQueue;
	priorityQueue = create();
	const char* fileName = getFileName();
	const int MAX_PRIORITY = 10000;
	const int OPERATIONS__COUNT = 100000;
	int invalidOperations = 0;
	bool validOperation;
	chrono::high_resolution_clock::time_point startTime, endTime;

	ofstream newfile;
	newfile.open(fileName);



	for (int i = 0; i < OPERATIONS__COUNT; i++)
	{
		validOperation = true;
		int generatedPriority = rand() % MAX_PRIORITY;
		T generatedValue = static_cast<T>(rand());

		startTime = chrono::high_resolution_clock::now();

		switch (scenario->getOperation(i))
		{
		case 0:
			push(generatedPriority, generatedValue, priorityQueue);
			break;

		case 1:
			if (!priorityQueue->isEmpty())
			{
				pop(priorityQueue);
			}
			else
			{
				validOperation = false;
			}
			break;

		case 2:
			if (!priorityQueue->isEmpty())
			{
				peek(priorityQueue);
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
			endTime = chrono::high_resolution_clock::now();
			newfile << scenario->getOperation(i) << ",";
			newfile << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << ",";
			newfile << priorityQueue->size();
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
	delete priorityQueue;
}

template<typename T>
inline void TestPriorityQueue<T>::push(const int priority, const T& data, PriorityQueue<T>* priorityQueue)
{
	priorityQueue->push(priority, data);
}

template<typename T>
inline T TestPriorityQueue<T>::pop(PriorityQueue<T>* priorityQueue)
{
	return priorityQueue->pop();
}

template<typename T>
inline T TestPriorityQueue<T>::peek(PriorityQueue<T>* priorityQueue)
{
	return priorityQueue->peek();
}

