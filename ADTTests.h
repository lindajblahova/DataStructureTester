#pragma once
#include <fstream>
#include <iostream>
#include "structures/heap_monitor.h"

#include "structures/vector/vector.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/matrix/incoherent_matrix.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"
#include "structures/priority_queue/heap.h"

#include "Scenarios.h"
#include "TestArrayList.h"
#include "TestLinkedList.h"
#include "TestBidirectionalCyclicLinkedList.h"
#include "TestPriorityQueueSortedArrayList.h"
#include "TestTwoListsLimitedCapacity.h"
#include "TestTwoListsHalfCapacity.h"
#include "TestTwoListsSqrtCapacity.h"
#include "TestHeap.h"
#include "TestPriorityQueue.h"
#include "TestCoherentMatrix.h"
#include "TestIncoherentMatrix.h"
#include "TestBitmap.h"
#include "TestSet.h"


using namespace std;
using namespace structures;

class ADTTests {

public:

	ADTTests();

	void testStructureFromFile();
	
	~ADTTests();

private:

	Scenarios* newScenario(int type);
	Scenarios* createScenarioMatrix();
	Scenarios* createScenario(int type);
	void testsTable(structureTypes type);
	int scenariosTable(string path, string folder, int structure);
	void testForStructure(Scenarios* scenario);

private:
	LinkedList<string>* scenariosForADT_ = nullptr;
};