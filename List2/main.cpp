#include <iostream>
#include <initializer_list>
using std::cin;
using std::cout;
using std::endl;

#define TAB "\t"
#define delimiter "\n----------------------------\n"

template <typename T>
class List
{
	template <typename T>
	class Element
	{
		T Data;
		Element<T>* pNext;
		Element<T>* pPrev;

	public:
		Element(T Data, Element<T>* pNext = nullptr, Element<T>* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	};
	Element<T>* Head; 
	Element<T>* Tail;	//Объявляем два указателя на объекты класса 'Element' непосредственно после описания класса;
	
	size_t size;	//Количество элементов списка

	template <typename T>
	class ConstBaseIterator
	{
	protected:
		Element<T>* Temp;

	public:
		ConstBaseIterator(Element<T>* Temp) :Temp(Temp) {}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator<T>& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator<T>& other)const
		{
			return this->Temp != other.Temp;
		}

		int operator*()const
		{
			return Temp->Data;
		}
	};


public:

	template <typename T>
	class ConstIterator :public ConstBaseIterator<T>
	{
	public:
		ConstIterator(Element<T>* Temp) :ConstBaseIterator<T>(Temp) {}
		~ConstIterator() {}

		ConstIterator<T>& operator++()		//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator<T> operator++(int)	//Postfix increment
		{
			ConstIterator<T> old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator<T>& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator<T> operator--(int)
		{
			ConstIterator<T> old = Temp;
			Temp = Temp->pPrev;
			return old;
		}
	};

	template <typename T>
	class ConstReverseIterator :public ConstBaseIterator<T>
	{
	public:
		ConstReverseIterator(Element<T>* Temp) :ConstBaseIterator<T>(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator<T>& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator<T> operator++(int)
		{
			ConstReverseIterator<T> old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator<T>& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator<T> operator--(int)
		{
			ConstReverseIterator<T> old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};

	template <typename T>
	class Iterator :public ConstIterator<T>
	{
	public:
		Iterator(Element<T>* Temp) :ConstIterator<T>(Temp) {}
		~Iterator() {}

		int& operator*()
		{
			return Temp->Data;
		}
	};

	template <typename T>
	class ReverseIterator :public ConstReverseIterator<T>
	{
	public:
		ReverseIterator(Element<T>* Temp) :ConstReverseIterator<T>(Temp) {}
		~ReverseIterator() {}

		int& operator*()
		{
			return Temp->Data;
		}
	};


	ConstIterator<T> begin()const
	{
		return Head;
	}
	ConstIterator<T> end()const
	{
		return nullptr;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}

	ConstReverseIterator<T> rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator<T> rend()const
	{
		return nullptr;
	}
	ReverseIterator<T> rbegin()
	{
		return Tail;
	}
	ReverseIterator<T> rend()
	{
		return nullptr;
	}

	// constructor and destructor List
	List()
	{
		//Конструктор по умолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstrutor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		//begin() - возвращает итератор на начало контейнера.
		//end()   - возвращает итератор на конец  контейнера.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List& other) :List()	//Без делегирования может падать
	{
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);	//Явный вызов MoveAssignment
	}
	~List()
	{
		//while(Head) pop_front();
		while (Tail) pop_back();
		cout << "LDestrutor:\t" << this << endl;
	}

	// Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();

		//Deep copy - Побитовое копирование:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head) pop_front();

		//Shallow copy - Поверхностное копирование:
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		//Обязательно нужно обнулить 'other':
		other.Head = other.Tail = nullptr;
		other.size = 0;

		cout << "LMoveAssignment:\t" << this << endl;
	}

	// Adding elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)Head = Tail = new Element(Data);
		else
		{
			Head = Head->pPrev = new Element<T>(Data, Head);
		}
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(T Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index == size - 1)return push_back(Data);
		if (Index >= size)throw std::exception("insert: Out of range exception");
		Element<T>* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
		size++;
	}

	// Removing elements
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size = 0;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		Element* Temp;
		if (Index == 0) return pop_front();
		if (Index == size - 1) return pop_back();
		if (Index >= size) throw std::exception("erase: Out of range exception");
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Element<T>* TempN = Temp->pNext;
		Element<T>* TempP = Temp->pPrev;
		Temp = nullptr;
		delete Temp;
		TempP->pNext = TempN;
		TempN->pPrev = TempP;
		size--;
	}

	// Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

template <typename T> 
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List buffer;
	for (List::ConstIterator it = left.begin(); it != left.end(); ++it)buffer.push_back(*it);
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}


//#define BASE_CHECK
//#define ITERATORS_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*for (int i = 0; i < n * 2; i++)list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << TAB; cout << endl;
	for (int i : list2)cout << i << TAB; cout << endl;
	for (int i : list3)cout << i << TAB; cout << endl;

	/*for (List<int>::Iterator<int> it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}*/
	for (int i : list1)cout << i << TAB; cout << endl;
	

	return 0;
}