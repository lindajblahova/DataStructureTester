#pragma once
#include "../structure.h"
#include "../array/array.h"
#include "matrix.h"

namespace structures
{
	template<typename T>
	class CoherentMatrix : public Matrix<T>
	{
	public:
		CoherentMatrix(size_t rows, size_t cols, T& data);
		~CoherentMatrix();

		Matrix<T>& operator=(const Matrix<T>& other) override;
		CoherentMatrix<T>& operator=(const CoherentMatrix<T>& other);
		T getDataOnIndex(const int rowIndex, const int colIndex) override;
		void setDataOnIndex(const int rowIndex, const int colIndex, const T& data) override;
		size_t getRows() override;
		size_t getColumns() override;
		size_t size() const override;
		void clear() override;

		int positionInArray(const int rowIndex, const int colIndex);

		//metody kvoli structure
		Structure* clone() const override;

	private:
		Array<T>* array_;
		size_t rows_;
		size_t columns_;

	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rows, size_t columns, T& data) :
		Matrix<T>::Matrix(),
		array_(new Array<T>(rows * columns)),
		rows_(rows),
		columns_(columns)
	{
		for (int i = 0; i < rows_ * columns_; i++)
		{
			(*array_)[i] = data;
		}
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		clear();
	}

	template<typename T>
	inline Matrix<T>& CoherentMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		} 
		return *this;
	}

	template<typename T>
	inline CoherentMatrix<T>& CoherentMatrix<T>::operator=(const CoherentMatrix<T>& other)
	{
		if (this != &other)
		{
			clear();
			array_ = new Array<T>(other.array_->size());
			for (int i = 0; i < rows_; i++)
			{
				(*array_)[i] = (*other.array_)[i];
			}
		}
		return *this;
	}

	template<typename T>
	inline T CoherentMatrix<T>::getDataOnIndex(const int rowIndex, const int colIndex)
	{
		DSRoutines::rangeCheckExcept(rowIndex, rows_, "Invalid index - row in matrix!");
		DSRoutines::rangeCheckExcept(colIndex, columns_, "Invalid index - column in matrix!");
		return (*array_)[positionInArray(rowIndex, colIndex)];
	}

	template<typename T>
	inline void CoherentMatrix<T>::setDataOnIndex(const int rowIndex, const int colIndex, const T& data)
	{
		(*array_)[positionInArray(rowIndex, colIndex)] = data;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRows()
	{
		return rows_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumns()
	{
		return columns_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size() const
	{
		return rows_ * columns_;
	}

	template<typename T>
	inline void CoherentMatrix<T>::clear()
	{
		delete array_;
		columns_ = 0;
		rows_ = 0;
	}

	template<typename T>
	inline int CoherentMatrix<T>::positionInArray(const int rowIndex, const int colIndex)
	{
		return  rowIndex * columns_ + colIndex;
	}

	template<typename T>
	inline Structure* CoherentMatrix<T>::clone() const
	{
		return new CoherentMatrix<T>(*this);
	}

}