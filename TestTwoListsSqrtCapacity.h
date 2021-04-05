#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "structures/priority_queue/priority_queue_two_lists_sqrt_capacity.h"


template<typename T>
class TestTwoListsSqrtCapacity : public TestPriorityQueue<T>
{
public:

	TestTwoListsSqrtCapacity();
	~TestTwoListsSqrtCapacity();

private:

	PriorityQueue<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestTwoListsSqrtCapacity<T>::TestTwoListsSqrtCapacity() : TestPriorityQueue<T>()
{
}

template<typename T>
inline TestTwoListsSqrtCapacity<T>::~TestTwoListsSqrtCapacity()
{
}

template<typename T>
inline PriorityQueue<T>* TestTwoListsSqrtCapacity<T>::newStructure()
{
	return new PriorityQueueTwoListsSqrtCapacity<T>();
}

template<typename T>
inline string TestTwoListsSqrtCapacity<T>::getFileName()
{
	return "csv/TwoListsSqrtCapacityTest.csv";
}

template<typename T>
inline string TestTwoListsSqrtCapacity<T>::getName()
{
	return "TLSQRT";
}
