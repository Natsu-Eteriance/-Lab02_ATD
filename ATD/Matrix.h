#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include <cmath>
#pragma once
template <class T>
class Matrix
{
private:
	size_t m_colsize; //rowcount
	size_t m_rowsize; //colcount
	Sequence<T>* m_matrix;
	const size_t getPos(size_t x, size_t y) const;
	Matrix() { m_colsize = 0; m_rowsize = 0; };
public:
	Matrix(bool Array);
	Matrix(const Sequence<T>* matrix, size_t rows, size_t cols, bool Array);

	size_t GetColSize() const;
	size_t GetRowSize() const;

	const Sequence<T>& GetFlat() const;

	void Sum(const Matrix<T>& matrix);
	void Multiply(const T& scalar);
	const T& computeNorm1() const;
	const T& computeNorm2() const;

	void swapRows(size_t firstRowIndex, size_t secondRowIndex);
	void swapCols(size_t firstColIndex, size_t secondColIndex);
	void multiplyRow(size_t row, T scalar);
	void sumRows(size_t rowToChange, size_t rowData);
	void sumRows(size_t rowToChange, size_t rowData, T scalar);

	const T& Get(size_t row, size_t col) const;
};
template <class T>
Matrix<T>::Matrix(bool Array) {
	m_rowsize = 0;
	m_colsize = 0;
	if (Array)
		m_matrix = new ArraySequence<T>;
	else
		m_matrix = new ListSequence<T>;
}
template <class T>
Matrix<T>::Matrix(const Sequence<T>* matrix, size_t rows, size_t cols, bool Array) {
	if (Array)
		m_matrix = new ArraySequence<T>;
	else
		m_matrix = new ListSequence<T>; 
	if (rows*cols != matrix->GetLength()) {
		throw std::out_of_range("size of matrix isnt equal to given shape");
	}
	m_rowsize = rows;
	m_colsize = cols;
	for (size_t i = 0; i < matrix->GetLength(); i++) {
		m_matrix->Append(matrix->Get(i));
	}
}
template <class T>
const size_t Matrix<T>::getPos(size_t x, size_t y) const {
	if (x >= m_colsize || x < 0 || y >= m_rowsize || y < 0) {
		throw std::out_of_range("out of range");
	}
	size_t index = m_colsize * y + x;
	return index;
}

template <class T>
size_t Matrix<T>::GetColSize() const {
	return m_colsize;
}

template <class T>
size_t Matrix<T>::GetRowSize() const {
	return m_rowsize;
}

template <class T>
const Sequence<T>& Matrix<T>::GetFlat() const {
	return *m_matrix;
}

template <class T>
void Matrix<T>::Sum(const Matrix<T>& matrix) {
	if (matrix.GetColSize() != m_colsize || matrix.GetRowSize() != m_rowsize) {
		throw std::out_of_range("given shapes of matrixs arent equal");
	}
	const Sequence<T>& flatMatrix = matrix.GetFlat();
	Sequence<T>* tmp = new ArraySequence<T>;
	for (size_t i = 0; i < m_matrix->GetLength(); i++) {
		tmp->Append(m_matrix->Get(i) + flatMatrix.Get(i));
	}
	delete m_matrix;
	m_matrix = tmp;
}

template <class T>
void Matrix<T>::Multiply(const T& scalar) {
	Sequence<T>* tmp = new ArraySequence<T>;
	for (size_t i = 0; i < m_matrix->GetLength(); i++) {
		tmp->Append(m_matrix->Get(i) * scalar);
	}
	delete m_matrix;
	m_matrix = tmp;
}
template <class T>
const T& Matrix<T>::computeNorm2() const {
	T sum = m_matrix->GetFirst() * m_matrix->GetFirst();
	for (size_t i = 1; i < m_matrix->GetLength(); i++) {
		sum += m_matrix->Get(i) * m_matrix->Get(i);
	}
	return sqrt(sum);
}

template <class T>
const T& Matrix<T>::computeNorm1() const {
	T maxx = 0;
	size_t RowSize = GetRowSize(), ColSize = GetColSize();
	for (size_t i = 0; i < RowSize; i++)
	{
		T s = 0;
		for (size_t j = 0; j < ColSize; j++)
			s += abs(m_matrix->Get(i * RowSize + j));
		maxx = max(abs(maxx), abs(s));
	}
	return maxx;
}

