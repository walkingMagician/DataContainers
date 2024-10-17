#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <ctime>
#include <chrono>
#include <functional>
#include <iomanip>
#include <queue>
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
			//cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "Edestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;

public:

	Element* getRoot()const
	{
		return Root;
	}

	Tree()
	{
		Root = nullptr;
		//cout << "Tconstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		Clear();
		//cout << "Tdestructor:\t" << this << endl;
	}

	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}

	void erase(int Data)
	{
		erase(Data, Root);
	}

	int maxValue() const
	{
		return maxValue(Root);
	}

	int minValue() const
	{
		return minValue(Root);
	}

	int Count() const
	{
		return Count(Root);
	}

	int Sum() const
	{
		return Sum(Root);
	}

	double Avg() const
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

	void time(std::function<void()> func)
	{
		// ���������� ������� ����� ����� ����������� ����� ����
		auto start = std::chrono::high_resolution_clock::now();
		func();
		// ������ ���������� ������� ����� ����� ���������� ����
		auto end = std::chrono::high_resolution_clock::now();
		// ��������� �����������������
		std::chrono::duration<double, std::milli> duration = end - start;
		// �����
		std::cout << "����� ����������: " << duration.count() << " �����������" << std::endl;
	}

	void print() const
	{
		print(Root);
		cout << endl;
	}

private:

	// methods 
	// �������� ������ ������
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

	// �������� ��������
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	int Derth(Element* Root)
	{
		if (Root == nullptr) return 0;
		int Left = Derth(Root->pLeft);
		int Right = Derth(Root->pRight);
		return max(Left, Right) + 1;
	}

	// ������� ��� ������ ������ � ����� ��������� � ������
	void AddTreeInVector(std::vector<int>& vector, Element* Root)
	{
		if (Root)
		{
			AddTreeInVector(vector, Root->pLeft);
			vector.push_back(Root->Data);
			AddTreeInVector(vector, Root->pRight);
		}
	}

	// ������ ��������� �� �������������� ������� � ������������� ������ 
	Element* SortVectorTree(std::vector<int>& vector, int start, int end)
	{
		if (start > end) return nullptr;
		int mid = start + (end - start) / 2;

		Element* Root = new Element(vector[mid]);
		
		Root->pLeft = SortVectorTree(vector, start, mid - 1);
		Root->pRight = SortVectorTree(vector, mid + 1, end);
		
		return Root;
	}

	// ������� ������� �������� �� ������
	Element* Balance(Element* Root) 
	{
		std::vector<int> vector;
		AddTreeInVector(vector, Root);
		sort(vector.begin(), vector.end());

		return SortVectorTree(vector, 0, vector.size() - 1);
	}

	// ������� ��� ���������� ������������� �������� � ������
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)throw std::exception("Error is maxValue: ������ ������");
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	// ������� ��� ���������� ������������ �������� � ������
	int minValue(Element* Root)const
	{
		if (Root == nullptr)throw std::exception("Error is minValue: ������ ������");
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}

	int Count(Element* Root) const // ���-�� ��������� ������
	{
		if (Root == nullptr) return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root) const // ����� ���� ��������� ������
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
	friend class UniqueTree;
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};




	/*clock_t start = clock();
	clock_t end = clock();
	cout << " ����� " << double(end - start) / CLOCKS_PER_SEC << " ������\n";*/

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
		//tree.print();
		cout << "����������� ��������: " << tree.minValue() << endl;
		cout << "������������ ��������: " << tree.maxValue() << endl;
		cout << "������ ������: " << tree.Count() << endl;
		cout << "��������������������: " << tree.Avg() << endl;
		cout << "����� ���� ���������: " << tree.Sum() << endl;
		cout << "������� ������: " << tree.Derth() << endl;
		tree.time([&]() { tree.Derth(); });
		//tree.time([&]() { tree.erase(50); });
		//cout << "������������ ������: " << tree.Balance() << endl;
		tree.erase(4);
		//tree.print();
		cout << endl;


		/*UniqueTree utree;
		utree.insert(5);
		utree.print();*/

	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}

}