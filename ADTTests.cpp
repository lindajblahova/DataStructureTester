#include "ADTTests.h"

ADTTests::ADTTests()
{
	testsList_ = new LinkedList<int>();
	ADTToTest_ = new LinkedList<int>();
	firstADSToTest_ = new LinkedList<int>();
	secondADSToTest_ = new LinkedList<int>();
}

void ADTTests::chooseStructure()
{
	int structureToTest = -1;
	Scenarios* scenario = nullptr;
	char runTester = 'y';

	const char* fileName = "adttests.txt";
	fstream structuresFile(fileName);

	const char* adt = "default";
	const char* ads1 = "default";
	const char* ads2 = "default";

	readFromFile(structuresFile, fileName);
	structuresFile.close();

	while (runTester == 'y')
	{
		system("CLS");
		cout << "_________________________________________________________________" << endl;
		cout << "+---------------+---------------+---------------+---------------+" << endl;
		cout << "|     Test      |      ADT      |     ADS 1     |     ADS 2     |" << endl;

		for (int i = 0; i < testsList_->size(); i++)
		{
			adt = getADTName((*ADTToTest_)[i], (*firstADSToTest_)[i]);
			ads1 = getADSName((*ADTToTest_)[i], (*firstADSToTest_)[i]);
			ads2 = getADSName((*ADTToTest_)[i], (*secondADSToTest_)[i]);

			cout << "+---------------+---------------+---------------+---------------+" << endl;
			cout << "|\t" << (*testsList_)[i] << "\t|   " << adt << "\t| " << ads1 << "\t| "
				 << ((*secondADSToTest_)[i] == -1 ? "\t-" : ads2) << "\t|" << endl;

		}
		cout << "+---------------+---------------+---------------+---------------+" << endl;
		cout << "|            Pre vytvorenie vlastneho testu zadajte 99          |" << endl;
		cout << "+---------------------------------------------------------------+" << endl;

		cout << "Zadajte cislo testu, ktory chcete vykonat: ";
		cin >> structureToTest;
		bool chosen = false, created = false;
		int index = 0;

		while (chosen == false)
		{
			if (structureToTest == 99)
			{
				structuresFile.open(fileName, fstream::app);
				structureToTest = createStructureTest(structuresFile, (*testsList_)[testsList_->size() - 1]);
				structuresFile.close();

				clearAllLists();

				structuresFile.open(fileName);
				readFromFile(structuresFile, fileName);
				structuresFile.close();
				created = true;
			}

			if (structureToTest > -1 && structureToTest < testsList_->size())
			{
				index = testsList_->getIndexOf(structureToTest);
				chosen = true;
				
			}
			
			if (chosen == false && created == false)
			{
				cout << "Zadany ADT neexistuje! Vyberte inu moznost: ";
				cin >> structureToTest;
			}

		}

		int adtToTest = (*ADTToTest_)[index];
		int asdToTest1 = (*firstADSToTest_)[index];
		int asdToTest2 = (*secondADSToTest_)[index];

		scenario = new Scenarios();
		scenario->chooseScenario(adtToTest);

		testForStructure(scenario, adtToTest, asdToTest1);
		if (asdToTest2 != -1)
		{
			testForStructure(scenario, adtToTest, asdToTest2);
		}
		


		cout << "---------------------------------------------------------------" << endl;

		while (true)
		{
			cout << "Chcete testovat dalsie ADT? (y/n)" << endl;
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
}

int ADTTests::createStructureTest(fstream& newfile, int lastStructure)
{
	int adt = -1, ads1 = -1, ads2 = -1, tested = 2;
	while (true)
	{
		cout << "Zadajte ADT ktory chcete testovat (0 - List, 1 - PriortyQueue, 2 - Matrix) : ";
		cin >> adt;
		while (true)
		{
			if (adt > -1 && (ADTToTest_->getIndexOf(adt) != -1))
			{
				break;
			}
			else
			{
				cout << "Zadany ADT neexistuje ! Vyberte iny ADT: ";
				cin >> adt;
			}
			
		}
		cout << "Zadajte pocet testovanych struktur (1 - jedna, 2 - dve): ";
		cin >> tested;
		while (true)
		{
			if (tested > 0 && tested < 3)
			{
				break;
			}
			else
			{
				cout << "Mozte testovat iba 1 alebo 2 struktury! Zadajte pocet: ";
				cin >> tested;
			}

		}
		cout << "Struktury ktore mozno testovat ";
		switch (adt)
		{
		case 0:
			cout << "(0 - ArrayList, 1 - LinkedList, 2 - BidirectionalCyclicLinkedList) :" << endl;
			break;
		case 1:
			cout << "(0 - Heap, 1 - PriorityQueueSortedArrayList) :" << endl;
			break;
		case 2:
			cout << "(0 - CoherentMatrix, 1 - IncoherentMatrix) :" << endl;
			break;
		default:
			break;
		}
		cout << "Zadajte prvu strukturu pre testovanie: ";
		cin >> ads1;
		if (tested == 2)
		{
			cout << "Zadajte druhu strukturu pre testovanie: ";
			cin >> ads2;
		}
	
		if ((ads1 >= 0 && tested == 1 ) || (ads1 >= 0 && ads2 >= 0 && tested == 2))
		{
			break;
		}
		cout << "Niektore zadane udaje boli neplatne!" << endl;
	}

	if (lastStructure == 99)
	{
		++lastStructure;
	}
	newfile << ++lastStructure << endl;
	newfile << adt << endl;
	newfile << ads1 << endl;
	newfile << ads2 << endl;
	newfile << ";" << endl;

	return lastStructure;
}

void ADTTests::testForStructure(Scenarios* scenario, int adt, int ads1)
{
	TestArrayList<int> testAL;
	TestLinkedList<int> testLL;
	TestBidirectionalCyclicLinkedList<int> testBCLL;
	TestHeap<int> testH;
	TestPriorityQueueSortedArrayList<int> testPQSAL;
	TestCoherentMatrix<int> testCM;
	TestIncoherentMatrix<int> testIM;


	switch (adt)
	{
	case 0: case 3:
		switch (ads1)
		{
		case 0:
			cout << "Testujem ArrayList..." << endl;
			testAL.test(scenario);
			break;
		case 1:
			cout << "Testujem LinkedList..." << endl;
			testLL.test(scenario);
			break;
		case 2:
			cout << "Testujem BidirectionalCyclicLinkedList..." << endl;
			testBCLL.test(scenario);
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (ads1)
		{
		case 0:
			cout << "Testujem Heap..." << endl;
			testH.test(scenario);
			break;
		case 1:
			cout << "Testujem TestPriorityQueueSortedArrayList..." << endl;
			testPQSAL.test(scenario);
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (ads1)
		{
		case 0:
			cout << "Testujem CoherentMatrix..." << endl;
			testCM.test(scenario);
			break;
		case 1:
			cout << "Testujem TestIncoherentMatrix..." << endl;
			testIM.test(scenario);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	testAL.~TestArrayList();
	testLL.~TestLinkedList();
	testBCLL.~TestBidirectionalCyclicLinkedList();
	testH.~TestHeap();
	testPQSAL.~TestPriorityQueueSortedArrayList();
	testCM.~TestCoherentMatrix();
	testIM.~TestIncoherentMatrix();
}

const char* ADTTests::getADTName(int adt, int ads)
{
	const char* adtName = "default";
	switch (adt)
	{
	case 0:
		adtName = "List";
		break;
	case 1:
		adtName = "Prior.Queue";
		break;
	case 2:
		adtName = "Matrix";
		break;
	default:
		break;
	}
	getADSName(adt, ads);
	return adtName;
}

const char* ADTTests::getADSName(int adt, int ads)
{
	const char* adsName = "default";
	switch (adt)
	{
	case 0:
		switch (ads)
		{
		case 0:
			adsName = "ArrayList";
			break;
		case 1:
			adsName = "LinkedList";
			break;
		case 2:
			adsName = "BCLinkedList";
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (ads)
		{
		case 0:
			adsName = "Left.Heap";
			break;
		case 1:
			adsName = "PQSortedAL";
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (ads)
		{
		case 0:
			adsName = "Coher.Matrix";
			break;
		case 1:
			adsName = "Incoh.Matrix";
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return adsName;
}

void ADTTests::readFromFile(fstream& newfile, const char* fileName)
{
	string line;
	while (getline(newfile, line)) {

		testsList_->add(atoi(line.c_str()));
		getline(newfile, line);
		ADTToTest_->add(atoi(line.c_str()));
		getline(newfile, line);
		firstADSToTest_->add(atoi(line.c_str()));
		getline(newfile, line);
		secondADSToTest_->add(atoi(line.c_str()));
		getline(newfile, line);
	}
}

void ADTTests::clearAllLists()
{
	testsList_->clear();
	ADTToTest_->clear();
	firstADSToTest_->clear();
	secondADSToTest_->clear();
}

ADTTests::~ADTTests()
{
	delete testsList_;
	testsList_ = nullptr;
	delete ADTToTest_;
	ADTToTest_ = nullptr;
	delete firstADSToTest_;
	firstADSToTest_ = nullptr;
	delete secondADSToTest_;
	secondADSToTest_ = nullptr;
}
