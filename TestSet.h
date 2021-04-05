#pragma once

#include <iostream>
#include <chrono>
#include "structures/heap_monitor.h"
#include "Scenarios.h"
#include "ScenariosOther.h"
#include "ScenariosOtherBitMap.h"
#include "structures/set/bitmap.h"
#include "Test.h"

using namespace std;

template <typename T>
class TestSet : public Test<T>
{
public:
	TestSet();

	void test(Scenarios* scenario) override;

	~TestSet();

private:

	virtual BitMap* newStructure(int minBase, int maxBase) = 0;
	virtual string getFileName() = 0;

};

template <typename T>
inline TestSet<T>::TestSet() : Test<T>()
{
}

// vola vytvorenie struktury cez newStructure a dostane jej nazov csv suboru cez getFileName a skratku struktury cez getName
// vykonava testovanie struktury podla scenara prechadzaju sa postupne vsetky velkosti bazovej mnoziny a pre kazde sa vykonavaju operacie ako pri listoch
// do suboru sa zapisu priemerne casy operacii pri danej velkosti bazy
// sign ktory sa vypisuje v cykle je pocitadlo ktore ukazuje % vykonaneho testu
template <typename T>
inline void TestSet<T>::test(Scenarios* scenario)
{
	
	const char SIGN = 176;

	chrono::high_resolution_clock::time_point startTime, endTime;
	ScenariosOtherBitMap* scen = dynamic_cast<ScenariosOtherBitMap*>(scenario);
	string fileName = getFileName();

	ofstream* newfile = new ofstream();
	newfile->open(fileName);
	
	const int STEP = 10; // interval v ktorom sa meni velkost bazy

	int minBase = scen->getMinBase(); // minimalna velkost bazy  ktora sa bude testovat
	int maxBase = scen->getMaxBase(); // maximalna velkost bazy ktora sa bude testovat

	int minimumOfBase = 0; // minimum bazy , maximum sa vypocitava z aktualne testovanej velkosti

	int differ = maxBase / 100;
	int remains = maxBase % 100;
	if (remains == 0 && differ != 0)
	{
		cout << "0%\t\t\t\t\t\t50%\t\t\t\t\t\t100%" << endl;
	}
	else
	{
		cout << "Testujem...";
	}

	*newfile << "VelkostBazy:" << maxBase << ",";
	*newfile << "PocetOperacii:" << scen->getOperationData() << ",";
	*newfile << "Vloz:" << scen->getDataFromFile()->operator[](0) << ",";
	*newfile << "Vyber:" << scen->getDataFromFile()->operator[](1) << ",";
	*newfile << "Patri:" <<scen->getDataFromFile()->operator[](2) << ",";
	*newfile << "JeRovnaka:" << scen->getDataFromFile()->operator[](3) << ",";
	*newfile << "JePodmnozinou:" << scen->getDataFromFile()->operator[](4) << ",";
	*newfile << "Zjednotenie:" << scen->getDataFromFile()->operator[](5) << ",";
	*newfile << "Prienik:" << scen->getDataFromFile()->operator[](6) << ",";
	*newfile << "Rozdiel:" << scen->getDataFromFile()->operator[](7);
	*newfile << endl;


	for (int i = 0;  i + minBase <= maxBase  ; i++)
	{
		if (i % STEP == 0)
		{

			BitMap* bitMap = newStructure(minimumOfBase, minBase + i );
			BitMap* otherBitMap = newStructure(minimumOfBase, minBase + i ); // pomocna baza pre operacie ako scitanie, zjednotenie, prienik
			BitMap* tmpBitmap;

			for (int j = 0; j < otherBitMap->size(); j++)
			{
				int randNumber = rand() % 2;
				randNumber == 0 ? otherBitMap->add(j) : otherBitMap->remove(j);
			}

			char sign = 176;
			bool validOperation;
			int currentSize = 0;

			int sumTimeAdd = 0;
			int sumTimeRemove = 0;
			int sumTimeIsPresent = 0;
			int sumTimeIsEqual = 0;
			int sumTimeIsSubset = 0;
			int sumTimeUnification = 0;
			int sumTimeConjunction = 0;
			int sumTimeDifference = 0;

			int countAdd = 0;
			int countRemove = 0;
			int countIsPresent = 0;
			int countIsEqual = 0;
			int countIsSubset = 0;
			int countUnification = 0;
			int countConjunction = 0;
			int countDifference = 0;


			int operationsSize = scen->getOperationData();
			for (int j = 0; j < operationsSize; j++)
			{
				currentSize = bitMap->size();
				validOperation = true;
				int generatedItem = rand() % (minBase + i - minimumOfBase);


				switch (scen->getOperation(j))
				{
				case 0:
					startTime = chrono::high_resolution_clock::now();
					bitMap->add(generatedItem);
					endTime = chrono::high_resolution_clock::now();
					sumTimeAdd += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countAdd++;
					break;

				case 1:
					startTime = chrono::high_resolution_clock::now();
					bitMap->remove(generatedItem);
					endTime = chrono::high_resolution_clock::now();
					sumTimeRemove += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countRemove++;
					break;

				case 2:
					startTime = chrono::high_resolution_clock::now();
					bitMap->isPresent(generatedItem);
					endTime = chrono::high_resolution_clock::now();
					sumTimeIsPresent += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countIsPresent++;
					break;

				case 3:
					startTime = chrono::high_resolution_clock::now();
					bitMap->isEqual(otherBitMap);
					endTime = chrono::high_resolution_clock::now();
					sumTimeIsEqual += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countIsEqual++;
					break;

				case 4:
					startTime = chrono::high_resolution_clock::now();
					bitMap->isSubSet(otherBitMap);
					endTime = chrono::high_resolution_clock::now();
					sumTimeIsSubset += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countIsSubset++;
					break;

				case 5:
					startTime = chrono::high_resolution_clock::now();
					tmpBitmap = bitMap->unification(otherBitMap);
					endTime = chrono::high_resolution_clock::now();
					delete tmpBitmap;
					sumTimeUnification += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countUnification++;
					break;

				case 6:
					startTime = chrono::high_resolution_clock::now();
					tmpBitmap = bitMap->conjunction(otherBitMap);
					endTime = chrono::high_resolution_clock::now();
					delete tmpBitmap;
					sumTimeConjunction += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countConjunction++;
					break;

				case 7:
					startTime = chrono::high_resolution_clock::now();
					tmpBitmap = bitMap->difference(otherBitMap);
					endTime = chrono::high_resolution_clock::now();
					delete tmpBitmap;
					sumTimeDifference += chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
					countDifference++;
					break;

				default:
					break;
				}

			}

			*newfile << minBase + i - minimumOfBase << ","; // velkost bazy 
			*newfile << scen->getOperationData() << ",";		// celkovy pocet operacii
			*newfile << (countAdd == 0 ? 0 : (double)(sumTimeAdd / countAdd)) << ",";
			*newfile << (countRemove == 0 ? 0 : (double)(sumTimeRemove / countRemove)) << ",";
			*newfile << (countIsPresent == 0 ? 0 : (double)(sumTimeIsPresent / countIsPresent)) << ",";
			*newfile << (countIsEqual == 0 ? 0 : (double)(sumTimeIsEqual / countIsEqual)) << ",";
			*newfile << (countIsSubset == 0 ? 0 : (double)(sumTimeIsSubset / countIsSubset)) << ",";
			*newfile << (countUnification == 0 ? 0 : (double)(sumTimeUnification / countUnification)) << ",";
			*newfile << (countConjunction == 0 ? 0 : (double)(sumTimeConjunction / countConjunction)) << ",";
			*newfile << (countDifference == 0 ? 0 : (double)(sumTimeDifference / countDifference));
			*newfile << endl;

			delete bitMap;
			delete otherBitMap;
		}

		if (differ != 0 && remains == 0 && i % differ == 0)
		{
			cout << SIGN;
		}
		
	}
	cout << endl;
	newfile->close();

	delete newfile;
	newfile = nullptr;

	cout << "Vysledky testu su ulozene v subore: " << fileName << endl;

	
}

template <typename T>
inline TestSet<T>::~TestSet()
{
}