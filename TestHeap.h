#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "structures/priority_queue/heap.h"

template<typename T>
class TestHeap : public TestPriorityQueue<T>
{
public:

	TestHeap();
	~TestHeap();

private:

	PriorityQueue<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestHeap<T>::TestHeap() : TestPriorityQueue<T>()
{
}

template<typename T>
inline TestHeap<T>::~TestHeap()
{
}

template<typename T>
inline PriorityQueue<T>* TestHeap<T>::newStructure()
{
	return new Heap<T>();
}

template<typename T>
inline string TestHeap<T>::getFileName()
{
	return "csv/HeapTest.csv";
}

template<typename T>
inline string TestHeap<T>::getName()
{
	return "HEAP";
}
