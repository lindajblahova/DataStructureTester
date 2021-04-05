#pragma once
#include "../structure.h"
#include "../array/array.h"
#include "matrix.h"

namespace structures
{
	template<typename T>
	class IncoherentMatrix : public Matrix<T>
	{
	public:
		IncoherentMatrix(size_t rows, size_t columns, T& data);
		IncoherentMatrix(const IncoherentMatrix<T>& other);
		~IncoherentMatrix();

		Matrix<T>& operator=(const Matrix<T>& other) override;
		IncoherentMatrix<T>& operator=(const IncoherentMatrix<T>& other);
		T getDataOnIndex(const int rowIndex, const int colIndex) override;
		void setDataOnIndex(const int rowIndex, const int colIndex, const T& data) override;
		void clear() override;

		Structure* clone() const override;

	private:
		Array<Array<T>*>* arrayOfArrays_;

	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rows, size_t columns, T& data) :
		Matrix<T>::Matrix(rows, columns),
		arrayOfArrays_(new Array<Array<T>*>(rows))
	{
		for (int i = 0; i < this->rows_; i++)
		{
			(*arrayOfArrays_)[i] = new Array<T>(this->columns_);
		}

		for (int i = 0; i < this->rows_; i++)
		{
			for (int j = 0; j < this->columns_; j++)
			{
				(*(*arrayOfArrays_)[i])[j] = data;
			}
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(const IncoherentMatrix<T>& other) :
		Matrix<T>(other.rows_, other.columns_),
		arrayOfArrays_(new Array<Array<T>*>(*(other.arrayOfArrays_)))
	{
		for (int i = 0; i < this->rows_; i++)
		{
			(*arrayOfArrays_)[i] = new Array<T>(*(*other.arrayOfArrays_)[i]);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		clear();
	}

	template<typename T>
	inline Matrix<T>& IncoherentMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const IncoherentMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline IncoherentMatrix<T>& IncoherentMatrix<T>::operator=(const IncoherentMatrix<T>& other)
	{
		if (this != &other)
		{
			clear();
			this->rows_ = other.rows_;
			this->columns_ = other.columns_;
			arrayOfArrays_ = new Array<Array<T>*>(other.rows_);
			for (int i = 0; i < this->rows_; i++)
			{
				(*arrayOfArrays_)[i] = new Array<T>((*(*other.arrayOfArrays_)[i]));
			}
		}
		return *this;
	}

	template<typename T>
	inline T IncoherentMatrix<T>::getDataOnIndex(const int rowIndex, const int colIndex)
	{
		return (*(*arrayOfArrays_)[rowIndex])[colIndex];
	}

	template<typename T>
	inline void IncoherentMatrix<T>::setDataOnIndex(const int rowIndex, const int colIndex, const T& data)
	{
		(*(*arrayOfArrays_)[rowIndex])[colIndex] = data;
	}

	template<typename T>
	inline void IncoherentMatrix<T>::clear()
	{
		for (int i = 0; i < this->rows_; i++)
		{
			delete (*arrayOfArrays_)[i];
			(*arrayOfArrays_)[i] = nullptr;
		}
		delete arrayOfArrays_;
		arrayOfArrays_ = nullptr;
		this->columns_ = 0;
		this->rows_ = 0;
	}
	template<typename T>
	inline Structure* IncoherentMatrix<T>::clone() const
	{
		return new IncoherentMatrix<T>(*this);
	}
}