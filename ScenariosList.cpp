#include "ScenariosList.h"

#include <algorithm>

Scenarios::Scenarios(char scenario)
{
	Array<int>* ratio = new Array<int>(100);
	this->operations = new Array<int>(100000);

	int insertO = 0, deleteO = 0, getSetO = 0, indexO = 0;
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
		(*ratio)[i] = 0;
	}

	for (int i = insertO; i < deleteO; i++)
	{
		(*ratio)[i] = 1;
	}

	for (int i = deleteO; i < getSetO; i++)
	{
		(*ratio)[i] = 2;
	}

	for (int i = getSetO; i < indexO; i++)
	{
		(*ratio)[i] = 3;
	}

	for (int i = 0; i < 1000; i++) 
	{
		Array<int>::copy(*ratio, 0, *this->operations, i*100 , 100);
	}

	std::random_shuffle(&(*this->operations)[0], &(*this->operations)[99999]);
	
	delete ratio;
}

int Scenarios::getOperacia(int index)
{
	return (*this->operations)[index];
}

Scenarios::~Scenarios()
{
	delete this->operations;
}



/*if (scenario == 'a')
{
	insertO = 20;
	deleteO = 20;
	getSetO = 50;
	indexO = 10;
}*/