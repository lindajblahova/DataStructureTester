#pragma once

#include <iostream>

#include "structures/heap_monitor.h"
#include "Scenarios.h"
#include "ScenariosMatrix.h"
#include "structures/matrix/matrix.h"
#include "Test.h"

using namespace std;

template<typename T>
class TestMatrix : public Test<T>
{
public:

	TestMatrix();
	void test(Scenarios* scenario) override;

	~TestMatrix();

protected:
	virtual Matrix<T>* newStructure(size_t rows, size_t columns, T& data) = 0;
	virtual string getFileName() = 0;
	virtual string getName() = 0;

private:

	void fileStream(ofstream& file, string operation, int rows, int columns, int time);
	void testMatrix(ofstream& file, int operation, int i, int j);

};

template<typename T>
inline TestMatrix<T>::TestMatrix() : Test<T>()
{
}

// vola vytvorenie struktury cez newStructure a dostane jej nasov csv suboru cez getFileName a skratku struktury cez getName
// vykonava testovanie struktury podla scenara
// cele testovanie prebehne 5x pre ziskanie aspon trochu priemernych vysledkov, nie len z 1 behu
// vola sa metoda testMatrix - TESTOVACIA METODA
// testovanie sa vyknava pre parametre obojstranne - [Variab][Const] a [Const][Variab]
// char ktory sa vypisuje je pocitadlo
template<typename T>
inline void TestMatrix<T>::test(Scenarios* scenario)
{
	const char SIGN = 176;

	ScenariosMatrix* scen = dynamic_cast<ScenariosMatrix*>(scenario);
	string fileName = getFileName();

	ofstream* newfile = new ofstream();
	newfile->open(fileName);

	int constant = scen->getConstValue();
	int step = scen->getStep();
	int operation = scen->getOperationData();
	int maxVal = scen->getVariableValue();

	int differ = maxVal / 100;   //  vypocitavam pre vypisovanie pocitadla
	differ *= 10; // 2*5
	int remains = maxVal % 100;

	if (remains == 0 && differ != 0)
	{
		cout << "0%\t\t\t\t\t\t50%\t\t\t\t\t\t100%" << endl;
	}
	else
	{
		cout << "Testujem...";
	}
	for (int k = 0; k < 5; k++)
	{
		for (int i = 1; i <= maxVal; i++)
		{
			if (i % step == 0)
			{
				testMatrix(*newfile, operation, i, constant);
			}
			if (differ != 0 && remains == 0 && i % differ == 0)
			{
				cout << SIGN;
			}
		}

		for (int j = 1; j <= maxVal; j++)
		{
			if (j % step == 0)
			{
				testMatrix(*newfile, operation, constant, j);
			}
			if (differ != 0 && remains == 0 && j % differ == 0)
			{
				cout << SIGN;
			}
		}
	}
	
	cout <<  endl;

	newfile->close();

	delete newfile;
	newfile = nullptr;

	cout << "Vysledky su ulozene v subore " << fileName << endl;

}

// zapisuje udaje z testu do suboru
template<typename T>
inline void TestMatrix<T>::fileStream(ofstream& newfile, string operation,int rows, int columns, int time)
{
	newfile << getName() << ",";
	newfile << operation << ",";
	newfile << rows << ",";
	newfile << columns << ",";
	newfile << time;
	newfile << endl;
}

// testovacia metoda rozhodne sa kotry typ operacie sa vykona 0-sucet, 1-sucin
// vytvori nove matice - 2 operandy a jednu do ktorej zapisuje vysledok, podla potrebnych velkosti (scitanie vsetky su MxN, nasobenie MxN , NxM a M*M )
// zavola maticovu operaciu (addition/multiplication)
// zavola metodu filestream pre zapis do suboru
template<typename T>
inline void TestMatrix<T>::testMatrix(ofstream& file, int operation, int i, int j )
{
	T data = 1;
	chrono::high_resolution_clock::time_point startTime, endTime;
	int duration;
	Matrix<T>* matrix1;
	Matrix<T>* matrix2;
	Matrix<T>* matrixResult;

	switch (operation)
	{
	case 0:
		matrix1 = newStructure(i, j, data);
		matrix2 = newStructure(i, j, data);
		matrixResult = newStructure(i, j, data);
		startTime = chrono::high_resolution_clock::now();
		matrix1->addition(matrix2, matrixResult);
		endTime = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
		fileStream(file, "sucet" ,matrix1->getRows(), matrix1->getColumns(), duration);
		delete matrix1;
		delete matrix2;
		delete matrixResult;
		break;

	case 1:
		matrix1 = newStructure(i, j, data);
		matrix2 = newStructure(j, i, data);
		matrixResult = newStructure(i, i, data);
		startTime = chrono::high_resolution_clock::now();
		matrix1->multiplication(matrix2, matrixResult);
		endTime = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		fileStream(file, "sucin", matrix1->getRows(), matrix1->getColumns(), duration);
		delete matrix1;
		delete matrix2;
		delete matrixResult;
		break;

	default:
		break;
	}

}

template<typename T>
inline TestMatrix<T>::~TestMatrix()
{
}