using namespace std;
#include <iostream>
#include <complex>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Matrix.h"
#include "tests.h"
template <class T>

void printMatrix(const Matrix<T>& matrix) {
	const Sequence<T>& flat = matrix.GetFlat();
	for (size_t i = 0; i < matrix.GetRowSize(); i++) {
		for (size_t j = 0; j < matrix.GetColSize(); j++) {
			cout << matrix.Get(j, i) <<" ";
		}
		cout << endl;
	}
}
template <class T>
Matrix<T> makeMatrix() {
	size_t rows;
	size_t cols;
	cout << "Enter the number of rows: " << endl;
	cin >> rows;
	cout << "Enter the number of cols: " << endl;
	cin >> cols;
	Sequence<T>* tmp = new ArraySequence<T>;
 	for (size_t i = 0; i < rows; i++) {
		cout << "Input "<< cols <<" numbers in row #" << i << endl;
		for (size_t j = 0; j < cols; j++) {
			T item;
			if (typeid(T) == typeid(complex<double>))
			{
				double real, imag;
				cout << "Input real part: ";
				cin >> real;
				cout << "Input image part: ";
				cin >> imag;
				complex<double>* comp = (complex<double>*)&item;
				comp->real(real);
				comp->imag(imag);
				tmp->Append(item);
			}
			else
			{
				cin >> item;
				tmp->Append(item);
			}
				
		}
	}
	Matrix<T> c(tmp, rows, cols, true);
	return c;
}

void printChoice() {
	cout << endl << "Select an action:" << endl;
	cout << "1. Sum matrixes" << endl;
	cout << "2. Multiply by scalar" << endl;
	cout << "3. Sum row to row multiplyed by scalar" << endl;
	cout << "4. Swap rows" << endl;
	cout << "5. Swap cols" << endl;
	cout << "6. Multiply row by scalar" << endl;
	cout << "7. Sum row to row" << endl;
	cout << "8. Compute second norm of matrix" << endl;
	cout << "9. Compute first norm of matrix" << endl;
	cout << "10. Test" << endl;
	cout << ">";
}

template <class T>
void computer() {
	Matrix<T> a = makeMatrix<T>();
	printChoice();
	size_t choosenOption;
	cin >> choosenOption;
	if (choosenOption == 1)
	{
		cout << endl << "Input matrix to sum" << endl;
		Matrix<T> b = makeMatrix<T>();
		a.Sum(b);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 2)
	{
		cout << endl << "Input scalar to multiply" << endl;
		T scalar;
		cin >> scalar;
		a.Multiply(scalar);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 8)
	{
		T norma = a.computeNorm2();
		cout << endl << "Result: " << norma << endl;
	}
	else if (choosenOption == 4)
	{
		cout << endl << "Input first row index to swap" << endl;
		size_t first;
		cin >> first;
		cout << endl << "Input second row index to swap" << endl;
		size_t second;
		cin >> second;
		a.swapRows(first, second);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 5)
	{
		cout << endl << "Input first col index to swap" << endl;
		size_t first;
		cin >> first;
		cout << endl << "Input second col index to swap" << endl;
		size_t second;
		cin >> second;
		a.swapCols(first, second);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 6)
	{
		cout << endl << "Input first col index to swap" << endl;
		size_t first;
		cin >> first;
		cout << endl << "Input second col index to swap" << endl;
		T scalar;
		cin >> scalar;
		a.multiplyRow(first, scalar);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 7)
	{
		cout << endl << "Input first row index to multiply" << endl;
		size_t first;
		cin >> first;
		cout << endl << "Input scalar to multiply" << endl;
		size_t second;
		cin >> second;
		a.sumRows(first, second);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 3)
	{
		cout << endl << "Input first row index to swap" << endl;
		size_t first;
		cin >> first;
		cout << endl << "Input second row index to swap" << endl;
		size_t second;
		cin >> second;
		cout << endl << "Input scalar to multiply" << endl;
		T scalar;
		cin >> scalar;
		a.sumRows(first, second, scalar);
		cout << endl << "Result:" << endl;
		printMatrix(a);
	}
	else if (choosenOption == 9)
	{
		T norma = a.computeNorm1();
		cout << endl << "Result: " << norma << endl;
	}
	else if (choosenOption == 10)
	{
		test();
	}
	else
	{
		cout << endl << "Error on choice!" << endl;
	}
}

bool menu() {
	cout << "Select the type number: " << endl;
	cout << "1. Integer" << endl;
	cout << "2. Float" << endl;
	cout << "3. Complex" << endl;
	cout << "0. Exit" << endl;
	cout << ">";
	size_t choosenOption;
	cin >> choosenOption;
	switch (choosenOption)
	{
	case 1:
		computer<int>();
		return true;
	case 2:
		computer<float>();
		return true;
	case 3:
		computer<std::complex<double>>();
		return true;
	case 0:
		return false;
	default:
		cout << endl << "Error on choice!" << endl;
		break;
	}
}

int main() {
	//test();
	try {
		bool b_flag = true;
		while (b_flag)
		{
			b_flag = menu();
		}
		
	}
	catch (std::exception ex) {
		std::string s = ex.what();
		int k = 0;
	}

	return 0;
}