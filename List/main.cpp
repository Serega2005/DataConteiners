#include<iostream>
using namespace std;
using std::cout;
using std::endl;
using std::cin;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"
//#define DEBUG

template<typename T>class List
{
	class Element
	{
		T Data;      //Значение элемента
		Element* pNext;//указатель на следующий элемент
		Element* pPrev;//указатель на предыдущий элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
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
		friend class List<T>;
	};
	Element* Head;
	Element* Tail;
	unsigned int size;

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BITConstructor:\t" << this << endl;
#endif //DEBUG
		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BITDestructor:\t" << this << endl;
#endif //DEBUG
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
		T& operator*()
		{
			return Temp->Data;
		}

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		friend class Iterator;
		friend class ReverseIterator;
	};
public:
	class Iterator :public BaseIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
		}

		Iterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return* this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

		Iterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return* this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ReverseIterator :public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
	};
	size_t getSize()const;
	const Iterator begin()const;
	Iterator begin();
	const Iterator end()const;
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	List();
	List(int size);
	List(const initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();
	//               Operators:
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);
	T& operator[](int index);
	//               Adding elements:
	void puch_front(T Data);
	void puch_back(T Data);
	void insert(unsigned int Index, T Data);
	//            Erasing elements:
	void pop_front();
	void pop_back();
	void erase(int index);
	//            Methods:
	void print();
	void print_reverse();
};

template<typename T>size_t List<T>::getSize()const
{
	return size;
}
template<typename T>const typename List<T>::Iterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>const typename List<T>::Iterator List<T>::end()const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(int size)
{
	while (size--)puch_back(0);
}
template<typename T>List<T>::List(const initializer_list<T>& il)
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)puch_back(*it);
}
template<typename T>List<T>::List(const List<T>& other)
{
	for (T i : other)puch_back(i);
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(List<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "MoveConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//               Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (T i : other)puch_back(i);
	cout << "CopyAssignment:\t" << this << endl;
}
template<typename T>List<T>& List<T>::operator=(List<T>&& other)
{
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "MoveAssignment:\t" << this << endl;
	return *this;
}
template<typename T>T& List<T>::operator[](int index)
{
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	return Temp->Data;
}

//               Adding elements:
template<typename T>void List<T>::puch_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::puch_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(unsigned int Index, T Data)
{
	if (Index > size)return;
	if (Index == 0)
	{
		puch_front(Data);
		return;
	}
	if (Index == size)
	{
		puch_back(Data);
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//            Erasing elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}

template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>void List<T>::erase(int index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}
	if (index >= size)return;

	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	//1)Исключаем удаляемый элемент из списка:
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	//2) Удаляем элемент из памяти:
	delete Temp;
}

//            Methods:
template<typename T>void List<T>::print()
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: \t" << size << endl;
}
template<typename T>void List<T>::print_reverse()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: \t" << size << endl;
}

///////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (T i : right)cat.puch_back(i);
	return cat;
}

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
//#define ITERATORS_CHECK
//#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK
#define TEMPLATES_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер списка: "; cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
		list.puch_back(rand()%100);
	/*list.print();
	list.pop_back();*/
	list.print();
	cout << delimiter << endl;
	list.print_reverse();
	int index;
	int value;
	cout << delimiter << endl;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	cout << delimiter << endl;
	list.print();
	cout << delimiter << endl;
	list.print_reverse();
	cout << delimiter << endl;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	cout << delimiter << endl;
	list.print_reverse();
	cout << delimiter << endl;
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)list[i] = rand()%100;
	for (size_t i = 0; i < list.getSize(); i++)cout << list[i] << tab;
	cout << endl;
	list.print();
#endif // SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13 ,21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << delimiter << endl;
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef COPY_METHODS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();
	List list2 = list1;//CopyConstructor
	//List list2;
	//list2 = list1;//CopyAssignment
	list2.print();
#endif // COPY_METHODS_CHECK

#ifdef MOVE_METHODS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	cout << delimiter << endl;
	//List list3 = list1 + list2;//MoveConstructor
	List<int> list3;
	list3 = list1 + list2;//MoveAssignment
	cout << delimiter << endl;
	list3.print();
#endif // MOVE_METHODS_CHECK

	List<int> i_list = { 3,5,8,13,21 };
	i_list.print();
	List<double> d_list = { 2.4,3.14,5.2,8.3 };
	d_list.print();
	List<string> s_list = { "What", "can", "I", "do" };
	for (string i : s_list)cout << i << tab; cout << endl;
}