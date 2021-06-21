#pragma once
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

//#define DEBUG

template<typename T>class List
{
	Element* Head;	//Указатель на начальный элемент списка
	Element* Tail;	//Указатель на конечный элемент списка
	unsigned int size;	//Размер списка

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();

		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
		T& operator*();
	};
public:
	class Iterator :public BaseIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
	};
	class ReverseIterator :public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		ReverseIterator& operator++();
		ReverseIterator operator++(int);
		ReverseIterator& operator--();
		ReverseIterator operator--(int);
	};
	size_t getSize()const;

	const Iterator begin()const;
	const Iterator end()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	explicit List(int size);
	List(const initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();

	//				Operators:
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);
	T& operator[](size_t index);

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(unsigned int Index, T Data);

	//			Erasing elements:
	void pop_front();
	void pop_back();
	void erase(size_t index);

	//			Methods:
	void print();
	void print_reverse();
};