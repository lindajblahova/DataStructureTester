#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>


namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_);
	}

	// MOVE KONSTRUKTOR
	Vector::Vector(Vector&& other) noexcept :
		memory_(other.memory_),
		size_(other.size_) 
	{
		// 1. vytvor si memory a size z other
		// 2. zneplatni other mem a size
		other.memory_ = nullptr;
		other.size_ = 0;
	}

	Vector::~Vector()
	{
		free(memory_);

		// buduce ja ti podakuje :)
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memcpy(memory_, other.memory_, size_);
		}
		return *this;
	}

	// MOVE OPERATOR=
	Vector& Vector::operator=(Vector&& other) noexcept
	{
		// 1. zrus to co mas
		// 2. zober si to co ma other(memory aj size)
		// 3. zneplatni memory a size pre other
		free(memory_);
		size_ = other.size_;
		memory_ = other.memory_;

		other.memory_ = nullptr;
		other.size_ = 0;
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{

		return this == &other ||
			size_ == other.size_ &&
			memcmp(memory_, other.memory_, size_) == 0;
	}

	byte& Vector::operator[](const int index)
	{
		// vraciam adresu -> V[4] = 10
		//1. typecast
		//2. posun
		//3. dereferencia
		// index musi byt > 0 a < size-1
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		// nevraciam adresu -> urobim kopiu a tu vratim (Byte b = V[4])
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		// 1. platnost rozsahu (ci citam x bajtov medzi zaciatkom a koncom pola(nepresiahnem ho))
		// 2. skopiruj to co chces - memcpy
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid end index!");
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		// musis kontrolovat ci prepisujes svoju pridelenu pamat alebo kopirujes inam
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid src index !");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid dest index !");

		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) {
			memmove(
				dest.getBytePointer(destStartIndex),
				src.getBytePointer(srcStartIndex),
				length);
		}
		else {
			memcpy(
				dest.getBytePointer(destStartIndex),
				src.getBytePointer(srcStartIndex),
				length);
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return reinterpret_cast<byte*>(memory_) + index;
	}

}


