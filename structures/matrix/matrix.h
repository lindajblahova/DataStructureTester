#pragma once

#include "../structure.h"

namespace structures
{
	template<typename T>
	class Matrix : public Structure
	{
	public:

		void addition(Matrix<T>* other, Matrix<T>* resultMatrix);
		void multiplication(Matrix<T>* other, Matrix<T>* resultMatrix);

		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;
		virtual T getDataOnIndex(const int rowIndex, const int colIndex) = 0;
		virtual void setDataOnIndex(const int rowIndex, const int colIndex, const T& data) = 0;
		virtual void clear() = 0;

		size_t getRows();
		size_t getColumns();
		size_t size() const;

		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& other) override;

		~Matrix();

	protected:
		Matrix(int rows, int columns);

	protected:
		size_t rows_;
		size_t columns_;
	};


	template<typename T>
	inline Matrix<T>::Matrix(int rows, int columns) :
		Structure(),
		rows_(rows),
		columns_(columns)
	{
	}

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Matrix<T>::~Matrix()
	{
	}


	template<typename T>
	inline void Matrix<T>::addition(Matrix<T>* other, Matrix<T>* result)
	{
		T dataM1;
		T dataM2;
		T resultData;

		for (int i = 0; i < getRows(); i++)
		{
			for (int j = 0; j < getColumns(); j++)
			{
				dataM1 = this->getDataOnIndex(i, j);
				dataM2 = other->getDataOnIndex(i, j);
				resultData = dataM1 + dataM2;
				result->setDataOnIndex(i, j, resultData);
			}
		}
	}

	template<typename T>
	inline void Matrix<T>::multiplication(Matrix<T>* other, Matrix<T>* result)
	{
		T dataM1;
		T dataM2;
		T resultData;

		for (int i = 0; i < result->getRows(); i++)
		{
			for (int j = 0; j < result->getColumns(); j++)
			{
				resultData = 0;
				for (int k = 0; k < this->getColumns(); k++)
				{
					dataM1 = this->getDataOnIndex(i, k);
					dataM2 = other->getDataOnIndex(k, j);
					resultData += dataM1 * dataM2;
				}

				result->setDataOnIndex(i, j, resultData);
			}
		}
	}

	template<typename T>
	inline size_t Matrix<T>::getRows()
	{
		return rows_;
	}

	template<typename T>
	inline size_t Matrix<T>::getColumns()
	{
		return columns_;
	}

	template<typename T>
	inline size_t Matrix<T>::size() const
	{
		return rows_ * columns_;
	}

}