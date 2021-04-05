#include "ScenariosOtherBitMap.h"
#include "structures/heap_monitor.h"

ScenariosOtherBitMap::ScenariosOtherBitMap()
{
}

ScenariosOtherBitMap::ScenariosOtherBitMap(Array<short int>* dataFromFile, int numberOfOperations, int minBase, int maxBase) :
	ScenariosOther(dataFromFile, numberOfOperations, 3)
{
	minBase_ = minBase;
	maxBase_ = maxBase;
}

int ScenariosOtherBitMap::getMinBase()
{
	return minBase_;
}

int ScenariosOtherBitMap::getMaxBase()
{
	return maxBase_;
}

ScenariosOtherBitMap::~ScenariosOtherBitMap()
{
	minBase_ = 0;
	maxBase_ = 0;
}
