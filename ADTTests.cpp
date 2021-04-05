#include <iostream>
#include <algorithm>

#include "structures/heap_monitor.h"
#include "ADTTests.h"
#include "Test.h"
#include "ScenariosMatrix.h"
#include "ScenariosOther.h"
#include "ScenariosOtherBitMap.h"
#include "structures/list/linked_list.h"


using namespace std;

ADTTests::ADTTests()
{
	scenariosForADT_ = new LinkedList<string>();
}

// menu metoda, ma cyklus ktory bezi a vola vyber(+nacitanie)/vytvorenie scenara a vypis tabuliek a testovanie struktury, bez kym ho pouzivatel neukonci 
void ADTTests::testStructureFromFile()
{
	
	fstream* reader = new fstream();
	string fileName;
	string input;
	string folder;
	string path;
	int structure;

	char runningApp = 'y';

	while (runningApp == 'y')
	{
		Scenarios* scen = nullptr;
		cout << "_________________________________" << endl;
		cout << "+---------------+---------------+" << endl;
		cout << "|     Test      |      ADT      |" << endl;
		cout << "+---------------+---------------+" << endl;
		cout << "|       0       |      List     |" << endl;
		cout << "+---------------+---------------+" << endl;
		cout << "|       1       | PriorityQueue |" << endl;
		cout << "+---------------+---------------+" << endl;
		cout << "|       2       |     Matrix    |" << endl;
		cout << "+---------------+---------------+" << endl;
		cout << "|       3       |      Set      |" << endl;
		cout << "+-------------------------------+" << endl;
		cout << "Vyberte cislo ADT pre testovanie: ";
		cin >> structure;

		while (structure < 0 || structure > 3)
		{
			cout << "Zadany ADT neexistuje! Vyberte inu moznost: ";
			cin >> structure;
		}

		switch (structure)
		{
		case 0:
			folder = "list/";
			input = "savedListScenarios.txt";
			break;
		case 1:
			folder = "priorityQueue/";
			input = "savedPriorityQueueScenarios.txt";
			break;
		case 2:
			folder = "matrix/";
			input = "savedMatrixScenarios.txt";
			break;
		case 3:
			folder = "set/";
			input = "savedSetScenarios.txt";
			break;
		default:
			folder = "";
			input = "";
			break;
		}

		path = "scenarios/" + folder + input;

		int fileFound = scenariosTable(path, folder, structure);
		if (fileFound == -1)
		{
			delete reader;
			throw logic_error("Subor pre scenare nebol najdeny!");
		}

		cout << "Zadajte nazov scenaru pre testovanie: ";
		cin >> input;

		;
		while (scenariosForADT_->getIndexOf(input) == -1 &&  input != "novy")
		{
			cout << "Zadany scenar neexistuje! Zadajte nazov scenaru: ";
			cin >> input;
		}

		if (input == "novy")
		{
			scen = newScenario(structure);
		}
		else
		{
			string type;
			string number;
			int operationData = 0;
			int minBase = 0, maxBase = 100;
			Array<short int>* ratio = nullptr;
			path = "scenarios/" + folder + input + ".txt";

			reader->open(path);

			if (reader->fail())
			{
				delete reader;
				throw logic_error("Scenar sa nenasiel!");
			}

			getline(*reader, type);

			if (type.compare("set") == 0) {
				getline(*reader, number);
				minBase = stoi(number);
				getline(*reader, number);
				maxBase = stoi(number);
			}

			getline(*reader, number);
			operationData = stoi(number);

			if (type.compare("list") == 0) {
				ratio = new Array<short int>(4);
			}
			if (type.compare("priorityQueue") == 0) {
				ratio = new Array<short int>(3);
			}
			if (type.compare("matrix") == 0) {
				ratio = new Array<short int>(3);
			}
			if (type.compare("set") == 0) {
				ratio = new Array<short int>(8);
			}

			if (ratio != nullptr)
			{
				for (int i = 0; i < ratio->size(); i++) {
					getline(*reader, number);
					(*ratio)[i] = stoi(number);
				}
			}

			reader->close();
			if (structure == 2)
			{
				scen = new ScenariosMatrix(ratio, operationData);
			}
			else if (structure == 3)
			{
				scen = new ScenariosOtherBitMap(ratio, operationData, minBase, maxBase);
			}
			else
			{
				scen = new ScenariosOther(ratio, operationData, structure);
			}
		}

		if (scen != nullptr)
		{
			testForStructure(scen);

		}


		while(true)
		{
			cout << "Chcete pokracovat v testovani? (y/n): ";
			cin >> runningApp;
			if (runningApp == 'y' || runningApp == 'n')
			{
				break;
			}
		}

		delete scen;
	}
	

	delete reader;
}

