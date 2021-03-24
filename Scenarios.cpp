#include "Scenarios.h"
#include "structures/list/linked_list.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int OPERATIONS_RATIO =  100;

const int OPERATION_INSERT = 0;
const int OPERATION_DELETE = 1;
const int OPERATION_GETSET = 2;
const int OPERATION_INDEX = 3;

Scenarios::Scenarios()
{
	scenariosList_ = new LinkedList<char>();
	structuresList_ = new LinkedList<int>();
	operationsCount_ = new LinkedList<int>();
	firstGroupOperations_ = new LinkedList<int>();
	secondGroupOperations_ = new LinkedList<int>();
	thirdGroupOperations_ = new LinkedList<int>();
	fourthGroupOperations_ = new LinkedList<int>();
}

char Scenarios::createNewScenario(int structure, fstream& newfile, char scenarioChar)
{
	int operationsCount = 0, firstGroup = 0, secondGroup = 0, thirdGroup = 0, fourthGroup = 0;

	while (true)
	{
		if (structure != 2)
		{
			cout << "Zadajte celkovy pocet operacii: ";
			cin >> operationsCount;
			cout << "Zadajte pocet % prvej skupiny operacii: ";
			cin >> firstGroup;
			cout << "Zadajte pocet % druhej skupiny operacii: ";
			cin >> secondGroup;
			cout << "Zadajte pocet % tretej skupiny operacii: ";
			cin >> thirdGroup;
			if (structure == 0)
			{
				cout << "Zadajte pocet % stvrtej skupiny operacii: ";
				cin >> fourthGroup;
			}
			if (firstGroup + secondGroup + thirdGroup + fourthGroup == OPERATIONS_RATIO && (operationsCount % OPERATIONS_RATIO) == 0)
			{
				break;
			}
			cout << "Celkovy pocet operacii musi byt delitelny " << OPERATIONS_RATIO << 
				" a pocet % jednotlivych operacii musi dokopy byt " << OPERATIONS_RATIO  << "!" << endl;
		} 
		else
		{
			cout << "Zadajte operaciu ktoru chcete testovat (0 - scitanie, 1 - nasobenie): ";
			cin >> operationsCount;
			cout << "Zadajte maximalny pocet riadkov M: ";
			cin >> firstGroup;
			cout << "Zadajte maximalny pocet stlpcov N: ";
			cin >> secondGroup;
			if ((firstGroup > 0 && secondGroup > 0) && (operationsCount == 0  || operationsCount == 1))
			{
				break;
			}
			else
			{
				cout << "Niektore zadane udaje boli neplatne!" << endl;
			}
		}

	}

	if (scenarioChar == 'y')
	{
		++scenarioChar;
	}
	newfile << structure << endl;
	newfile << ++scenarioChar << endl;
	newfile << operationsCount << endl;
	newfile << firstGroup << endl;
	newfile << secondGroup << endl;
	newfile << thirdGroup << endl;
	newfile << fourthGroup << endl;
	newfile << ";" << endl;

	return scenarioChar;

}

int Scenarios::getOperation(int index)
{
	return (*this->operations_)[index];
}

int Scenarios::getOperationsSize()
{
	return operations_->size();
}

int Scenarios::getRows()
{
	return matrixRows_;
}

int Scenarios::getColumns()
{
	return matrixColumns_;
}

int Scenarios::getMatrixOperation()
{
	return matrixOperation_;
}

