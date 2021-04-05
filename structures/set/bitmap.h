#pragma once

#include "../array/array.h"
#include "../memory_routines.h"

using namespace structures;
typedef unsigned long long ULL;

namespace structures
{
	class BitMap : public Structure
	{
	public:
		BitMap(int minBase, int MaxBase);

		Structure* clone() const override;
		size_t size() const override;
		Structure& operator=(const Structure& other) override;
		BitMap& operator=(const BitMap& other);

		int getMinBase();
		int getMaxBase();
		ULL getULL(int index) const;
		void setULL(int index, ULL number);

		void add(int index);
		void remove(int index);
		bool isPresent(int index);
		bool isEqual(BitMap* other);

		// this je vacsia
		bool isSubSet(BitMap* other);

		BitMap* unification(BitMap* other);
		BitMap* conjunction(BitMap* other);

		// odcitavam od this other
		BitMap* difference(BitMap* other);

		~BitMap();

	private:
		Array<unsigned long long>* array_;
		int min_;
		int max_;
	};

}

