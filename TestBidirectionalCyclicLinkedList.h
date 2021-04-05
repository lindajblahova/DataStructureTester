#pragma once

#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "structures/list/bidirectional_cyclic_linked_list.h"
#include "TestList.h"

template<typename T>
class TestBidirectionalCyclicLinkedList : public TestList<T>
{
public:

	TestBidirectionalCyclicLinkedList();
	~TestBidirectionalCyclicLinkedList();

private:

	List<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestBidirectionalCyclicLinkedList<T>::TestBidirectionalCyclicLinkedList() : TestList<T>()
{
}

template<typename T>
inline TestBidirectionalCyclicLinkedList<T>::~TestBidirectionalCyclicLinkedList()
{
}

template<typename T>
inline List<T>* TestBidirectionalCyclicLinkedList<T>::newStructure()
{
	return new BidirectionalCyclicLinkedList<T>();
}

template<typename T>
inline string TestBidirectionalCyclicLinkedList<T>::getFileName()
{
	return  "csv/BidirectionalCyclicLinkedListTest.csv";
}

template<typename T>
inline string TestBidirectionalCyclicLinkedList<T>::getName()
{
	return "BCLL";
}
