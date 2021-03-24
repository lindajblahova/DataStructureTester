#pragma once

#include "structures/list/list.h"
#include "TestList.h"

template<typename T>
class TestLinkedList : public TestList<T>
{
public:

	TestLinkedList();
	~TestLinkedList();

private:

	virtual List<T>* newStructure() override;
	virtual const char* getFileName() override;
};

template<typename T>
inline TestLinkedList<T>::TestLinkedList()
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
inline const char* TestLinkedList<T>::getFileName()
{
	return "LinkedListTest.csv";
}
