#pragma once

#include "structures/heap_monitor.h"
#include "ScenariosOther.h"
class ScenariosOtherBitMap : public ScenariosOther
{
public:

	ScenariosOtherBitMap();
	ScenariosOtherBitMap(Array<short int>* dataFromFile, int numberOfOperations, int minBase, int maxBase );

	int getMinBase();
	int getMaxBase();

	~ScenariosOtherBitMap();

private:
	int minBase_;
	int maxBase_;
};

