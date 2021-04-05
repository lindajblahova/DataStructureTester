#include "bitmap.h"

structures::BitMap::BitMap(int minBase, int maxBase) : min_(minBase), max_(maxBase)
{
	array_ = new Array<ULL>(((max_ - min_)/64) + 1);
}


Structure* structures::BitMap::clone() const
{
	return new BitMap(*this);
}

size_t structures::BitMap::size() const
{
	return array_->size();
}

Structure& structures::BitMap::operator=(const Structure& other)
{
	if (this != &other)
	{
		*this = dynamic_cast<const BitMap&>(other);
	}
	return *this;
}

BitMap& structures::BitMap::operator=(const BitMap& other)
{
	if (this != &other) 
	{
		delete array_;
		array_ = new Array<ULL>(*other.array_);
		min_ = other.min_;
		max_ = other.max_;
	}
	return *this;
}

int structures::BitMap::getMinBase()
{
	return min_;
}

int structures::BitMap::getMaxBase()
{
	return max_;
}

ULL structures::BitMap::getULL(int index) const
{
	return (*array_)[index];
}

void structures::BitMap::setULL(int index, ULL number) 
{
	(*array_)[index] = number;
}

void structures::BitMap::add(int index)
{
	int realIndex = index - min_;
	int cellIndex = realIndex / 64;
	int indexInCell = realIndex % 64;

	ULL* tmp = &(*array_)[cellIndex];

	structures::MemoryRoutines<ULL>::TNthBitTo1(*tmp, indexInCell);
}

void structures::BitMap::remove(int index)
{
	int realIndex = index - min_;
	int cellIndex = realIndex / 64;
	int indexInCell = realIndex % 64;

	ULL* tmp = &(*array_)[cellIndex];

	structures::MemoryRoutines<ULL>::TNthBitTo0(*tmp, indexInCell);
}

bool structures::BitMap::isPresent(int index)
{
	int realIndex = index - min_;
	int cellIndex = realIndex / 64;
	int indexInCell = realIndex % 64;

	return structures::MemoryRoutines<ULL>::TNthBitGet((*array_)[cellIndex], indexInCell);
	
	
}

bool structures::BitMap::isEqual(BitMap* other)
{
	if (array_->size() != other->array_->size())
	{
		return false;
	}

	for (int i = 0; i < array_->size(); i++)
	{
		// ak sa nerovnaju nie su rovnake
		if (other->getULL(i) != this->getULL(i))
		{
			return false;
		}
	}
	return true;
}

bool structures::BitMap::isSubSet(BitMap* other)
{
	if (array_->size() != other->array_->size())
	{
		return false;
	}
	for (int i = 0; i < array_->size(); i++)
	{
		ULL toSet = MemoryRoutines<ULL>::TAND(this->getULL(i), other->getULL(i));
		if (toSet != other->getULL(i))
		{
			return false;
		}
	}
	return true;
}

BitMap* structures::BitMap::unification(BitMap* other)
{
	// vsetky prvky, prienikove iba raz
	BitMap* tmp = new BitMap(min_, max_);
	for (int i = 0; i < array_->size(); i++)
	{
		ULL toSet = MemoryRoutines<ULL>::TOR(this->getULL(i), other->getULL(i));
		tmp->setULL(i, toSet);
	}
	return tmp;
}

BitMap* structures::BitMap::conjunction(BitMap* other)
{
	// prienik - prvky ktore sa nachadzaju  v A aj B
	BitMap* tmp = new BitMap(min_, max_);
	for (int i = 0; i < array_->size(); i++)
	{
		ULL toSet = MemoryRoutines<ULL>::TAND(this->getULL(i), other->getULL(i));
		tmp->setULL(i, toSet);
	}
	return tmp;
}

BitMap* structures::BitMap::difference(BitMap* other)
{
	// rozdiel sa rbi tak, ze vysledkom je A s vymazanymi prvkami prieniku s B
	BitMap* tmp = new BitMap(min_, max_);
	for (int i = 0; i < array_->size(); i++)
	{
		ULL toSubtract = MemoryRoutines<ULL>::TAND(this->getULL(i), other->getULL(i));
		ULL toSet = this->getULL(i) - toSubtract;
		tmp->setULL(i, toSet);
	}
	return tmp;
}

structures::BitMap::~BitMap()
{
	delete array_;
	array_ = nullptr;
	min_ = -1;
	max_ = -1;
}
