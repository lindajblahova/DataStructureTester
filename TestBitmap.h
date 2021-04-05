#pragma once

#include "structures/heap_monitor.h"
#include "TestPriorityQueue.h"
#include "ScenariosOtherBitMap.h"
#include "structures/set/bitmap.h"
#include "TestSet.h"


class TestBitmap : public TestSet<int>
{
public:

	TestBitmap();
	~TestBitmap();

private:

	BitMap* newStructure(int minBase, int maxBase) override;
	string getFileName() override;
};

inline TestBitmap::TestBitmap() : TestSet<int>()
{
}

inline TestBitmap::~TestBitmap()
{
}

inline string TestBitmap::getFileName()
{
	return "csv/SetBitMapTest.csv";
}

inline BitMap* TestBitmap::newStructure(int minBase, int maxBase)
{
	return new BitMap(minBase, maxBase);
}