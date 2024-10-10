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
		cout << "Tdestructor:\t" << this << endl;
	}

	// methods 
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data == Root->Data) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pRight);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	// Функция для обхода дерева и сбора элементов
	void AddTreeInVector(std::vector<int>& vector, Element* Root)
	{
		if (Root)
		{
			AddTreeInVector(vector, Root->pLeft);
			vector.push_back(Root->Data);
			AddTreeInVector(vector, Root->pRight);
		}
	}

	Element* SortVectorTree(std::vector<int>& vector, int start, int end)
	{
		if (start > end) return nullptr;
		int mid = start + (end - start) / 2;

		Element* Root = new Element(vector[mid]);
		
		Root->pLeft = SortVectorTree(vector, start, mid - 1);
		Root->pRight = SortVectorTree(vector, mid + 1, end);
		
		return Root;
	}

	Element* Balance(Element* Root)
	{
		std::vector<int> vector;
		AddTreeInVector(vector, Root);
		sort(vector.begin(), vector.end());

		return SortVectorTree(vector, 0, vector.size() - 1);
	}

	// Функция для нахождения максимального значения в дереве
	int maxValue(Element* Root)
	{
		if (Root == nullptr) return INT_MIN;
		return max(Root->Data, max(maxValue(Root->pLeft), maxValue(Root->pRight)));
	}

	// Функция для нахождения минимального значения в дереве
	int minValue(Element* Root)
	{
		if (Root == nullptr) return INT_MAX;
		return min(Root->Data, min(minValue(Root->pLeft), minValue(Root->pRight)));
	}


	// methods displey
	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		cout << Root->Data << tab;
		print(Root->pLeft);
		print(Root->pRight);
	}
	

};

void main()
{
	setlocale(LC_ALL, "");


	int n;
	cout << "n = "; cin >> n;

	Tree tree;
	for (int i = 0; i < n; i++)
		tree.insert(rand() % 100, tree.getRoot());
	tree.print(tree.getRoot());
	//cout << endl;
	//cout << tree.minValue(tree.getRoot());
	//cout << endl;
	//tree.maxValue(tree.getRoot());
	//cout << tree.max;
	cout << endl;

	/*tree.Balance(tree.getRoot());
	tree.print(tree.getRoot());
	cout << endl;
	cout << tree.minValue(tree.getRoot());
	cout << endl;
	cout << tree.maxValue(tree.getRoot());*/
	cout << endl;



}