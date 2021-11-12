#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>

#pragma once
template <class T>
class Sequence {
public:
	virtual const T& GetFirst() const = 0;
	virtual const T& GetLast() const = 0;
	virtual const T& Get(size_t index) const = 0;
	virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const = 0;
	virtual size_t GetLength() const = 0;

	virtual void Append(const T& item) = 0;
	virtual void Prepend(const T& item) = 0;
	virtual void InsertAt(const T& item, size_t index) = 0;
	virtual Sequence <T>* Concat(Sequence <T>* list) = 0;

};