#pragma once

#include "priority_queue_two_lists.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoListsSqrtCapacity : public PriorityQueueTwoLists<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoListsSqrtCapacity();
		PriorityQueueTwoListsSqrtCapacity(const PriorityQueueTwoListsSqrtCapacity<T>& other);

		~PriorityQueueTwoListsSqrtCapacity();

		int setCustomCapacity() override;

		Structure* clone() const override;

	};

	template<typename T>
	inline PriorityQueueTwoListsSqrtCapacity<T>::PriorityQueueTwoListsSqrtCapacity() : PriorityQueueTwoLists<T>()
	{
	}

	template<typename T>
	inline PriorityQueueTwoListsSqrtCapacity<T>::PriorityQueueTwoListsSqrtCapacity(const PriorityQueueTwoListsSqrtCapacity<T>& other) :
		PriorityQueueTwoLists<T>(other)
	{
	}

	template<typename T>
	inline PriorityQueueTwoListsSqrtCapacity<T>::~PriorityQueueTwoListsSqrtCapacity()
	{
	}

	template<typename T>
	inline int PriorityQueueTwoListsSqrtCapacity<T>::setCustomCapacity()
	{
		size_t newShortSize = 4;
		newShortSize = newShortSize > this->longList_->size() ? 2 : (size_t)sqrt(this->longList_->size());
		return newShortSize;
	}

	template<typename T>
	inline Structure* PriorityQueueTwoListsSqrtCapacity<T>::clone() const
	{
		return new PriorityQueueTwoListsSqrtCapacity<T>(*this);
	}

}