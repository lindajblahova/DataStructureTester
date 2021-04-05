#pragma once
#include "ScenariosOther.h"
#include "ScenariosMatrix.h"
#include "structures/heap_monitor.h"

template<typename T>
class Test
{
public: 
	Test();

	virtual void test(Scenarios* scenario) = 0;

	~Test();
};

template<typename T>
inline Test<T>::Test()
{
}

template<typename T>
inline Test<T>::~Test()
{
}
