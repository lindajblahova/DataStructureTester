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
	class PriorityQueueTwoListsLimitedCapacity : public PriorityQueueTwoLists<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoListsLimitedCapacity(size_t capacity);

		PriorityQueueTwoListsLimitedCapacity(const PriorityQueueTwoListsLimitedCapacity<T>& other);
		~PriorityQueueTwoListsLimitedCapacity();

		Structure* clone() const override;

		int setCustomCapacity() override;

	};

	template<typename T>
	PriorityQueueTwoListsLimitedCapacity<T>::PriorityQueueTwoListsLimitedCapacity(size_t capacity) : PriorityQueueTwoLists<T>(capacity)
	{
	}

	template<typename T>
	PriorityQueueTwoListsLimitedCapacity<T>::PriorityQueueTwoListsLimitedCapacity(const PriorityQueueTwoListsLimitedCapacity<T>& other) :
		PriorityQueueTwoLists<T>(other)
	{
	}

	template<typename T>
	PriorityQueueTwoListsLimitedCapacity<T>::~PriorityQueueTwoListsLimitedCapacity()
	{
	}

	template<typename T>
	Structure* PriorityQueueTwoListsLimitedCapacity<T>::clone() const
	{
		return new PriorityQueueTwoListsLimitedCapacity<T>(*this);
	}

	template<typename T>
	inline int PriorityQueueTwoListsLimitedCapacity<T>::setCustomCapacity()
	{
		return this->shortList_->getCapacity();
	}

}