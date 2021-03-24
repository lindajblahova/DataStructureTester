#pragma once

#include <iostream>
#include "Scenarios.h"
#include "structures/matrix/matrix.h"


using namespace std;

template<typename T>
class TestMatrix
{
public:

	TestMatrix();
	void test(Scenarios* scenario);
	void matrixAddition(Matrix<T>* m1, Matrix<T>* m2, Matrix<T>* result, ofstream& newfile);
	void matrixMultiplication(Matrix<T>* m1, Matrix<T>* m2, Matrix<T>* result, ofstream& newfile);

	~TestMatrix();

private:

	virtual Matrix<T>* newStructure(size_t rows, size_t columns, T& data) = 0;
	virtual const char* getFileName() = 0;

};

template<typename T>
inline TestMatrix<T>::TestMatrix()
{
}

template<typename T>
inline void TestMatrix<T>::test(Scenarios* scenario)
{
	const char* fileName = getFileName();

	ofstream newfile;
	newfile.open(fileName);

	T data = 1;

	for (int i = 1; i <= scenario->getRows(); i++)
	{
		for (int j = 1; j <= scenario->getColumns(); j++)
		{
			Matrix<T>* matrix1;
			Matrix<T>* matrix2;
			Matrix<T>* matrixResult;
			switch (scenario->getMatrixOperation())
			{

			case 0:
				matrix1 = newStructure(i, j, data);
				matrix2 = newStructure(i, j, data);
				matrixResult = newStructure(i, j, data);
				matrixAddition(matrix1, matrix2, matrixResult, newfile);
				delete matrix1;
				delete matrix2;
				delete matrixResult;
				break;

			case 1:
				matrix1 = newStructure(i, j, data);
				matrix2 = newStructure(j, i, data);
				matrixResult = newStructure(i, i, data);
				matrixMultiplication(matrix1, matrix2, matrixResult, newfile);
				delete matrix1;
				delete matrix2;
				delete matrixResult;
				break;

			default:
				break;
			}
		}
	}

	newfile.close();

	cout << "Vysledky su ulozene v subore " << fileName << endl;
}

template<typename T>
inline void TestMatrix<T>::matrixAddition(Matrix<T>* matrix1, Matrix<T>* matrix2, Matrix<T>* resultMatrix, ofstream& newfile)
{
	
	T dataM1;
	T dataM2;
	T result;
	chrono::high_resolution_clock::time_point startTime, endTime;

	startTime = chrono::high_resolution_clock::now();
	for (int i = 0; i < matrix1->getRows(); i++)
	{
		for (int j = 0; j < matrix1->getColumns(); j++)
		{
			dataM1 = matrix1->getDataOnIndex(i, j);
			dataM2 = matrix2->getDataOnIndex(i, j);
			result = dataM1 + dataM2;
			resultMatrix->setDataOnIndex(i, j, result);
		}
	}
	endTime = chrono::high_resolution_clock::now();


	newfile << matrix1->getRows() << ",";
	newfile << matrix1->getColumns() << ",";
	newfile << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() ;
	newfile << endl;
}

template<typename T>
inline void TestMatrix<T>::matrixMultiplication(Matrix<T>* matrix1, Matrix<T>* matrix2, Matrix<T>* resultMatrix, ofstream& newfile)
{
		// nasobenie matic
	//  00 01  x  00 01 02  =  00*00+01*10    00*01+01*11    00*02+01*12
	//  10 11  x  10 11 12     10*00+11*10    10*01+11*11    10*02+11*12
	//  20 21                  20*00+21*10    20*01+21*11    20*02+21*12

	chrono::high_resolution_clock::time_point startTime, endTime;
	T dataM1;
	T dataM2;
	T result;
	startTime = chrono::high_resolution_clock::now();
	for (int i = 0; i < resultMatrix->getRows(); i++) 
	{
		for (int j = 0; j < resultMatrix->getColumns(); j++)
		{
			result = 0;
			for (int k = 0; k < matrix1->getColumns(); k++)
			{
				dataM1 = matrix1->getDataOnIndex(i, k);
				dataM2 = matrix2->getDataOnIndex(k, j);
				result += dataM1 * dataM2;
			}

			resultMatrix->setDataOnIndex(i, j, result);
		}
	}
	endTime = chrono::high_resolution_clock::now();


	newfile << matrix1->getRows() << ",";;
	newfile << matrix1->getColumns() << ",";;
	newfile << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
	newfile << endl;
}


template<typename T>
inline TestMatrix<T>::~TestMatrix()
{
}
