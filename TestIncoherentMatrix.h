#pragma once
#include "structures/heap_monitor.h"
#include "structures/matrix/incoherent_matrix.h"
#include "TestMatrix.h"


template<typename T>
class TestIncoherentMatrix : public TestMatrix<T>
{
public:

	TestIncoherentMatrix();
	~TestIncoherentMatrix();

private:

	virtual Matrix<T>* newStructure(size_t rows, size_t columns, T& data) override;
	string getFileName() override;
	string getName() override;

};

template<typename T>
inline TestIncoherentMatrix<T>::TestIncoherentMatrix() : TestMatrix<T>()
{
}

template<typename T>
inline TestIncoherentMatrix<T>::~TestIncoherentMatrix()
{
}

template<typename T>
inline Matrix<T>* TestIncoherentMatrix<T>::newStructure(size_t rows, size_t columns, T& data)
{
	return new IncoherentMatrix<T>(rows, columns, data);
}

template<typename T>
inline string TestIncoherentMatrix<T>::getFileName()
{
	return "csv/IncoherentMatrixTest.csv";
}

template<typename T>
inline string TestIncoherentMatrix<T>::getName()
{
	return "IMAT";
}
