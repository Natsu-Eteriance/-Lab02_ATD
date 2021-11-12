#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "LinkedList.h"
#include "Sequence.h"
#pragma once

template <class T>
class ListSequence : public Sequence<T> {
private:
	LinkedList<T> m_list;
	void checkIndex(size_t index) const {
		if (index >= m_list.GetLength() || index < 0) {
			throw std::out_of_range("LinkedList out of range");
		}
	};
public:
	ListSequence(const T* items, size_t count) : m_list(items, count) {};

	ListSequence() {};

	ListSequence(const LinkedList <T>& items) : m_list(items) {};

	virtual ~ListSequence() {};

	const T& GetFirst() const;
	const T& GetLast() const;
	const T& Get(size_t index) const;
	virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const;
	size_t GetLength() const;

	virtual void Append(const T& item);
	virtual void Prepend(const T& item);
	virtual void InsertAt(const T& item, size_t index);
	virtual Sequence <T>* Concat(Sequence <T>* list);
};

template <class T>
const T& ListSequence<T>::GetFirst() const {
	return m_list[0];
}

template <class T>
const T& ListSequence<T>::GetLast() const {
	return m_list[m_list.GetLength() - 1];;
}

template <class T>
const T& ListSequence<T>::Get(size_t index) const {
	checkIndex(index);
	return m_list[index];
}

template <class T>
size_t ListSequence<T>::GetLength() const {
	return m_list.GetLength();
}

template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(size_t startIndex, size_t endIndex)  const{
	checkIndex(startIndex);
	checkIndex(endIndex);

	Sequence<T>* newArr = new ListSequence<T>(*m_list.GetSubList(startIndex, endIndex));

	return newArr;
}

template <class T>
void ListSequence<T>::Append(const T& item) {
	m_list.Append(item);
}

template <class T>
void ListSequence<T>::Prepend(const T& item) {
	m_list.Prepend(item);
}

template <class T>
void ListSequence<T>::InsertAt(const T& item, size_t index) {
	m_list.InsertAt(index, item);
}
//
template <class T>
Sequence<T>* ListSequence<T>::Concat(Sequence <T>* list) {
	LinkedList<T>* newList = new LinkedList<T>;
	for (size_t i = 0; i < list->GetLength(); i++) {
		newList->Append(list->Get(i));
	}
	Sequence<T>* newArr = new ListSequence<T>(*m_list.Concat(newList));

	return newArr;
}