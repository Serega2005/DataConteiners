#pragma once
#include<iostream>
#include<string>
#include"List.h"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

//#define DEBUG
template<typename T>
class Element
{
	T Data;		//«начение элемента
	Element* pNext;	//”казатель на следующий элемент
	Element* pPrev;	//”казатель на предыдущий элемент
public:
	Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
	~Element();
	friend class List<T>;
};