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