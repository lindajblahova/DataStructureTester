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
		CoherentMatrix(const CoherentMatrix<T>& other);
		~CoherentMatrix();

		Matrix<T>& operator=(const Matrix<T>& other) override;
		CoherentMatrix<T>& operator=(const CoherentMatrix<T>& other);
		T getDataOnIndex(const int rowIndex, const int colIndex) override;
		void setDataOnIndex(const int rowIndex, const int colIndex, const T& data) override;
		void clear() override;

		int positionInArray(const int rowIndex, const int colIndex);

		//metody kvoli structure
		Structure* clone() const override;

	private:
		Array<T>* array_;

	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rows, size_t columns, T& data) :
		Matrix<T>::Matrix(rows, columns),
		array_(new Array<T>(rows * columns))
	{
		for (int i = 0; i < array_->size(); i++)
		{
			(*array_)[i] = data;
		}
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(const CoherentMatrix<T>& other) :
		Matrix<T>(other.rows_, other.columns_),
		array_(new Array<T>(*other.array_))
	{
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
			this->rows_ = other.rows_;
			this->columns_ = other.columns_;
			array_ = new Array<T>(other.array_->size());
			
		}
		return *this;
	}

	template<typename T>
	inline T CoherentMatrix<T>::getDataOnIndex(const int rowIndex, const int colIndex)
	{
		return (*array_)[positionInArray(rowIndex, colIndex)];
	}

	template<typename T>
	inline void CoherentMatrix<T>::setDataOnIndex(const int rowIndex, const int colIndex, const T& data)
	{

		(*array_)[positionInArray(rowIndex, colIndex)] = data;
	}

	template<typename T>
	inline void CoherentMatrix<T>::clear()
	{
		delete array_;
	}

	template<typename T>
	inline int CoherentMatrix<T>::positionInArray(const int rowIndex, const int colIndex)
	{
		return  rowIndex * this->columns_ + colIndex;
	}

	template<typename T>
	inline Structure* CoherentMatrix<T>::clone() const
	{
		return new CoherentMatrix<T>(*this);
	}

}