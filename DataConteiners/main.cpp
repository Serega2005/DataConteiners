#include"Element.h"
#include"Element.cpp"
#include"Iterator.h"
#include"Iterator.cpp"
#include"ForwardList.h"
#include"ForwardList.cpp"


//#define BASE_CHECK
//#define ITERATOR_CHECK
//#define RANGE_BASED_ARRAY
//#define RANGE_BASED_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
#endif // BASE_CHECK

#ifdef ITERATOR_CHECK
	for (Iterator it = list.getHead(); it != nullptr; it++)
	{
		*it = rand() % 100;
	}
	list = list;
	list.print();
#endif // ITERATOR_CHECK

#ifdef BASE_CHECK
	/*cout << delimiter << endl;
	list.pop_front();
	list.pop_back();
	list.print();*/
	int value;
	int index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого значения: "; cin >> index;
	list.erase(index);
	list.print();

	/*cout << "Еще один список:\n";
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();*/
#endif // BASE_CHECK

	/*ForwardList list2 = list;
	list2.print();

	ForwardList list3;
	list3 = list2;
	list3.print();*/

#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	cout << size(arr) << endl;
	int razmer = 0;
	for (int i = 0; i < size(arr); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	for (int i : arr)//Renge-based for (цикл for для диапазона, для контейнера)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_ARRAY

#ifdef RANGE_BASED_LIST
	ForwardList<int> list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_LIST

	ForwardList<double> list = { 2.5, 3.14, 8.3, 5.4, 7.2 };
	for (double i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}