void Scenarios::chooseScenario(int structure)
{
	const char* fileName = "scenarios.txt";
	fstream scenariosFile(fileName);
	string line;
	string structToTest = to_string(structure);
	char scenarioToTest;

	readFromFile(scenariosFile, fileName);
	scenariosFile.close();

	if (structure == 0)
	{
	cout << "_________________________________________________________________________________________________" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|    Scenar     | Pocet operacii|      Vloz     |     Zrus      |  Spristupni   |     Index     |" << endl;
	}
	if (structure == 1)
	{
		cout << "_________________________________________________________________________________" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "|    Scenar     | Pocet operacii|      Vloz     |     Vyber     |      Ukaz     |" << endl;
	}
	if (structure == 2)
	{
		cout << "_________________________________________________________________" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "|    Scenar     |    Operacia   |   Riadky(M)   |   Stlpce(N)   |" << endl;
	}

	for (int i = 0; i < scenariosList_->size(); i++)
	{
		if ((*structuresList_)[i] == structure)
		{
		
			if (structure != 2)
			{
				cout << "+---------------+---------------+---------------+---------------+---------------+";
				if (structure == 0)
				{
					cout << "---------------+";
				}
				cout << endl;

				cout << "|\t" << (*scenariosList_)[i] << "\t|    " << (*operationsCount_)[i] << "\t|\t" << (*firstGroupOperations_)[i]
					<< "\t|\t" << (*secondGroupOperations_)[i] << "\t|\t" << (*thirdGroupOperations_)[i];
				if (structure == 0)
				{
					cout << "\t|\t" << (*fourthGroupOperations_)[i];
				}
				cout << "\t|" << endl;
			}
			else
			{
				cout << "+---------------+---------------+---------------+---------------+" << endl;
				cout << "|\t" << (*scenariosList_)[i] << "\t|\t" << ((*operationsCount_)[i] == 0 ? "sucet" : "sucin") << "\t|\t" << (*firstGroupOperations_)[i]
					 << "\t|\t" << (*secondGroupOperations_)[i] << "\t|" << endl;
			}

		}
	}
	if (structure == 0)
	{
		cout << "+---------------+---------------+---------------+---------------+---------------+---------------+" << endl;
		cout << "|                   Pre vytvorenie vlastneho testovacieho scenara stlacte 'z'                   |" << endl;
		cout << "+-----------------------------------------------------------------------------------------------+" << endl;
	}
	else if (structure == 2)
	{
		cout << "+---------------+---------------+---------------+---------------+" << endl;
		cout << "|   Pre vytvorenie vlastneho testovacieho scenara stlacte 'z'   |" << endl;
		cout << "+---------------------------------------------------------------+" << endl;
	}
	else
	{
		cout << "+---------------+---------------+---------------+---------------+---------------+" << endl;
		cout << "|           Pre vytvorenie vlastneho testovacieho scenara stlacte 'z'           |" << endl;
		cout << "+-------------------------------------------------------------------------------+" << endl;
	}

	cout << "Zadajte pismeno scenara, ktory chcete testovat: ";
	cin >> scenarioToTest;

	bool found = false, created = false;
	char lastScenarioChar = '`';
	int index = 0;

	while (found == false)
	{
		if (scenarioToTest == 'z')
		{
			scenariosFile.open(fileName, fstream::app);
			scenarioToTest = createNewScenario(structure, scenariosFile, lastScenarioChar);
			scenariosFile.close();

			clearAllLists();

			scenariosFile.open(fileName);
			readFromFile(scenariosFile, fileName);
			scenariosFile.close();

			created = true;
		}

		for (int i = 0; i < scenariosList_->size(); i++)
		{
			if ((*structuresList_)[i] == structure && (*scenariosList_)[i] == scenarioToTest)
			{
				index = i;
				found = true;
				break;
			}
			else if ((*structuresList_)[i] == structure)
			{
				lastScenarioChar = (*scenariosList_)[i];
			}
		}

		if (found == false && created == false)
		{
			cout << "Tento scenar neexistuje! Vyberte niektory z existujucich scenarov:" << endl;
			cin >> scenarioToTest;
		}

	}

	if (structure != 2)
	{
		scenarioFillOperations((*operationsCount_)[index], (*firstGroupOperations_)[index], (*secondGroupOperations_)[index],
			(*thirdGroupOperations_)[index], (*fourthGroupOperations_)[index]);
	}
	else
	{
		scenarioForMatrix((*operationsCount_)[index], (*firstGroupOperations_)[index], (*secondGroupOperations_)[index]);
	}

}


void Scenarios::scenarioFillOperations(int countO, int insertO, int deleteO, int getSetO, int indexO)
{
	operations_ = new Array<int>(countO);
	Array<int>* ratio = new Array<int>(OPERATIONS_RATIO);

	for (int i = 0; i < insertO; i++)
	{
		(*ratio)[i] = OPERATION_INSERT;
	}

	for (int i = insertO; i < insertO + deleteO; i++)
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

	this->copyAndShuffleOperations(countO, ratio);

	delete ratio;
}

void Scenarios::scenarioForMatrix(int operation, int rowsMax, int colsMax)
{
	matrixOperation_ = operation;
	matrixRows_ = rowsMax;
	matrixColumns_ = colsMax;
}

void Scenarios::copyAndShuffleOperations(int countO, Array<int>* ratio)
{
	for (int i = 0; i < (countO / OPERATIONS_RATIO); i++)
	{
		Array<int>::copy(*ratio, 0, *operations_, i * OPERATIONS_RATIO, OPERATIONS_RATIO);
	}
	
	std::random_shuffle(&(*operations_)[0], &(*operations_)[countO - 1]);
}

void Scenarios::readFromFile(fstream& newfile, const char* fileName)
{
	string line;
	while (getline(newfile, line)) {

		structuresList_->add(atoi(line.c_str()));
		getline(newfile, line);
		scenariosList_->add(*line.c_str());
		getline(newfile, line);
		operationsCount_->add(atoi(line.c_str()));
		getline(newfile, line);
		firstGroupOperations_->add(atoi(line.c_str()));
		getline(newfile, line);
		secondGroupOperations_->add(atoi(line.c_str()));
		getline(newfile, line);
		thirdGroupOperations_->add(atoi(line.c_str()));
		getline(newfile, line);
		fourthGroupOperations_->add(atoi(line.c_str()));
		getline(newfile, line);
	}
}

void Scenarios::clearAllLists()
{
	structuresList_->clear();
	scenariosList_->clear();
	operationsCount_->clear();
	firstGroupOperations_->clear();
	secondGroupOperations_->clear();
	thirdGroupOperations_->clear();
	fourthGroupOperations_->clear();
}

Scenarios::~Scenarios()
{
	if (operations_ != nullptr)
	{
		delete operations_;
	}

	matrixRows_ = 0;
	matrixColumns_ = 0;
	matrixOperation_ = -1;

	delete scenariosList_;
	scenariosList_ = nullptr;
	delete structuresList_;
	structuresList_ = nullptr;
	delete operationsCount_;
	operationsCount_ = nullptr;
	delete firstGroupOperations_;
	firstGroupOperations_ = nullptr;
	delete secondGroupOperations_;
	secondGroupOperations_ = nullptr;
	delete thirdGroupOperations_;
	thirdGroupOperations_ = nullptr;
	delete fourthGroupOperations_;
	fourthGroupOperations_ = nullptr;
}