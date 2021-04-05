#pragma once

#include <fstream>
#include <iostream>

#include "structures/heap_monitor.h"
#include "structures/array/array.h"
#include "structures/list/linked_list.h"
#include "structureTypes.h"


using namespace std;
using namespace structures;

class Scenarios {

public:

	Scenarios();
	Scenarios(Array<short int>* data, int structureType);
	structureTypes getType();
	Array<short int>* getDataFromFile();

	virtual int getOperationData() = 0;
	string saveScenario(string toSave);

	~Scenarios();

protected:

	Array<short int>* dataFromFile_;
	structureTypes type_;

};