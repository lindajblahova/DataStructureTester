#pragma once

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

	virtual List<T>* newStructure() override;
	virtual const char* getFileName() override;
};

template<typename T>
inline TestBidirectionalCyclicLinkedList<T>::TestBidirectionalCyclicLinkedList()
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
inline const char* TestBidirectionalCyclicLinkedList<T>::getFileName()
{
	return  "BidirectionalCyclicLinkedListTest.csv";
}
