#pragma once

#include "structures/array/array.h"
#include "structures/list/linked_list.h"
#include <fstream>
#include <iostream>


using namespace std;
using namespace structures;

class Scenarios {

public:

	Scenarios();
	char createNewScenario(int structure, fstream& newfile, char scenarioChar);
	int getOperation(int index);
	int getOperationsSize();
	int getRows();
	int getColumns();
	int getMatrixOperation();
	void chooseScenario(int structure);
	void scenarioFillOperations(int countO, int insertO, int deleteO, int getSetO, int indexO);
	void scenarioForMatrix(int operation, int rowsMax, int colsMax);
	void copyAndShuffleOperations(int countO, Array<int>* ratio);
	void readFromFile(fstream& newfile, const char* fileName);
	void clearAllLists();
	
	~Scenarios();

private:
	Array<int>* operations_ = nullptr;
	int matrixRows_ = 0;
	int matrixColumns_ = 0;
	int matrixOperation_ = 0;
	LinkedList<char>* scenariosList_;
	LinkedList<int>* structuresList_;
	LinkedList<int>* operationsCount_;
	LinkedList<int>* firstGroupOperations_;
	LinkedList<int>* secondGroupOperations_;
	LinkedList<int>* thirdGroupOperations_;
	LinkedList<int>* fourthGroupOperations_;
};