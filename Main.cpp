#include <iostream>
#include "structures/vector/vector.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "Scenarios.h"
#include "Tests.h"


using namespace structures;
using namespace std;

int main()
{
	initHeapMonitor();
	int structureToTest = -1;
	char scenarioToTest = 'z';
	const char* fileName = "default.csv";
	const char* testing = "Prebieha test struktury...";
	Scenarios* scenario = nullptr;
	char runTester = 'y';

	srand(time(NULL));

	while (runTester == 'y')
	{
		cout << "Struktury ktore mozno testovat:" << endl;
		cout << "_____________________" << endl;
		cout << "+---+---------------+" << endl;
		cout << "| 0 |   ArrayList   |" << endl;
		cout << "+---+---------------+" << endl;
		cout << "| 1 |  LinkedList   |" << endl;
		cout << "---------------------" << endl;
		cout << "Zadajte cislo struktury ktoru chcete testovat:" << endl;
		cin >> structureToTest;

		while (true)
		{
			if (structureToTest > -1 && structureToTest < 2)
			{
				break;
			}
			cout << "Zadana struktura neexistuje! Vyberte inu strukturu:" << endl;
			cin >> structureToTest;
		}

		cout << "Vyberte scenar, ktory chcete testovat:" << endl;
		cout << "______________________________________________" << endl;
		cout << "+--------+--------+--------+--------+--------+" << endl;
		cout << "| Scenar |  Vloz  |  Zrus  | Nastav | Index  |" << endl;
		cout << "+--------+--------+--------+--------+--------+" << endl;

		switch (structureToTest)
		{
		case 0: case 1:
			cout << "|   A    |   20   |   20   |   50   |   10   |" << endl;
			cout << "+--------+--------+--------+--------+--------+" << endl;
			cout << "|   B    |   35   |   35   |   20   |   10   |" << endl;
			cout << "+--------+--------+--------+--------+--------+" << endl;
			cout << "|   C    |   45   |   45   |   5    |   5    |" << endl;
			break;

		default:
			break;
		}
		cout << "+--------+--------+--------+--------+--------+" << endl;
		cout << "Zadajte male pismeno vybraneho scenaru: " << endl;
		cin >> scenarioToTest;

		while (true)
		{
			if ((structureToTest == 0 || structureToTest == 1) &&
				(scenarioToTest == 'a') || (scenarioToTest == 'b') || (scenarioToTest == 'c'))
			{
				scenario = new Scenarios(scenarioToTest);
				break;
			}
			else
			{
				cout << "Tento scenar neexistuje! Vyberte niektory z existujucich scenarov:" << endl;
				cin >> scenarioToTest;
			}
		}

		if (structureToTest == 0)
		{
			ArrayList<int>* arrayList = new ArrayList<int>();
			fileName = "ArrayListTest.csv";
			cout << testing << endl;
			Tests<int>::ListTest(arrayList, scenario, fileName);
			cout << "Vysledky testu su ulozene v subore: " << fileName << endl;
			delete arrayList;
		}

		if (structureToTest == 1)
		{
			LinkedList<int>* linkedList = new LinkedList<int>();
			fileName = "LinkedListTest.csv";
			cout << testing << endl;
			Tests<int>::ListTest(linkedList, scenario, fileName);
			cout << "Vysledky testu su ulozene v subore: " << fileName << endl;
			delete linkedList;
		}

		cout << "---------------------------------------------------------------" << endl;

		while (true)
		{
			cout << "Chcete testovat dalsiu strukturu? (y/n)" << endl;
			cin >> runTester;
			if (runTester == 'y' || runTester == 'n')
			{
				break;
			}
		}

		if (scenario != nullptr)
		{
			delete scenario;
		}
	}



	return 0;
}