// zavola vytvorenie scenara podla typu, handluje ukladanie scenara a  zapis nazvu scenara do suboru vsetkych scenarov pre dany adt
Scenarios* ADTTests::newScenario(int type)
{
	int number;
	string folder, input, fileName;
	Scenarios* scen;
	fstream* reader = new fstream();
	cout << "__________________________________________________" << endl;

	
	if (type == 2)
	{
		scen = createScenarioMatrix();	
	}
	else
	{
		scen = createScenario(type);
	}

	cout << "Chcete vytvoreny scenar ulozit? (0 - ano, 1 - nie): ";
	cin >> number;
	if (number == 0)
	{
		cout << "Zadajte nazov pre ulozenie scenara (max 12 znakov): ";
		cin >> fileName;
		fileName = fileName.substr(0, 12);
		string folder = scen->saveScenario(fileName);

		switch (scen->getType())
		{
		case list:
			input = "savedListScenarios.txt";
			break;
		case priorityQueue:
			input = "savedPriorityQueueScenarios.txt";
			break;
		case matrix:
			input = "savedMatrixScenarios.txt";
			break;
		case set:
			input = "savedSetScenarios.txt";
			break;
		default:
			break;
		}
		string path = "scenarios/" + folder + input;

		reader->open(path, fstream::app);
		*reader << fileName << endl;
		reader->close();
	}


	delete reader;
	return scen;
}

//vytvorenie scenara pre maticu
Scenarios* ADTTests::createScenarioMatrix()
{
	Array<short int>* matrixParameters = new Array<short int>(3);

	int operationToPerform = 0;
	(*matrixParameters)[0] = 0;
	(*matrixParameters)[1] = 0;
	(*matrixParameters)[2] = -1;
	cout << "Zadajte operaciu ktoru chcete vykonat (0 - sucet, 1 - sucin): ";
	cin >> operationToPerform;
	while (operationToPerform != 0 && operationToPerform != 1)
	{
		cout << "Vybrana operacia neexistuje! Vyberte inu operaciu: ";
		cin >> operationToPerform;
	}

	cout << "Testovanie prebieha tak, ze jeden rozmer matice je konstantny, kym druhy je variabilny od 1 po zvolenu hodnotu" << endl;
	cout << "v zvolenych intervaloch. Testuje sa teda M-variabilny N-konstantny a nasledne naopak." << endl;
	while ( ((*matrixParameters)[0] <= 0 || (*matrixParameters)[1] <= 0 || (*matrixParameters)[2] <= 0) || ((*matrixParameters)[1] % (*matrixParameters)[2] != 0) )
	{
		cout << "Zadajte konstantny rozmer matice:  ";
		cin >> (*matrixParameters)[0];

		cout << "Zadajte maximalny variabilny rozmer matice:  ";
		cin >> (*matrixParameters)[1];

		cout << "Zadajte velkost intervalu pre variabilny rozmer:  ";
		cin >> (*matrixParameters)[2];

		if ((*matrixParameters)[0] <= 0 || (*matrixParameters)[1] <= 0 || (*matrixParameters)[2] <= 0)
		{
			cout << "Niektory z rozmerov je zly! Zadajte ine rozmery: " << endl;;
		}
		if ((*matrixParameters)[2] != 0)
		{
			if ((*matrixParameters)[1] % (*matrixParameters)[2] != 0)
			{
				cout << "Maximalny variabilny rozmer musi byt delitelny velkostou kroku!" << endl;
			}
		}
		else
		{
			cout << "Krok nemoze byt nulovy!" << endl;
			(*matrixParameters)[2] = -1;
		}

	}
	return new ScenariosMatrix(matrixParameters, operationToPerform);
}

