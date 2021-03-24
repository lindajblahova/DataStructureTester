#pragma once
#include "TestPriorityQueue.h"
#include "structures/priority_queue/heap.h"

template<typename T>
class TestHeap : public TestPriorityQueue<T>
{
public:

	TestHeap();
	~TestHeap();

private:

	virtual PriorityQueue<T>* create() override;
	virtual const char* getFileName() override;
};

template<typename T>
inline TestHeap<T>::TestHeap()
{
}

template<typename T>
inline TestHeap<T>::~TestHeap()
{
}

template<typename T>
inline PriorityQueue<T>* TestHeap<T>::create()
{
	return new Heap<T>();
}

template<typename T>
inline const char* TestHeap<T>::getFileName()
{
	return "HeapTest.csv";
}
