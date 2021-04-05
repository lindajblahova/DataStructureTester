#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "structures/priority_queue/priority_queue_two_lists_limited_capacity.h"


template<typename T>
class TestTwoListsLimitedCapacity : public TestPriorityQueue<T>
{
public:

	TestTwoListsLimitedCapacity(size_t capacity);
	~TestTwoListsLimitedCapacity();

private:

	PriorityQueue<T>* newStructure() override;
	string getFileName() override;
	string getName() override;

private:

	// atribut uklada v sebe kapacitu, ktora prichadza konstruktorom(z vytvorenia testu), aby sa podla nej mohla vytvorit instancia s kapacitou
	size_t capacity_;
};

template<typename T>
inline TestTwoListsLimitedCapacity<T>::TestTwoListsLimitedCapacity(size_t capacity) : TestPriorityQueue<T>(), capacity_(capacity)
{
}

template<typename T>
inline TestTwoListsLimitedCapacity<T>::~TestTwoListsLimitedCapacity()
{
}

template<typename T>
inline PriorityQueue<T>* TestTwoListsLimitedCapacity<T>::newStructure()
{
	return new PriorityQueueTwoListsLimitedCapacity<T>(capacity_);
}

template<typename T>
inline string TestTwoListsLimitedCapacity<T>::getFileName()
{
	return "csv/TwoListsLimitedCapacityTest.csv";
}

template<typename T>
inline string TestTwoListsLimitedCapacity<T>::getName()
{
	return "TLCONST";
}
