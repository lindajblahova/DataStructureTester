#pragma once

#include <iostream>

#include "structures/heap_monitor.h"
#include "structureTypes.h"
#include "Scenarios.h"

using namespace std;
using namespace structures;

class ScenariosMatrix :public Scenarios
{
public:
	ScenariosMatrix();
	ScenariosMatrix(Array<short int>* ratio, int operationToPerform);
	~ScenariosMatrix();

	int getConstValue();
	int getVariableValue();
	int getStep();

	int getOperationData() override;

private:
	int operationToPerform_;
};

