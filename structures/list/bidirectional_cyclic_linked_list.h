#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class BCLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		BCLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		BCLinkedListItem(const BCLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~BCLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		BCLinkedListItem<T>* getNext();

		/// <summary> Getter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Predchadzajuci prvok zretazeneho zoznamu. </returns>
		BCLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(BCLinkedListItem<T>* next);

		/// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "previous"> Novy predchadzajuci prvok zretazeneho zoznamu. </param>
		void setPrevious(BCLinkedListItem<T>* previous);

	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		BCLinkedListItem<T>* next_;

		/// <summary> Predchadzajuci prvok zretazeneho zoznamu. </summary>
		BCLinkedListItem<T>* previous_;
	};

	/// <summary> Obojstranne zretazeny cyklicky zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class BidirectionalCyclicLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		BidirectionalCyclicLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BCLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		BidirectionalCyclicLinkedList(const BidirectionalCyclicLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~BidirectionalCyclicLinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		BidirectionalCyclicLinkedList<T>& operator=(const BidirectionalCyclicLinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;

	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;

		/// <summary> Prvy prvok zoznamu. </summary>
		BCLinkedListItem<T>* first_;

	private:

		/// <summary> Vrati posledny prvok zoznamu. </summary>
		/// <returns> Posledny prvok zoznamu. </param>
		BCLinkedListItem<T>* getLastItem() const;

		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		BCLinkedListItem<T>* getItemAtIndex(int index) const;

	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class BCLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			BCLinkedListIterator(BCLinkedListItem<T>* position, const BidirectionalCyclicLinkedList<T>* bcList);

			/// <summary> Destruktor. </summary>
			~BCLinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			BCLinkedListItem<T>* position_;

			const BidirectionalCyclicLinkedList<T>* bcList_;

		};
	};

	template<typename T>
	inline BCLinkedListItem<T>::BCLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline BCLinkedListItem<T>::BCLinkedListItem(const BCLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline BCLinkedListItem<T>::~BCLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline BCLinkedListItem<T>* BCLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline BCLinkedListItem<T>* BCLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void BCLinkedListItem<T>::setNext(BCLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void BCLinkedListItem<T>::setPrevious(BCLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>::BidirectionalCyclicLinkedList() :
		List<T>::List(),
		size_(0),
		first_(nullptr)
	{
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>::BidirectionalCyclicLinkedList(const BidirectionalCyclicLinkedList<T>& other) :
		BidirectionalCyclicLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>::~BidirectionalCyclicLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* BidirectionalCyclicLinkedList<T>::clone() const
	{
		return new BidirectionalCyclicLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t BidirectionalCyclicLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& BidirectionalCyclicLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const BidirectionalCyclicLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>& BidirectionalCyclicLinkedList<T>::operator=(const BidirectionalCyclicLinkedList<T>& other)
	{
		// test identity
		if (this != &other)
		{
			clear();

			// prejdi druhy zoznam
			// add(data z aktualneho bc linked list itemu)
			for (T data : other)
			{
				add(data);
			}
		}
		return *this;
	}

	template<typename T>
	inline T& BidirectionalCyclicLinkedList<T>::operator[](const int index) // kompilator sa bude snazit zavolat tuto lebo je rychlejsia
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T BidirectionalCyclicLinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void BidirectionalCyclicLinkedList<T>::add(const T& data)
	{
		BCLinkedListItem<T>* newBCLLItem = new BCLinkedListItem<T>(data);

		if (size_ == 0) {
			first_ = newBCLLItem;
			newBCLLItem->setPrevious(first_);
			newBCLLItem->setNext(first_);
		}
		else
		{
			getLastItem()->setNext(newBCLLItem);
			newBCLLItem->setPrevious(getLastItem());
			first_->setPrevious(newBCLLItem);
			newBCLLItem->setNext(first_);
	
		}
		size_++;
	}

	template<typename T>
	inline void BidirectionalCyclicLinkedList<T>::insert(const T& data, const int index)
	{
		if (index == size_) {
			add(data);
		}
		else {

			if (index == 0) {
				BCLinkedListItem<T>* newBCLLItem = new BCLinkedListItem<T>(data);
				newBCLLItem->setNext(first_);
				newBCLLItem->setPrevious(getLastItem());
				getLastItem()->setNext(newBCLLItem);
				first_->setPrevious(newBCLLItem);

				first_ = newBCLLItem;
			}
			else {
				BCLinkedListItem<T>* prevLLItem = getItemAtIndex(index - 1);
				BCLinkedListItem<T>* newBCLLItem = new BCLinkedListItem<T>(data);

				newBCLLItem->setNext(prevLLItem->getNext());
				newBCLLItem->setPrevious(prevLLItem);
				prevLLItem->getNext()->setPrevious(newBCLLItem);
				prevLLItem->setNext(newBCLLItem);
			}

			size_++;
		}
	}

	template<typename T>
	inline bool BidirectionalCyclicLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data); // vracia -1 ak nenajde index  / O(n)
		if (index != -1) {
			removeAt(index);		// O(n)  -> zlozitost je 2O(n) ale da sa prerobit na O(n)
			return true;
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline T BidirectionalCyclicLinkedList<T>::removeAt(const int index)
	{
		BCLinkedListItem<T>* deleted = nullptr;

		if (index == 0 && size_ > 0) {
			deleted = first_;

			if (size_ == 1) {
				first_ = nullptr;
			} 
			else
			{
				getLastItem()->setNext(deleted->getNext());
				deleted->getNext()->setPrevious(getLastItem());
				first_ = deleted->getNext();
			}
		}
		else 
		{
			deleted = getItemAtIndex(index);
			deleted->getNext()->setPrevious(deleted->getPrevious());
			deleted->getPrevious()->setNext(deleted->getNext());
		}

		T data = deleted->accessData();
		delete deleted;
		size_--;

		return data;

	}

	template<typename T>
	inline int BidirectionalCyclicLinkedList<T>::getIndexOf(const T& data)
	{
		BCLinkedListItem<T>* current = first_;
		int index = 0;

		while (current != nullptr) {

			// test ci som nasiel
			if (current->accessData() == data) {
				return index;
			}
			index++;
			current = current->getNext();
			if (current == first_)
			{
				break;
			}
		}

		return -1;
		// nerobit to forcyklom lebo zlozitost O(n^2)!!!
	}

	template<typename T>
	inline void BidirectionalCyclicLinkedList<T>::clear()
	{
		BCLinkedListItem<T>* current = first_;

		while (current != nullptr )
		{
			BCLinkedListItem<T>* deleted = current;
			current = current->getNext();
			delete deleted;
			if (current == first_)
			{
				break;
			}
		}

		first_ = nullptr;
		size_ = 0;

	}

	template<typename T>
	inline Iterator<T>* BidirectionalCyclicLinkedList<T>::getBeginIterator() const
	{
		return new BCLinkedListIterator(first_, this);
	}

	template<typename T>
	inline Iterator<T>* BidirectionalCyclicLinkedList<T>::getEndIterator() const
	{
		return new BCLinkedListIterator(nullptr, this);
	}

	template<typename T>
	inline BCLinkedListItem<T>* BidirectionalCyclicLinkedList<T>::getLastItem() const
	{
		return first_->getPrevious();
	}

	template<typename T>
	inline BCLinkedListItem<T>* BidirectionalCyclicLinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index");

		BCLinkedListItem<T>* result ;
		if (index > (size_ / 2))
		{
			result = this->getLastItem();
			for (int i = size_; i > index; i--) {
				result = result->getPrevious();
			}
		} 
		else
		{
			result = first_;
			for (int i = 0; i < index; i++) {
				result = result->getNext();
			}
		}
		return result;
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::BCLinkedListIterator(BCLinkedListItem<T>* position, const BidirectionalCyclicLinkedList<T>* bcList) :
		position_(position), 
		bcList_(bcList)
	{
	}

	template<typename T>
	inline BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::~BCLinkedListIterator()
	{
		position_ = nullptr;
		bcList_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::operator=(const Iterator<T>& other)
	{
		position_ = dynamic_cast<const BCLinkedListIterator&>(other).position_;
		bcList_ = dynamic_cast<const BCLinkedListIterator&>(other).bcList_;

		return *this;
	}

	template<typename T>
	inline bool BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::operator!=(const Iterator<T>& other)
	{
		
		return (position_ != dynamic_cast<const BCLinkedListIterator&>(other).position_) ||
			(bcList_ != dynamic_cast<const BCLinkedListIterator&>(other).bcList_);
	}

	template<typename T>
	inline const T BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::operator*()
	{
		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& BidirectionalCyclicLinkedList<T>::BCLinkedListIterator::operator++()
	{
		if (position_->getNext() != bcList_->first_)
		{
			position_ = position_->getNext();
		}
		else
		{
			position_ = nullptr;
		}
		return *this;
	}
}