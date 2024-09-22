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
		Element* pNext;
		Element* pPrev;

	public:
		// Constructor
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "Econstructor:\t " << this << endl;
		}
		~Element() // Destructor
		{
			cout << "Edestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail; //обьявляем 2 указателя на обЪекты класса Element непосредственно после написания класса ;
	

	size_t size; // кол-во элементов в списке 

public:
	// Constructor
	List()
	{
		// конструктор по умолчанию создаёт пустой список 
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() // Destructor
	{
		cout << "Ldestructor:\t" << this << endl;
	}

	// methods List
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
		}
		else
		{
			// создаём новый элемент 
			Element* New = new Element(Data);
			// присоединяем элемент к списку 
			New->pNext = Head;
			// присоединяем список к элементу 
			Head->pPrev = New;
			// смещаем голову на новый элемент 
			Head = New;
			size++;
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
	list.revers_print();
}