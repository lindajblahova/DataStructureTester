#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "structures/priority_queue/priority_queue_two_lists_half_capacity.h"


template<typename T>
class TestTwoListsHalfCapacity : public TestPriorityQueue<T>
{
public:

	TestTwoListsHalfCapacity();
	~TestTwoListsHalfCapacity();

private:

	PriorityQueue<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestTwoListsHalfCapacity<T>::TestTwoListsHalfCapacity() : TestPriorityQueue<T>()
{
}

template<typename T>
inline TestTwoListsHalfCapacity<T>::~TestTwoListsHalfCapacity()
{
}

template<typename T>
inline PriorityQueue<T>* TestTwoListsHalfCapacity<T>::newStructure()
{
	return new PriorityQueueTwoListsHalfCapacity<T>();
}

template<typename T>
inline string TestTwoListsHalfCapacity<T>::getFileName()
{
	return "csv/TwoListsHalfCapacityTest.csv";
}

template<typename T>
inline string TestTwoListsHalfCapacity<T>::getName()
{
	return "TLHALF";
}
