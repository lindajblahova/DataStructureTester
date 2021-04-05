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
	class PriorityQueueTwoListsHalfCapacity : public PriorityQueueTwoLists<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoListsHalfCapacity();
		PriorityQueueTwoListsHalfCapacity(const PriorityQueueTwoListsHalfCapacity<T>& other);

		~PriorityQueueTwoListsHalfCapacity();

		int setCustomCapacity() override;

		Structure* clone() const override;

	};

	template<typename T>
	PriorityQueueTwoListsHalfCapacity<T>::PriorityQueueTwoListsHalfCapacity() : PriorityQueueTwoLists<T>()
	{
	}

	template<typename T>
	inline PriorityQueueTwoListsHalfCapacity<T>::PriorityQueueTwoListsHalfCapacity(const PriorityQueueTwoListsHalfCapacity<T>& other) :
		PriorityQueueTwoLists<T>(other)
	{
	}

	template<typename T>
	PriorityQueueTwoListsHalfCapacity<T>::~PriorityQueueTwoListsHalfCapacity()
	{
	}

	template<typename T>
	inline int PriorityQueueTwoListsHalfCapacity<T>::setCustomCapacity()
	{
		size_t newShortSize = 4;
		newShortSize = newShortSize > this->longList_->size() ? 2 : (this->longList_->size()/ 2);
		return newShortSize;
	}

	template<typename T>
	inline Structure* PriorityQueueTwoListsHalfCapacity<T>::clone() const
	{
		return new PriorityQueueTwoListsHalfCapacity<T>(*this);
	}

}