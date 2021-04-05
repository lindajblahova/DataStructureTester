#pragma once

#include "structures/heap_monitor.h"
#include "structures/list/list.h"
#include "TestList.h"

template<typename T>
class TestArrayList : public TestList<T>
{
public:

	TestArrayList();
	~TestArrayList();

private:

	List<T>* newStructure() override;
	string getFileName() override;
	string getName() override;
};

template<typename T>
inline TestArrayList<T>::TestArrayList() : TestList<T>()
{
}

template<typename T>
inline TestArrayList<T>::~TestArrayList()
{
}

template<typename T>
inline List<T>* TestArrayList<T>::newStructure()
{
	return new ArrayList<T>();
}

template<typename T>
inline string TestArrayList<T>::getFileName()
{
	return  "csv/ArrayListTest.csv";
}

template<typename T>
inline string TestArrayList<T>::getName()
{
	return "AL";
}
