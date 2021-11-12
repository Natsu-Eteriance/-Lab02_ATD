using namespace std;
#include <iostream>
#include <complex>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Matrix.h"
void testDynamicArray() {
	int values[] = { 1, 2, 3, 4, 5, 6 };
	int values1[] = { 99, 98, 97 };
	auto sz = sizeof(values) / sizeof(int);
	DynamicArray<int> arr3(3);
	DynamicArray<int> arr1(values, sz);
	DynamicArray<int> arr2(arr1);
	arr2.Get(0);
	if (arr2.Get(0) == arr1.Get(0)) {
		cout << "DynamicArray initialization ok" << endl;
	}
	else
	{
		cout << "DynamicArray initialization failed" << endl;
	}
}
void testLinkedList() {
	int values[] = { 1, 2, 3, 4, 5, 6 };
	int values1[] = { 99, 98, 97 };
	auto sz = sizeof(values) / sizeof(int);
	LinkedList<int> list1(values, sz);
	LinkedList<int> list2(list1);
	//list2[1] = 99;
	list2.Append(3336);
	list2.Prepend(1488);
	int test[] = { 1488, 1, 2, 3, 4, 5, 6, 3336 };
	bool b_ok = true;
	for (size_t i = 0; i < 8; i++) {
		if (list2[i] != test[i]) {
			b_ok = false;
		}
	}
	if (b_ok)
		cout << "LinkedList ok" << endl;
	else
		cout << "LinkedList failed" << endl;
}

void testArraySequence() {
	int values[] = { 1, 2, 3, 4, 5, 6 };
	int values1[] = { 99, 98, 97 };
	auto sz = sizeof(values) / sizeof(int);
	Sequence<int>* ar = new ArraySequence<int>(values, sz);
	auto sz1 = sizeof(values1) / sizeof(int);

	Sequence<int>* ar1 = new ArraySequence<int>(values1, sz1);
	bool b_ok = true;;
	auto ar2 = ar->Concat(ar1);
	auto tf = ar->GetFirst();
	if (tf != 1)
		b_ok = false;
	auto tl = ar->GetLast();
	if (tl != 6)
		b_ok = false;
	auto ts = ar->GetLength();
	if (ts != 6)
		b_ok = false;
	auto subAr = ar->GetSubsequence(1, 5);
	auto tf1 = ar2->GetFirst();
	auto tl1 = ar2->GetLast();
	auto ts1 = ar2->GetLength();
	if (b_ok)
	{
		cout << "ArraySequence ok" << endl;
	}
	else {
		cout << "ArraySequence failed" << endl;
	}
}
void testListSequence() {
	int values[] = { 1, 2, 3, 4, 5, 6 };
	int values1[] = { 99, 98, 97 };
	auto sz = sizeof(values) / sizeof(int);
	Sequence<int>* ar = new ListSequence<int>(values, sz);
	auto sz1 = sizeof(values1) / sizeof(int);

	Sequence<int>* ar1 = new ListSequence<int>(values1, sz1);
	bool b_ok = true;;
	auto ar2 = ar->Concat(ar1);
	auto tf = ar->GetFirst();
	if (tf != 1)
		b_ok = false;
	auto tl = ar->GetLast();
	if (tl != 6)
		b_ok = false;
	auto ts = ar->GetLength();
	if (ts != 6)
		b_ok = false;
	auto subAr = ar->GetSubsequence(1, 5);
	auto tf1 = ar2->GetFirst();
	auto tl1 = ar2->GetLast();
	auto ts1 = ar2->GetLength();
	if (b_ok)
	{
		cout << "ListSequence ok" << endl;
	}
	else {
		cout << "ListSequence failed" << endl;
	}
}

void testMatrix() {
	int values[] = { 1, 2, 3, 4, 5, 6 };
	auto sz = sizeof(values) / sizeof(int);
	Sequence<int>* ar = new ListSequence<int>(values, sz);
	Matrix<int> c(ar, 2, 3, true);
	c.Multiply(3);
	c.Sum(c);
	const Sequence<int>& flat = c.GetFlat();
	bool b_ok = true;
	for (size_t i = 0; i < 6; i++) {
		if (flat.Get(i) != values[i] * 3 * 2) {
			b_ok = false;
		}
	}
	if (b_ok)
	{
		cout << "Matrix ok" << endl;
	}
	else {
		cout << "Matrix failed" << endl;
	}
}
void test() {
	testDynamicArray();

	testLinkedList();

	testArraySequence();

	testListSequence();

	testMatrix();
}