// vytvorenie scenara podla typu - list, front, set
Scenarios* ADTTests::createScenario(int type)
{
	int minBase = -1, maxBase = -1;
	if (type == 3)
	{
		while (minBase == -1 || maxBase == -1 || (minBase >= maxBase))
		{
			cout << "Zadajte minimalnu velkost bazovej mnoziny: ";
			cin >> minBase;
			cout << "Zadajte maximalnu velkost bazovej mnoziny: ";
			cin >> maxBase;

			if (minBase < 0 || maxBase < 0 || (minBase >= maxBase))
			{
				cout << "Niektore udaje boli zadane zle! Minimum a maximum musia byt aspon 0 a zaroven minimum musi byt mensie ako maximum!" << endl;
			}
		}

	}

	cout << "Zadajte celkovy pocet operacii: " ;
	int operationsCount;
	cin >> operationsCount;

	while (operationsCount % 100 != 0)
	{
		cout << "Pocet operacii musi byt delitelny 100: ";
		cin >> operationsCount;
	}

	int number = type == 0 ? 4 : type == 1 ? 3 : 8;
	int sum = 0;
	if (type == 0)
	{
		cout << "Druh operacii: 0 - vloz, 1 - zrus, 2 - get/set, 3 - index" << endl;
	}
	else if (type == 1)
	{
		cout << "Druh operacii: 0 - vloz, 1 - vyber, 2 - ukaz" << endl;
	}
	else
	{
		cout << "Druh operacii: 0 - vloz, 1 - odober, 2 - patri, 3 - je rovna" << endl;
		cout << "4 - je podmnozinou, 5 - zjednotenie, 6 - prienik, 7 - rozdiel" << endl;
	}
	Array<short int>* ratio = new Array<short int>(number);
	while (sum != 100)
	{
		sum = 0;
		for (int i = 0; i < number; i++) {
			cout << "Zadajte pocet % operacie " << i << ".: ";
			cin >> (*ratio)[i];
			sum += (*ratio)[i];
		}
		if (sum != 100)
		{
			cout << "Sucet % musi byt rovny 100!" << endl;
		}
	}
	if (type == 3)
	{
		return new ScenariosOtherBitMap(ratio, operationsCount, minBase, maxBase);
	}
	else
	{
		return new ScenariosOther(ratio, operationsCount, type);
	}
}

// vytvorenie instancie pre Test podla vybranej struktury, zavolanie metody test pre strukturu - TESTOVACIA METODA
void ADTTests::testForStructure(Scenarios* scenario)
{
	int number;
	structureTypes type = scenario->getType();
	
	testsTable(type);
	cin >> number;

	Test<int>* test = nullptr;
	switch (type)
	{
	case list:
		switch (number)
		{
		case 0:
			test = new TestArrayList<int>();
			break;
		case 1:
			test = new TestLinkedList<int>();
			break;
		case 2:
			test = new TestBidirectionalCyclicLinkedList<int>();
			break;
		default:
			cout << "Zadany typ neexistuje! Vyberte iny: ";
			testForStructure(scenario);
			break;
		}
		break;

	case priorityQueue:
		switch (number)
		{
		case 0:
			test = new TestHeap<int>();
			break;
		case 1:
			test = new TestPriorityQueueSortedArrayList<int>();
			break;
		case 2:
			test = new TestTwoListsLimitedCapacity<int>(((*(scenario->getDataFromFile()))[0] * scenario->getOperationData()) / 1000 );
			break;
		case 3:
			test = new TestTwoListsSqrtCapacity<int>();
			break;
		case 4:
			test = new TestTwoListsHalfCapacity<int>();
			break;
		default:
			cout << "Zadany typ neexistuje! Vyberte iny: ";
			testForStructure(scenario);
			break;
		}
		break;

	case matrix:
		switch (number)
		{
		case 0:
			test = new TestCoherentMatrix<int>();
			break;

		case 1:
			test = new TestIncoherentMatrix<int>();
			break;
		default:
			cout << "Zadany typ neexistuje! Vyberte iny: ";
			testForStructure(scenario);
			break;
		}
		break;

	case set:
		switch (number)
		{
		case 0:
			test = new TestBitmap();
			break;

		default:
			cout << "Zadany typ neexistuje! Vyberte iny: ";
			testForStructure(scenario);
			break;
		}
		break;

	default:
		break;
	}

	if (test != nullptr)
	{
		test->test(scenario);
	}

	delete test;


	test = nullptr;
}


