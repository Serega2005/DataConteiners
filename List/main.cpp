#include<iostream>
#include<string>
#include"List.h"
#include"List.cpp"
#include"Element.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

//#define DEBUG


template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
{
	this->Data = Data;
	this->pNext = pNext;
	this->pPrev = pPrev;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>bool List<T>::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}
template<typename T>T& List<T>::BaseIterator::operator*()
{
	return Temp->Data;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::Iterator::Iterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator++()	//Prefix increment
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}

template<typename T>typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::ReverseIterator::ReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::ReverseIterator& List<T>::ReverseIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ReverseIterator List<T>::ReverseIterator::operator++(int)
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ReverseIterator& List<T>::ReverseIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ReverseIterator List<T>::ReverseIterator::operator--(int)
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>size_t List<T>::getSize()const
{
	return size;
}

template <typename T>const typename List<T>::Iterator List<T>::begin()const
{
	return Head;
}
template <typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>const typename List<T>::Iterator List<T>::end()const
{
	return nullptr;
}
template <typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////


//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
//#define ITERATORS_CHECK
//#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK
#define TEMPLATES_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
	//int n;	cout << "Введите размер списка: "; cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
		list.push_back(rand() % 100);
	/*list.print();
	list.pop_front();*/
	list.print();
	list.print_reverse();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();

	cout << "Введите индекс удавляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.print_reverse();
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
	//List list = n;	//Type conversion from int to List
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)list[i] = rand() % 100;
	for (size_t i = 0; i < list.getSize(); i++)cout << list[i] << tab;
	cout << endl;
	list.print();
#endif // SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << "\n----------------------------------------------------------\n";
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef COPY_METHODS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();
	//List list2 = list1;	//CopyConstructor
	List list2;
	list2 = list1;	//CopyAssignment
	list2.print();
#endif // DEBUG

#ifdef MOVE_METHODS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	cout << delimiter << endl;
	//List list3 = list1 + list2;	//MoveConstructor
	List<int> list3;
	list3 = list1 + list2;	//MoveAssignment
	cout << delimiter << endl;
	list3.print();
#endif // MOVE_METHODS_CHECK

	List<int> i_list = { 3,5,8,13,21 };
	i_list.print();
	List<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	d_list.print();
	List<string> s_list = { "What", "can", "I", "do" };
	for (string i : s_list)cout << i << tab; cout << endl;
}