#include "Scenarios.h"
#include <iostream>

#include "structures/heap_monitor.h"
#include "ScenariosOtherBitMap.h"

using namespace std;

Scenarios::Scenarios()
{
}
// nastavi atributy
Scenarios::Scenarios(Array<short int>* data, int structureType) : dataFromFile_(data)
{
	switch (structureType)
	{
	case 0:
		type_ = list;
		break;
	case 1:
		type_ = priorityQueue;
		break;
	case 2:
		type_ = matrix;
		break;
	case 3:
		type_ = set;
		break;
	default:
		break;
	}
}

structureTypes Scenarios::getType()
{
	return type_;
}

Array<short int>* Scenarios::getDataFromFile()
{
	return dataFromFile_;
}

// ulozi scenar do noveho txt suboru
string Scenarios::saveScenario(string toSave)
{
	string filename = toSave + ".txt";
	string folder = "/";
	ofstream file;

	switch (getType())
	{
	case list:
		folder = "list/";
		break;

	case priorityQueue:
		folder = "priorityQueue/";
		break;

	case matrix:
		folder = "matrix/";
		break;

	case set:
		folder = "set/";
		break;

	default:
		break;
	}
	string path = "scenarios/" + folder + filename;
	file.open(path);

	file << folder.substr(0, folder.length() - 1) << endl;

	if (type_ == set)
	{
		ScenariosOtherBitMap* scen = dynamic_cast<ScenariosOtherBitMap*>(this);
		file << scen->getMinBase() << endl;
		file << scen->getMaxBase() << endl;
	}

	file << getOperationData() << endl;

	for (int i = 0; i < this->dataFromFile_->size(); i++) {
		file << (*(this->dataFromFile_))[i] << endl;
	}
	file.close();
	return folder;
}


Scenarios::~Scenarios()
{
	delete dataFromFile_;
	dataFromFile_ = nullptr;
}