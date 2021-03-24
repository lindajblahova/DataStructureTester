#pragma once
#include "structures/matrix/coherent_matrix.h"
#include "TestMatrix.h"


template<typename T>
class TestCoherentMatrix : public TestMatrix<T>
{
public:

	TestCoherentMatrix();
	~TestCoherentMatrix();

private:

	Matrix<T>* newStructure(size_t rows, size_t columns, T& data) override;
	const char* getFileName() override;

};

template<typename T>
inline TestCoherentMatrix<T>::TestCoherentMatrix()
{
}

template<typename T>
inline TestCoherentMatrix<T>::~TestCoherentMatrix()
{
}

template<typename T>
inline Matrix<T>* TestCoherentMatrix<T>::newStructure(size_t rows, size_t columns, T& data)
{
	return new CoherentMatrix<T>(rows, columns, data);
}

template<typename T>
inline const char* TestCoherentMatrix<T>::getFileName()
{
	return "CoherentMatrixTest.csv";
}
