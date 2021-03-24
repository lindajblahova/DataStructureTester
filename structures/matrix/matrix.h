#pragma once

#include "../structure.h"

namespace structures
{
	template<typename T>
	class Matrix : public Structure
	{
	public:

		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;
		virtual T getDataOnIndex(const int rowIndex, const int colIndex) = 0;
		virtual void setDataOnIndex(const int rowIndex, const int colIndex, const T& data) = 0;
		virtual size_t getRows() = 0;
		virtual size_t getColumns() = 0;
		virtual size_t size() const = 0;
		virtual void clear() = 0;
		//virtual ~Matrix();

		// metody kvoli structure
		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& other) override;



	protected:
		Matrix();
	};

	template<typename T>
	inline Matrix<T>::Matrix() :
		Structure()
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

	//template<typename T>
	//inline Matrix<T>::~Matrix()
	//{
	//}

}