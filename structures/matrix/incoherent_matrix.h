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
		size_t getRows() override;
		size_t getColumns() override;
		size_t size() const override;
		void clear() override;

		//metody kvoli structure
		Structure* clone() const override;

	private:
		Array<Array<T>*>* arrayOfArrays_;
		size_t rows_;
		size_t columns_;

	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rows, size_t columns, T& data) :
		arrayOfArrays_(new Array<Array<T>*>(rows)),
		rows_(rows),
		columns_(columns)
	{
		for (int i = 0; i < rows_; i++) //TODO: mozes to castovat na int, zbavis sa warnings
		{
			(*arrayOfArrays_)[i] = new Array<T>(columns_);
		}

		for (int i = 0; i < rows_; i++)
		{
			for (int j = 0; j < columns_; j++)
			{
				(*(*arrayOfArrays_)[i])[j] = data;
			}
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(const IncoherentMatrix<T>& other) :
		arrayOfArrays_(new Array<Array<T>*>(*(other.arrayOfArrays_))),
		rows_(other.rows_),
		columns_(other.columns_)
	{
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
			arrayOfArrays_ = new Array<Array<T>*>(other.rows_);
			for (int i = 0; i < rows_; i++)
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
	inline size_t IncoherentMatrix<T>::getRows()
	{
		return rows_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumns()
	{
		return columns_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size() const
	{
		return rows_ * columns_;
	}
	template<typename T>
	inline void IncoherentMatrix<T>::clear()
	{
		for (int i = 0; i < rows_; i++)
		{
			delete (*arrayOfArrays_)[i];
			(*arrayOfArrays_)[i] = nullptr;
		}
		delete arrayOfArrays_;
		arrayOfArrays_ = nullptr;
		columns_ = 0;
		rows_ = 0;
	}
	template<typename T>
	inline Structure* IncoherentMatrix<T>::clone() const
	{
		return new IncoherentMatrix<T>(*this);
	}
}