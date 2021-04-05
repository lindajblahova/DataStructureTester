#pragma once
#include <iostream>

#include "structures/heap_monitor.h"
#include "structureTypes.h"
#include "Scenarios.h"

using namespace std;
using namespace structures;

class ScenariosOther : public Scenarios
{
public:
	ScenariosOther();
	ScenariosOther(Array<short int>* ratio, int numberOfOperations, structureTypes type);
	ScenariosOther(Array<short int>* ratio, int numberOfOperations, int structureType);
	~ScenariosOther();

	int getOperation(int index);
	void copyAndShuffleOperations();
	int getOperationData();

private:

	Array<byte>* operations_ = nullptr;

};

