#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define TAB "\t"
#define DELIMETR "\n-----------------------------------------------\n" 

class List
{
	class Element
	{
		int Data;
		Element* pNext; // следующий элимент
		Element* pPrev; // предыдущий элимент

	public:
		// Constructor
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "Econstructor:\t " << this << endl;
		}
		~Element() // Destructor
		{
			delete pNext;
			delete pPrev;
			//delete new::List;
			cout << "Edestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail; // обьявления головы и хвоста, указатели на обьект класса element 

	size_t size; // кол-во элементов в списке 

public:
	// Constructor
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() // Destructor
	{
		//delete Head;
		//delete Tail;
		cout << "Ldestructor:\t" << this << endl;
	}

	// methods List
	void push_front(int Data) // добавлеине элиментка в начало списка
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
		}
		else
		{
			Element* New = new Element(Data);
			New->pNext = Head; // присоединяем элемент к списку 
			Head->pPrev = New; // присоединяем список к элементу 
			Head = New; // смещаем голову на новый элемент 
			size++;
		}
	}

	void push_back(int Data) // добавление элимента в конец в список
	{
		if (Head == nullptr && Tail == nullptr) push_front(Data);
		else
		{
			Element* New = new Element(Data);
			New->pPrev = Tail; // присоединяемся к хвосту
			Tail->pNext = New; // хвост присоединяем к новому списку
			Tail = New; // сдвигаем хвост
			size++;
		}
	}

	void insert(int Data, int Index) // добавление элимента по индексу в списке
	{
		if (Index > size) return;
		else if (Index == 0) push_front(Data);
		else
		{
			Element* Temp = Head;
			for(int i = 0; i < Index - 1; i++)
				Temp = Temp->pNext;
			
			Element* New = new Element(Data);
			
			New->pNext = Temp->pNext; // присоединяемся к переду
			Temp->pNext = New; // перед присоединяем к списку
			New->pPrev = Temp->pPrev; // список присоединяем к заду
			Temp->pPrev = New; // зад присоединяется к списку
			size++;
		}
	}

	void pop_front() // удаление элимента в начале спика
	{
		//Head = Head->pNext;
		Element* Temp = Head = Head->pNext; // temp и head сдвигаем на следующию голову
		Temp->pPrev = NULL; // искоючаем ненужный элимент
		size--;
	}

	void pop_back() // удаление в конце списка
	{
		if (Head == nullptr && Tail == nullptr) return; // если пуст то нечего
		else if (Head->pNext == nullptr) pop_front(); // если следующий элемент от головы пуст то активируем функцию pop_front()
		else 
		{
			Element* Temp = Tail = Tail->pPrev; // temp и tail сдвигаем на предыдущий хвост
			Temp->pNext = NULL; // исключаем из списка
			size--;
		}
	}

	void erase(int Index) // удаление элимента по индексу в списке
	{
		if (Index > size) return; // нечего 
		else if (Index == size) pop_back(); // если индекс = длине то активируем фуекцию pop_back()
		else if (Index == 0) pop_front(); // если индекс = 0 то активируем функцию pop_front()
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < Index - 1; i++) // идём до нужного элимента
				Temp = Temp->pNext;
			
			Element* TempN = Temp->pNext; // TempN сдвинут к следующему элименту от temp
			Element* TempP = Temp->pPrev; // TempP сдвинут к предыдущему элименту от temp
			Temp = nullptr; // исключаем элимент из списка
			TempP->pNext = TempN; // связываем tempN и tempP
			TempN->pPrev = TempP;
			size--;
			
		}
	}

	//methods
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		}
		cout << "Tail:\t" << Tail << endl;
		cout << "кол-во элементов списка: " << size << endl;
	}

	void revers_print()
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << TAB << Temp << TAB << Temp->Data << TAB << Temp->pNext << endl;
		}
		cout << "Head:\t" << Head << endl;
		cout << "кол-во элементов списка: " << size << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;

	List list;
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

	/*List list2 = { 3, 5, 8, 13, 21 };
	for (int i : list2)
	{
		cout << i << TAB;
	}
	cout << endl;*/
	
}