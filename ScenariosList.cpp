#include "Scenarios.h"

#include <algorithm>
#include <iostream>

const int OPERATIONS_RATIO =  100;
const int OPERATIONS_COUNT = 100000;

const int OPERATION_INSERT = 0;
const int OPERATION_DELETE = 1;
const int OPERATION_GETSET = 2;
const int OPERATION_INDEX = 3;

Scenarios::Scenarios(char scenario)
{
	int insertO = 0, deleteO = 0, getSetO = 0, indexO = 0;
	Array<int>* ratio = new Array<int>(OPERATIONS_RATIO);
	this->operations = new Array<int>(OPERATIONS_COUNT);


	switch (scenario)
	{
	case 'a':
		insertO = 20;
		deleteO = 20;
		getSetO = 50;
		indexO = 10;
		break;

	case 'b':
		insertO = 35;
		deleteO = 35;
		getSetO = 20;
		indexO = 10;
		break;

	case 'c':
		insertO = 45;
		deleteO = 45;
		getSetO = 5;
		indexO = 5;
		break;

	default:
		//TODO: ???
		break;
	}
	

	for (int i = 0; i < insertO; i++)
	{
		(*ratio)[i] = OPERATION_INSERT;
	}

	for (int i = insertO; i < insertO + deleteO ; i++)
	{
		(*ratio)[i] = OPERATION_DELETE;
	}

	for (int i = insertO + deleteO; i < insertO + deleteO + getSetO; i++)
	{
		(*ratio)[i] = OPERATION_GETSET;
	}

	for (int i = insertO + deleteO + getSetO; i < insertO + deleteO + getSetO + indexO; i++)
	{
		(*ratio)[i] = OPERATION_INDEX;
	}

	for (int i = 0; i < (OPERATIONS_COUNT/OPERATIONS_RATIO); i++) 
	{
		Array<int>::copy(*ratio, 0, *this->operations, i*OPERATIONS_RATIO , OPERATIONS_RATIO);
	}

	std::random_shuffle(&(*this->operations)[0], &(*this->operations)[OPERATIONS_COUNT-1]);
	
	delete ratio;
}

int Scenarios::getOperation(int index)
{
	return (*this->operations)[index];
}

Scenarios::~Scenarios()
{
	delete this->operations;
}