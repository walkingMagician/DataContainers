#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>
using std::cout;
using std::cin;
using std::endl;


#define TAB "\t"
#define DELIMETR "\n-----------------------------------------------\n" 
//#define WORK

template <typename T>
class List
{	
	template <typename Y>
	class Element
	{
		Y Data;
		Element* pNext; // следующий элимент
		Element* pPrev; // предыдущий элимент

	public:
		// Constructor
		Element(Y Data, Element<Y>* pNext = nullptr, Element<Y>* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "Econstructor:\t " << this << endl;
		}
		~Element() // Destructor
		{
			
			cout << "Edestructor:\t" << this << endl;
		}		
		friend class List;
	}; // обьявления головы и хвоста, указатели на обьект класса element 
	
	Element<T>* Head;
	Element<T>* Tail;

	size_t _size; // кол-во элементов в списке 

public:
	// Constructor
	List()
	{
		Head = Tail = nullptr;
		_size = 0; 
		cout << "LConstructor:\t" << this << endl;
	}
	List(std::initializer_list<T> init) :List()
	{
		for (T i: init) Adding(i);
		cout << "LConstructor2:\t" << this << endl;
	}
	~List() // Destructor
	{
		Element<T>* current = Head; // итератор равен голове
		while (current)
		{
			Element<T>* Temp = current; // временный элимент который равен итератору
			current = current->pNext; // переходим к след элименту
			delete Temp; // освобождаем память
		}
		cout << "Ldestructor:\t" << this << endl;
	}

	

	// methods List
	void push_front(T Data) // добавлеине элиментка в начало списка
	{
		if (Head == NULL && Tail == NULL)
		{
			Head = Tail = new Element<T>(Data);
			_size++;
		}
		else
		{
			Element<T>* New = new Element<T>(Data);
			New->pNext = Head; // присоединяем элемент к списку 
			Head->pPrev = New; // присоединяем список к элементу 
			Head = New; // смещаем голову на новый элемент 
			_size++;
		}
	}

	void push_back(T Data) // добавление элимента в конец в список
	{
		if (Head == nullptr && Tail == nullptr) push_front(Data);
		else
		{
			Element<T>* New = new Element<T>(Data);
			New->pPrev = Tail; // присоединяемся к хвосту
			Tail->pNext = New; // хвост присоединяем к новому списку
			Tail = New; // сдвигаем хвост
			_size++;
		}
	}

	void insert(T Data, int Index) // добавление элимента по индексу в списке
	{
		if (Index > _size) return;
		else if (Index == 0) push_front(Data);
		else
		{
			Element<T>* Temp = Head;
			for(T i = 0; i < Index - 1; i++)
				Temp = Temp->pNext;
			
			Element<T>* New = new Element<T>(Data);
			
			New->pNext = Temp->pNext; // присоединяемся к переду
			Temp->pNext = New; // перед присоединяем к списку
			New->pPrev = Temp->pPrev; // список присоединяем к заду
			Temp->pPrev = New; // зад присоединяется к списку
			_size++;
		}
	}

	void pop_front() // удаление элимента в начале спика
	{
		//Head = Head->pNext;
		Element<T>* Temp = Head = Head->pNext; // temp и head сдвигаем на следующию голову
		Temp->pPrev = NULL; // искоючаем ненужный элимент
		_size--;
	}

	void pop_back() // удаление в конце списка
	{
		if (Head == nullptr && Tail == nullptr) return; // если пуст то нечего
		else if (Head->pNext == nullptr) pop_front(); // если следующий элемент от головы пуст то активируем функцию pop_front()
		else 
		{
			Element<T>* Temp = Tail = Tail->pPrev; // temp и tail сдвигаем на предыдущий хвост
			Temp->pNext = NULL; // исключаем из списка
			_size--;
		}
	}

	void erase(int Index) // удаление элимента по индексу в списке
	{
		if (Index > _size) return; // нечего 
		else if (Index == _size) pop_back(); // если индекс = длине то активируем фуекцию pop_back()
		else if (Index == 0) pop_front(); // если индекс = 0 то активируем функцию pop_front()
		else
		{
			Element<T>* Temp = Head;
			for (int i = 0; i < Index - 1; i++) // идём до нужного элимента
				Temp = Temp->pNext;
			
			Element<T>* TempN = Temp->pNext; // TempN сдвинут к следующему элименту от temp
			Element<T>* TempP = Temp->pPrev; // TempP сдвинут к предыдущему элименту от temp
			Temp = nullptr; // исключаем элимент из списка
			TempP->pNext = TempN; // связываем tempN и tempP
			TempN->pPrev = TempP;
			_size--;
			
		}
	}

	//methods
	void Adding(T Data)
	{
		Element<T>* New = new Element<T>(Data);
		if (Head == NULL) 
		{
			Head = New; 
			Tail = New;
		}
		else
		{
			Tail->pNext = New; // присоединение к хвосту и сдвиг хвоста
			New->pPrev = Tail;
			Tail = New;
		}
			_size++;
	}

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		}
		cout << "Tail:\t" << Tail << endl;
		cout << "кол-во элементов списка: " << _size << endl;
	}

	void revers_print()
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		}
		cout << "Head:\t" << Head << endl;
		cout << "кол-во элементов списка: " << _size << endl;
	}

	//methods LIST

};




int main()
{
	setlocale(LC_ALL, "");
	
#ifdef WORK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List<int> list;
	for (int i = 0; i < n; i++) list.push_front(rand() % 100);
	list.print();
	
	//list.push_front(13131);
	//list.push_back(1231);
	//list.pop_front();
	//list.pop_back();
	//list.insert(1000, 3);
	//list.erase(2);
	//list.print();
	list.revers_print();
	cout << DELIMETR;
#endif
	

	//List<int> list = {};
	//List<int> list = {3};
	List<int> list = { 3, 5, 8, 13, 21 };
	//list.print();
	//cout << list;

	for (auto i : list)
	{
		cout << i << endl;
	}
	cout << endl;
	
	return 0;
}