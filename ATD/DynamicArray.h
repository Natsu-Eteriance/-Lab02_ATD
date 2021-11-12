#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>

#pragma once

template <class T> 
class DynamicArray
{
public:

	DynamicArray():size(0),items(NULL){};
	DynamicArray(const T* items, size_t count);
	DynamicArray(size_t size);
	DynamicArray(const DynamicArray<T>& dynamicArray);
	virtual ~DynamicArray();

	const T& Get(size_t index) const;


	size_t GetSize() const;

	void Set(size_t index, T value);

	void Resize(size_t newSize);

	T& operator[] (size_t i);
	const T& operator[] (size_t i) const;
private:
	size_t size;
	T* items;
};


template <class T>
DynamicArray<T>::DynamicArray(size_t size) {
	items = new T[size];
	this->size = size;
}

template <class T>
DynamicArray<T>::DynamicArray(const T* items, size_t count) {
	this->items = new T[count];
	size = count;
	for (size_t i = 0; i < count; i++)
	{
		this->items[i] = items[i];
	}
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
	size = dynamicArray.GetSize();
	items = new T[size];

	for (size_t i = 0; i < size; i++)
	{
		items[i] = dynamicArray.Get(i);
	}
}

template <class T>
DynamicArray<T>::~DynamicArray() {
	if (items)
		delete[] items;
}

template <class T>
void DynamicArray<T>::Set(size_t i, T value) {
	if (i >= size || i < 0) {
		throw std::out_of_range("out of range");
	}
	items[i] = value;
}

template <class T>
const T& DynamicArray<T>::Get(size_t i) const {
	if (i >= size || i < 0) {
		throw std::out_of_range("out of range");
	}
	return items[i];
}

template <class T>
size_t DynamicArray<T>::GetSize() const {
	return size;
}

template <class T>
void DynamicArray<T>::Resize(size_t newSize) {
	// create a temporary buffer and copy values into it
	T* newArr = new T[newSize];
	for (size_t i = 0; i < newSize && i < size; i++)
	{
		newArr[i] = items[i];
	}

	// delete the old items buffer and set new size parameters
	delete[] items;
	size = newSize;

	// create new items memory and copy the data from the buffer
	items = new T[newSize];
	for (size_t i = 0; i < size; i++)
	{
		items[i] = newArr[i];
	}
	// delete temporary buffer
	delete[] newArr;
}

template <class T>
T& DynamicArray<T>::operator[] (size_t i) {
	return items[i];
}

template <class T>
const T& DynamicArray<T>::operator[] (size_t i) const {
	return items[i];
}
