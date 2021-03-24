#pragma once

#include "TestPriorityQueue.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"


template<typename T>
class TestPriorityQueueSortedArrayList : public TestPriorityQueue<T>
{
public:

	TestPriorityQueueSortedArrayList();
	~TestPriorityQueueSortedArrayList();

private:

	virtual PriorityQueue<T>* create() override;
	virtual const char* getFileName() override;
};

template<typename T>
inline TestPriorityQueueSortedArrayList<T>::TestPriorityQueueSortedArrayList()
{
}

template<typename T>
inline TestPriorityQueueSortedArrayList<T>::~TestPriorityQueueSortedArrayList()
{
}

template<typename T>
inline PriorityQueue<T>* TestPriorityQueueSortedArrayList<T>::create()
{
	return new PriorityQueueSortedArrayList<T>();
}

template<typename T>
inline const char* TestPriorityQueueSortedArrayList<T>::getFileName()
{
	return "PriorityQueueSortedArrayListTest.csv";
}
