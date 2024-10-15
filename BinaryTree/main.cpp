#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define tab "\t";


class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight) 
		{
			cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Edestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;

public:

	Element* getRoot()const
	{
		return Root;
	}

	Tree()
	{
		Root = nullptr;
		cout << "Tconstructor:\t" << this << endl;
	}
	~Tree()
	{
		Clear();
		cout << "Tdestructor:\t" << this << endl;
	}

	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}

	void insert(int Data)
	{
		return insert(Data, Root);
	}

	int maxValue() const
	{
		return maxValue(Root);
	}

	int minValue() const
	{
		return minValue(Root);
	}

	int Count()
	{
		return Count(Root);
	}

	int Sum()
	{
		return Sum(Root);
	}

	double Avg()
	{
		return (double)Sum() / Count();
	}

	int Derth()
	{
		return Derth(Root);
	}

	Element* Balance()
	{
		return Balance(Root);
	}

	void print() const
	{
		print(Root);
		cout << endl;
	}

private:

	// methods 
	// стирание ветвей дерева
	void Clear(Element* Root)
	{
		if (Root == nullptr) return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int Derth(Element* Root)
	{
		int size = 0;
		return size;
	}

	// функция для обхода дерева и сбора элементов в вектор
	void AddTreeInVector(std::vector<int>& vector, Element* Root)
	{
		if (Root)
		{
			AddTreeInVector(vector, Root->pLeft);
			vector.push_back(Root->Data);
			AddTreeInVector(vector, Root->pRight);
		}
	}

	// функци собирания из сортированного вектора в сортированное дерево 
	Element* SortVectorTree(std::vector<int>& vector, int start, int end)
	{
		if (start > end) return nullptr;
		int mid = start + (end - start) / 2;

		Element* Root = new Element(vector[mid]);
		
		Root->pLeft = SortVectorTree(vector, start, mid - 1);
		Root->pRight = SortVectorTree(vector, mid + 1, end);
		
		return Root;
	}

	// главная функция собирает всё вместе
	Element* Balance(Element* Root) 
	{
		std::vector<int> vector;
		AddTreeInVector(vector, Root);
		sort(vector.begin(), vector.end());

		return SortVectorTree(vector, 0, vector.size() - 1);
	}

	// Функция для нахождения максимального значения в дереве
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)throw std::exception("Error is maxValue: дерево пустое");
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	// Функция для нахождения минимального значения в дереве
	int minValue(Element* Root)const
	{
		if (Root == nullptr)throw exception("Error is minValue: дерево пустое");
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}

	int Count(Element* Root) // кол-во элиментов дерева
	{
		if (Root == nullptr) return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root) // сумма всех элиментов дерева
	{
		if (Root == nullptr) return 0;
		else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
	}

	// methods displey
	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

};

void main()
{
	setlocale(LC_ALL, "");

	try
	{

		int n;
		cout << "n = "; cin >> n;

		Tree tree;
		for (int i = 0; i < n; i++)
			tree.insert(rand() % 100);
		tree.print();
		cout << tree.minValue() << endl;
		cout << tree.maxValue() << endl;
		cout << tree.Avg() << endl;
		cout << tree.Count() << endl;
		cout << tree.Sum() << endl;
		//tree.Balance();
		//tree.print();
		cout << endl;
		cout << endl;

		cout << tree.Derth() << endl;

	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}

}