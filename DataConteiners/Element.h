#pragma once
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------\n"
//#define DEBUG

template<typename T>class Iterator;
template<typename T>class ForwardList;

template<typename T>class Element
{
	T Data;
	Element<T>* pNext;
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
	friend class Iterator<T>;
	friend class ForwardList<T>;
};