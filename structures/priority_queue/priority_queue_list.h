#pragma once

#include "priority_queue.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Spolocny predok pre vsetky prioritne fronty, ktorych implementujucim typom je zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueList : public PriorityQueue<T>
	{
	public:
		/// <summary> Destruktor. </summary>
		~PriorityQueueList();

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia pre prioritny front implementovany zoznamom. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom zoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom zoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
		void clear() override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho zoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>  
		int peekPriority() const override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky prioritneho frontu. </param>
		/// <remarks> 
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu. 
		/// Prioritny front implementovany zoznamom dealokuje tento objekt.
		/// </remarks>
		PriorityQueueList(List<PriorityQueueItem<T>*>* list);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueList(const PriorityQueueList<T>& other);

		/// <summary> Vrati index v zozname, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>  
		virtual int indexOfPeek() const;

	protected:
		/// <summary> Smernik na zoznam, do ktoreho sa ukladaju prvky prioritneho frontu. </summary>
		List<PriorityQueueItem<T>*>* list_;
	};

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*>* list) :
		PriorityQueue<T>(),
		list_(list)
	{
	}

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(const PriorityQueueList<T>& other) :
		PriorityQueueList<T>(dynamic_cast<List<PriorityQueueItem<T>*>*>(other.list_->clone()))
	{
		list_->clear();
		*this = other;
	}

	template<typename T>
	inline PriorityQueueList<T>::~PriorityQueueList()
	{
		//TODO 06: PriorityQueueList
		clear();
		delete list_;
		list_ = nullptr;
	}

	template<typename T>
	inline PriorityQueue<T>& PriorityQueueList<T>::operator=(const PriorityQueue<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const PriorityQueueList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueList<T>::operator=(const PriorityQueueList<T>& other)
	{
		//TODO 06: PriorityQueueList
		if (this != &other)
		{
			clear();

			for (PriorityQueueItem<T>* current : *other.list_)
			{
				list_->add(new PriorityQueueItem<T>(*current));
			}
		}
		return *this;
	}

	template<typename T>
	inline size_t PriorityQueueList<T>::size() const
	{
		//TODO 06: PriorityQueueList
		return list_->size();
	}

	template<typename T>
	inline void PriorityQueueList<T>::clear()
	{
		//TODO 06: PriorityQueueList
		for (PriorityQueueItem<T>* deleted : *list_)
		{
			delete deleted;
		}

		list_->clear();
	}

	template<typename T>
	inline int PriorityQueueList<T>::indexOfPeek() const
	{
		//TODO 06: PriorityQueueList
		if (list_->isEmpty())
		{
			throw std::logic_error("Priority queue is empty!");
		}
		
		int current = 0, index = 0;
		int priorityMax = (*list_)[0]->getPriority();

		for (PriorityQueueItem<T>* priority : *list_)
		{
			if (priority->getPriority() < priorityMax) // lebo cim mensie cislo tym vacsia priorita
			{
				priorityMax = priority->getPriority();
				index = current;
			}
			current++;
		}
		return index;
	}

	template<typename T>
	inline T PriorityQueueList<T>::pop()
	{
		//TODO 06: PriorityQueueList
		PriorityQueueItem<T>* popped = list_->removeAt(indexOfPeek());
		T data = popped->accessData();
		delete popped;
		return data;
	}

	template<typename T>
	inline T & PriorityQueueList<T>::peek()
	{
		//TODO 06: PriorityQueueList
		return (*list_)[indexOfPeek()]->accessData();
	}

	template<typename T>
	inline const T PriorityQueueList<T>::peek() const
	{
		//TODO 06: PriorityQueueList
		return (*list_)[indexOfPeek()]->accessData();
	}

	template<typename T>
	inline int PriorityQueueList<T>::peekPriority() const
	{
		//TODO 06: PriorityQueueList
		return (*list_)[indexOfPeek()]->getPriority();
	}
}