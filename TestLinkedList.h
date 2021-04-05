#pragma once

#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "TestList.h"

template<typename T>
class TestLinkedList : public TestList<T>
{
public:

	TestLinkedList();
	~TestLinkedList();

private:

	List<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestLinkedList<T>::TestLinkedList() : TestList<T>()
{
}

template<typename T>
inline TestLinkedList<T>::~TestLinkedList()
{
}

template<typename T>
inline List<T>* TestLinkedList<T>::newStructure()
{
	return new LinkedList<T>();
}

template<typename T>
inline string TestLinkedList<T>::getFileName()
{
	return "csv/LinkedListTest.csv";
}

template<typename T>
inline string TestLinkedList<T>::getName()
{
	return "LL";
}
