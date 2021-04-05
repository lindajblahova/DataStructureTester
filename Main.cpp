#include <iostream>

#include "structures/heap_monitor.h"
#include "ADTTests.h"
#include "TestSet.h"
#include "structures/list/bidirectional_cyclic_linked_list.h"


using namespace std;

int main()
{
	initHeapMonitor();
	srand(time(nullptr));
	ADTTests* tester = new ADTTests();
	try
	{
		tester->testStructureFromFile();
	}
	catch (logic_error e)
	{
		cout << e.what();
	}

	delete tester;
	tester = nullptr;

	return 0;
}

