#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#pragma once

template <class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const T* items, size_t count);
	LinkedList(const LinkedList <T>& list);
	virtual ~LinkedList();

	const T& GetFirst() const;
	const T& GetLast() const;

	const T& Get(size_t index) const;

	LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const;

	size_t GetLength() const;

	void Append(T item);
	void Prepend(T item);
	void InsertAt(size_t index, T item);

	LinkedList<T>* Concat(LinkedList<T>* list);

	T& operator[] (size_t index);
	const T& operator[] (size_t index) const;
private:
	size_t m_lenght;

	struct Node {
		T item;
		struct Node* next;
	};

	Node* m_head;
	Node* m_end;
};

template <class T>
LinkedList<T>::LinkedList() {
	m_lenght = 0;
	m_head = NULL;
	m_end = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const T* items, size_t count) {
	Node* tmp = new Node; 
	tmp->item = items[0];
	m_head = tmp;
	m_end = m_head;
	for (size_t i = 1; i < count; i++) {
		Node* tmp = new Node; 
		tmp->item = items[i];
		m_end->next = tmp;
		m_end = tmp;
	}
	m_lenght = count;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList <T>& list) {
	Node* tmp = list.m_head;
	m_lenght = list.m_lenght;
	m_head = new Node; 
	m_head->item = list.m_head->item;
	m_end = m_head;
	for (size_t i = 0; i < list.m_lenght-1; i++) {
		tmp = tmp->next;
		Node* tmpLocal = new Node; 
		tmpLocal->item = tmp->item;
		this->m_end->next = tmpLocal;
		this->m_end = tmpLocal;
	}
}
template <class T>
LinkedList<T>::~LinkedList() {
	Node* tmp1 = m_head;
	for (size_t i = 0; i < m_lenght-1; i++) {
		Node* tmp2 = tmp1;
		tmp1 = tmp1->next;
		delete tmp2;
	}
}
template <class T>
const T& LinkedList<T>::GetFirst() const {
	if (this->m_lenght == 0) {
		throw std::out_of_range("out of range");
	}
	return m_head->item;
}

template <class T>
const T& LinkedList<T>::GetLast() const {
	if (m_lenght == 0) {
		throw std::out_of_range("out of range");
	}
	return m_end->item;
}

template <class T>
const T& LinkedList<T>::Get(size_t index) const {
	if (index >= m_lenght || index < 0) {
		throw std::out_of_range("out of range");
	}
	struct Node* tmp = m_head;
	for (size_t i = 0; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp->item;
}

template <class T>
size_t LinkedList<T>::GetLength() const{
	return m_lenght;
}

template <class T>
T& LinkedList<T>::operator[] (size_t index) {
	if (index >= m_lenght || index < 0) {
		throw std::out_of_range("out of range");
	}
	struct Node* tmp = m_head;
	for (size_t i = 0; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp->item;
}
template <class T>
const T& LinkedList<T>::operator[] (size_t index) const{
	if (index >= m_lenght || index < 0) {
		throw std::out_of_range("out of range");
	}
	Node* tmp = m_head;
	for (size_t i = 0; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp->item;
}
template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(size_t startIndex, size_t endIndex) const {
	if (startIndex >= m_lenght || startIndex < 0 || endIndex >= m_lenght || endIndex < 0) {
		throw std::out_of_range("out of range");
	}
	Node* tmp = m_head;
	LinkedList<T>* newList = new LinkedList<T>();
	for (size_t i = 0; i < startIndex; i++) {
		tmp = tmp->next;
	}
	for (size_t i = startIndex; i <= endIndex; i++) {
		newList->Append(tmp->item);
		tmp = tmp->next;
	}
	return newList;
}

template <class T>
void LinkedList<T>::Append(T item) {
	m_lenght++;
	Node* tmp = new Node; 
	tmp->item = item;
	if (m_lenght > 1) {
		m_end->next = tmp;
		m_end = tmp;
	}
	else {
		m_head = tmp;
		m_end = tmp;
	}
}
template <class T>
void LinkedList<T>::Prepend(T item) {
	m_lenght++;
	Node* tmp = new Node; 
	tmp->item = item;
	if (m_lenght > 1) {
		tmp->next = m_head;
		m_head = tmp;
	}
	else {
		m_head = tmp;
		m_end = tmp;
	}
}
template <class T>
void LinkedList<T>::InsertAt(size_t index,T item) {
	if (index >= this->m_lenght || index < 0) {
		throw std::out_of_range("out of range");
	}
	m_lenght++;
	Node* tmp = new Node; 
	tmp->item = item;
	Node* search = m_head;
	for (size_t i = 0; i < index-1; i++) {
		search = search->next;
	}
	Node* buffer = search->next;
	search->next = tmp;
	tmp->next = buffer;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList<T>* newList = new LinkedList<T>(*this);
	newList->m_end->next = list->m_head;
	newList->m_end = list->m_end;
	newList->m_lenght += list->m_lenght;
	return newList;
}
