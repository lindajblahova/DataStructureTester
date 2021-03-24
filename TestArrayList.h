#pragma once

#include "structures/list/list.h"
#include "TestList.h"

template<typename T>
class TestArrayList : public TestList<T>
{
public:

	TestArrayList();
	~TestArrayList();

private:

	virtual List<T>* newStructure() override;
	virtual const char* getFileName() override;
};

template<typename T>
inline TestArrayList<T>::TestArrayList()
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
inline const char* TestArrayList<T>::getFileName()
{
	return  "ArrayListTest.csv";
}
