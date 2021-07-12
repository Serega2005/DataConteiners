#include<iostream>
using namespace std;
using std::cout;
using std::endl;
using std::cin;

#define tab "\t"
#define delimiter "\n-------------------------------------------------------------------------\n"
//#define DEBUG

template<typename T> class Tree;
template<typename T> class UniqueTree;

template<typename T>class Tree
{
protected:
	class Element
	{
		T Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
            cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree<T>;
		friend class UniqueTree<T>;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const initializer_list<T>& il) :Tree()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
			insert(*it, Root);
	}
	Tree(const Tree<T>& other)
	{
		copy(other.Root);
		cout << "CopyConstructor:" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}

	//               Operators:
	Tree<T>& operator=(const Tree<T>& other)
	{
		if (this == &other)return *this;
		clear(Root);
		copy(other.Root);
		cout << "CopyAssignment;\t" << this << endl;
	}


	void insert(T Data)
	{
		insert(Data, this->Root);
	}
	void erase(T Data)
	{
		erase(Data, Root);
	}
	void clear()
	{
		clear(Root);
		this->Root = nullptr;
	}
	T minValue()const
	{
		return minValue(this->Root);
	}
	T maxValue()const
	{
		return maxValue(this->Root);
	}
	T count()const
	{
		return count(Root);
	}
	T sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return avg(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(T Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			/*if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);*/
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
	void erase(T Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
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
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	T minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	T maxValue(Element* Root)const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	T count(Element* Root)const
	{
		//return count(Root->pRight) + count(Root->pLeft) + 1;
		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
	}
	T sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	double avg(Element* Root)const
	{
		return (double)sum(Root) / count(Root);
	}
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
};

template<typename T>class UniqueTree :public Tree<T>
{
private:
	void insert(T Data, Tree<T>::Element* Root)
	{
		if (this->Root == nullptr)this->Root = new typename Tree<T>::Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new typename Tree<T>::Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			/*if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);*/
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new typename Tree<T>::Element(Data);
		}
	}
public:
	void insert(T Data)
	{
		return insert(Data, this->Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.insert(-2, tree.getRoot());
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "количество элементов дерева: " << tree.count() << endl;
	cout << "Сумму элементов дерева: " << tree.sum() << endl;
	cout << "Ср.зн. элементов дерева: " << tree.avg() << endl;
	int value;
	cout << "Введите значение удаляемого элемента: "; cin >> value;
	tree.erase(value);
	tree.print();
	cout << delimiter << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "количество элементов дерева: " << u_tree.count() << endl;
	cout << delimiter << endl;

	//Tree tree2 = tree;
	Tree tree2;
	tree2 = tree;
	tree.print();
#endif // BASE_CHECK

	Tree<int> tree = { 50, 25, 80, 16, 32, 64, 85, 12, 22, 31, 58, 77, 84, 91 };
	tree.print();
	int value;
	cout << "Введите значение удаяляемого элемента: "; cin >> value;
	tree.erase(value);
	tree.print();
}