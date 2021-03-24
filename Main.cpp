#include <iostream>

#include "ADTTests.h"

using namespace std;

int main()
{
	initHeapMonitor();
	srand(time(nullptr));

	ADTTests tester;
	tester.chooseStructure();
	tester.~ADTTests();

	return 0;
}

