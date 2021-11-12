#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "DynamicArray.h"
#include "Sequence.h"

#pragma once
template <class T>
class ArraySequence : public Sequence<T> {
	private:
		DynamicArray<T> m_items;
		void checkIndex(size_t index) const {
			if (index >= m_items.GetSize() || index < 0) {
				throw std::out_of_range("DynamicArray out of range");
			}
		};
	public:
		ArraySequence(const T* items, size_t count) : m_items(items, count) {};

		ArraySequence() {};

		 ArraySequence(const DynamicArray <T>& items) : m_items(items) {};

		 virtual ~ArraySequence() {};

		 const T& GetFirst() const;
		 const T& GetLast() const;
		 const T& Get(size_t index) const;
		 Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const;
		 size_t GetLength() const;

		 virtual void Append(const T& item);
		 virtual void Prepend(const T& item);
		 virtual void InsertAt(const T& item, size_t index);
		 virtual Sequence <T>* Concat(Sequence <T>* list);
};



template <class T>
const T& ArraySequence<T>::GetFirst() const {
	return m_items[0];
}

template <class T>
const T& ArraySequence<T>::GetLast() const {
	return m_items[m_items.GetSize() - 1];
}

template <class T>
const T& ArraySequence<T>::Get(size_t index) const {
	checkIndex(index);
	return m_items[index];
}

template <class T>
size_t ArraySequence<T>::GetLength() const {
	return m_items.GetSize();
}

template <class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
	checkIndex(startIndex);
	checkIndex(endIndex);
	Sequence<T>* newArr = new ArraySequence<T>;
	for (size_t i = startIndex; i <= endIndex; i++) {
		newArr->Append(m_items[i]);
	}
	
	return newArr;
}

template <class T>
void ArraySequence<T>::Append(const T& item) {
	m_items.Resize(m_items.GetSize() + 1);
	m_items.Set(m_items.GetSize() - 1, item);
}

template <class T>
void ArraySequence<T>::Prepend(const T& item) {
	m_items.Resize(m_items.GetSize() + 1);
	for (size_t i = 0; i < m_items.GetSize(); i++) {
		m_items.Set(i, m_items.Get(i - 1));
	}
	m_items.Set(0, item);
}

template <class T>
void ArraySequence<T>::InsertAt(const T& item, size_t index) {
	m_items.Resize(m_items.GetSize() + 1);
	for (size_t i = index + 1; i < m_items.GetSize(); i++) {
		m_items.Set(i, m_items[i - 1]);
	}
	m_items.Set(index, item);
}
//
template <class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence <T>* list) {
	Sequence<T>* newArr = new ArraySequence<T>(m_items);
	for (size_t i = 0; i < list->GetLength(); i++) {
		newArr->Append(list->Get(i));
	}

	return newArr;
}