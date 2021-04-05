#include "ScenariosMatrix.h"
#include "structures/heap_monitor.h"

ScenariosMatrix::ScenariosMatrix() : Scenarios()
{
}

ScenariosMatrix::ScenariosMatrix(Array<short int>* dataFromFile, int operationToPerform) : Scenarios(dataFromFile, 2)
{
	dataFromFile_ = dataFromFile;
	operationToPerform_ = operationToPerform;
}

int ScenariosMatrix::getConstValue()
{
	return (*dataFromFile_)[0];
}

int ScenariosMatrix::getVariableValue()
{
	return (*dataFromFile_)[1];
}

int ScenariosMatrix::getStep()
{
	return (*dataFromFile_)[2];
}

int ScenariosMatrix::getOperationData()
{
	return operationToPerform_;
}

ScenariosMatrix::~ScenariosMatrix()
{
	operationToPerform_ = -1;
}
