#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"


template<typename T>
class TestPriorityQueueSortedArrayList : public TestPriorityQueue<T>
{
public:

	TestPriorityQueueSortedArrayList();
	~TestPriorityQueueSortedArrayList();

private:

	PriorityQueue<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestPriorityQueueSortedArrayList<T>::TestPriorityQueueSortedArrayList() : TestPriorityQueue<T>()
{
}

template<typename T>
inline TestPriorityQueueSortedArrayList<T>::~TestPriorityQueueSortedArrayList()
{
}

template<typename T>
inline PriorityQueue<T>* TestPriorityQueueSortedArrayList<T>::newStructure()
{
	return new PriorityQueueSortedArrayList<T>();
}

template<typename T>
inline string TestPriorityQueueSortedArrayList<T>::getFileName()
{
	return "csv/PriorityQueueSortedArrayListTest.csv";
}

template<typename T>
inline string TestPriorityQueueSortedArrayList<T>::getName()
{
	return "PQSAL";
}