template <class T>
void Matrix<T>::swapRows(size_t firstRowIndex, size_t secondRowIndex) {
	size_t min_index = min(firstRowIndex, secondRowIndex);
	size_t max_index = max(firstRowIndex, secondRowIndex);
	Sequence<T>* tmp = new ArraySequence<T>;
	size_t pos1 = getPos(0, min_index);
	size_t pos2 = getPos(0, max_index);
	for (size_t i = 0; i < pos1; i++) {
		tmp->Append(m_matrix->Get(i));
	}
	for (size_t i = pos2; i < pos2 + m_colsize; i++) {
		tmp->Append(m_matrix->Get(i));
	}
	for (size_t i = pos1 + m_colsize; i < pos2; i++) {
		tmp->Append(m_matrix->Get(i));
	}
	for (size_t i = pos1; i < pos1 + m_colsize; i++) {
		tmp->Append(m_matrix->Get(i));
	}
	for (size_t i = pos2 + m_colsize; i < m_matrix->GetLength(); i++) {
		tmp->Append(m_matrix->Get(i));
	}
	delete m_matrix;
	m_matrix = tmp;
}

template <class T>
void Matrix<T>::swapCols(size_t firstColIndex, size_t secondColIndex) {
	size_t min_index = min(firstColIndex, secondColIndex);
	size_t max_index = max(firstColIndex, secondColIndex);
	Sequence<T>* tmp = new ArraySequence<T>;

	for (size_t i = 0; i < m_rowsize; i++) {
		for (size_t j = 0; j < m_colsize; j++) {
			size_t index;
			if (j == min_index) {
				index = getPos(max_index, i);
			}
			else if (j == max_index) {
				index = getPos(min_index, i);
			}
			else {
				index = getPos(j, i);
			}
			tmp->Append(m_matrix->Get(index));
		}
	}

	delete m_matrix;
	m_matrix = tmp;
}
template <class T>
void Matrix<T>::multiplyRow(size_t row, T scalar) {
	Sequence<T>* tmp = new ArraySequence<T>;

	for (size_t i = 0; i < m_rowsize; i++) {
		for (size_t j = 0; j < m_colsize; j++) {
			size_t index;
			if (i == row) {
				index = getPos(j, i);
				tmp->Append(scalar*m_matrix->Get(index));
			}
			else {
				index = getPos(j, i);
				tmp->Append(m_matrix->Get(index));
			}
			
		}
	}

	delete m_matrix;
	m_matrix = tmp;
}

template <class T>
const T& Matrix<T>::Get(size_t row, size_t col) const{
	size_t index = getPos(row, col);
	return m_matrix->Get(index);
}

template <class T>
void Matrix<T>::sumRows(size_t rowToChange, size_t rowData) {
	Sequence<T>* tmp = new ArraySequence<T>;

	for (size_t i = 0; i < m_rowsize; i++) {
		for (size_t j = 0; j < m_colsize; j++) {
			size_t index;
			size_t indexSum;
			if (i == rowToChange) {
				index = getPos(j, rowToChange);
				indexSum = getPos(j, rowData);
				tmp->Append(m_matrix->Get(index) + m_matrix->Get(indexSum));
			}
			else {
				index = getPos(j, i);
				tmp->Append(m_matrix->Get(index));
			}

		}
	}

	delete m_matrix;
	m_matrix = tmp;
}
template <class T>
void Matrix<T>::sumRows(size_t rowToChange, size_t rowData, T scalar) {
	Sequence<T>* tmp = new ArraySequence<T>;

	for (size_t i = 0; i < m_rowsize; i++) {
		for (size_t j = 0; j < m_colsize; j++) {
			size_t index;
			size_t indexSum;
			if (i == rowToChange) {
				index = getPos(j, rowToChange);
				indexSum = getPos(j, rowData);
				tmp->Append(m_matrix->Get(index) + scalar*m_matrix->Get(indexSum));
			}
			else {
				index = getPos(j, i);
				tmp->Append(m_matrix->Get(index));
			}

		}
	}

	delete m_matrix;
	m_matrix = tmp;
}