#include "ScenariosOther.h"
#include "structures/heap_monitor.h"
#include <algorithm>

ScenariosOther::ScenariosOther() : Scenarios()
{
}


ScenariosOther::ScenariosOther(Array<short int>* dataFromFile, int numberOfOperations, structureTypes type) : Scenarios(dataFromFile, type)
{

	operations_ = new Array<byte>(numberOfOperations);
	this->copyAndShuffleOperations();

}

ScenariosOther::ScenariosOther(Array<short int>* dataFromFile, int numberOfOperations, int structureType) : Scenarios(dataFromFile, structureType)
{
	operations_ = new Array<byte>(numberOfOperations);
	this->copyAndShuffleOperations();
}

int ScenariosOther::getOperation(int index)
{
	return static_cast<int>((*this->operations_)[index]);
}

int ScenariosOther::getOperationData()
{
	return operations_->size();
}


void ScenariosOther::copyAndShuffleOperations()
{

	Array<byte>* mapRatio = new Array<byte>(100);
	int index = 0;
	for (int i = 0; i < dataFromFile_->size(); i++) {
		for (int y = 0; y < (*dataFromFile_)[i]; y++) {
			(*mapRatio)[y + index] = static_cast<byte>(i);
		}
		index += (*dataFromFile_)[i];
	}
	int ratio = (operations_->size() / mapRatio->size());
	for (int i = 0; i < ratio; i++)
	{
		Array<byte>::copy(*mapRatio, 0, *operations_, i * mapRatio->size(), mapRatio->size());
	}

	random_shuffle(&(*operations_)[0], &(*operations_)[operations_->size() - 1]);
	delete mapRatio;
}

ScenariosOther::~ScenariosOther()
{
	delete operations_;
	operations_ = nullptr;
}
