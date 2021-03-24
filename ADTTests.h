#pragma once
#include <fstream>
#include <iostream>
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
#include "TestHeap.h"
#include "TestPriorityQueue.h"
#include "TestCoherentMatrix.h"
#include "TestIncoherentMatrix.h"


using namespace std;
using namespace structures;

class ADTTests {

public:

	ADTTests();

	void chooseStructure();
	
	~ADTTests();

private:

	int  createStructureTest(fstream& newfile, int lastStructure);
	void testForStructure(Scenarios* scenario, int adt, int ads1);
	const char* getADTName(int adt, int ads);
	const char* getADSName(int adt, int ads);
	void readFromFile(fstream& newfile, const char* fileName);
	void clearAllLists();

private:

	LinkedList<int>* testsList_;
	LinkedList<int>* ADTToTest_;
	LinkedList<int>* firstADSToTest_;
	LinkedList<int>* secondADSToTest_;
};