// vypis tabuliek struktur ktore mozno testovat
void ADTTests::testsTable(structureTypes type)
{
	switch (type)
	{
		case list:
			cout << "_________________________________" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|     Test      |      ADS      |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       0       |   ArrayList   |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       1       |  LinkedList   |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       2       | BCLinkedList  |" << endl;
			cout << "+-------------------------------+" << endl;
			break;

		case priorityQueue:
			cout << "_________________________________" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|     Test      |      ADS      |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       0       |     Heap      |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       1       | PQSArrayList  |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       2       | 2Lists 1/1000 |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       3       | 2Lists sqrt(n)|" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       4       |  2Lists n/2   |" << endl;
			cout << "+-------------------------------+" << endl;
			break;

		case matrix:
			cout << "_________________________________" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|     Test      |      ADS      |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       0       |  CoherMatrix  |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       1       | IncoherMatrix |" << endl;
			cout << "+-------------------------------+" << endl;
			break;

		case set:
			cout << "_________________________________" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|     Test      |      ADS      |" << endl;
			cout << "+---------------+---------------+" << endl;
			cout << "|       0       |     BitMap    |" << endl;
			cout << "+-------------------------------+" << endl;
			break;
		
		default:
			break;
	}
	cout << "Vyber cislo ADS pre testovanie: ";
}

// otvori si subory pre nacitanie scenarov a ich detailov, vypise na konzolu, vrati -1 ked nenajde subor so vsetkymi scenarmi
int ADTTests::scenariosTable( string path, string folder, int structure)
{
	fstream* reader = new fstream();
	fstream* reader2 = new fstream();
	string line;

	reader->open(path);

	if (reader->fail())
	{
		delete reader;
		delete reader2;
		return -1;
	}

	if (structure == 0)
	{
		cout << "_________________________________________________________________________________________________" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "|     Nazov     | Pocet operacii|      Vloz     |     Zrus      |   Spristupni  |     Index     |" << endl;
	}
	if (structure == 1)
	{
		cout << "_________________________________________________________________________________" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "|     Nazov     | Pocet operacii|      Vloz     |     Vyber     |      Ukaz     |" << endl;
	}
	if (structure == 2)
	{
		cout << "_________________________________________________________________________________" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "|     Nazov     |    Operacia   |   Konstantny  |   Variabilny  |      Krok     |" << endl;
	}
	if (structure == 3)
	{
		cout << "_______________________________________________________________________________________________________________________" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|     Nazov     |  MinB |     MaxB      |  Pocet oper.  | Vloz  | Odob  | Patri | Rovna | Podmn | Zjedn | Prien | Rozd |" << endl;

	}

	while (getline(*reader, line)) {
		scenariosForADT_->add(line);
		switch (structure)
		{
		case 0:
			cout << "+---------------+---------------+---------------+---------------+---------------+---------------+" << endl;
			break;
		case 1: case 2:
			cout << "+---------------+---------------+---------------+---------------+---------------+" << endl;
			break;
		case 3:
			cout << "+---------------+-------+---------------+---------------+-------+-------+-------+-------+-------+-------+-------+------+" << endl;
					 
			break;
		default:
			break;
		}

		cout << "|  " << line << "\t|   ";
		reader2->open("scenarios/" + folder + line + ".txt");

		if (structure != 3)
		{
			getline(*reader2, line);
			if (line == "matrix")
			{
				getline(*reader2, line);
				cout << (line == "0" ? "sucet" : "sucin") << "\t|\t";
			}
			while (getline(*reader2, line)) {
				cout << line << "\t|\t";
			}
			cout << endl;
		}
		else
		{
			getline(*reader2, line);
			getline(*reader2, line);
			cout << line << "\t| ";
			getline(*reader2, line);
			cout << line << "   \t| ";
			getline(*reader2, line);
			cout << line << "    \t|";
			while (getline(*reader2, line)) {
				cout << line << "\t|";
			}
			cout << endl;
		}
		
		reader2->close();

	}
	reader->close();

	switch (structure)
	{
	case 0:
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "|                        Pre vytvorenie vlastneho scenara zadajte 'novy'                        |" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;

		break;
	case 1: case 2:
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "|                 Pre vytvorenie vlastneho scenara zadajte 'novy'               |" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;

		break;

	case 3:
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                   Pre vytvorenie vlastneho scenara zadajte 'novy'                                    |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		break;
	default:
		break;
	}

	delete reader;
	delete reader2;
	return 0;
}


ADTTests::~ADTTests()
{
	delete scenariosForADT_;
	scenariosForADT_ = nullptr;
}
