#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Matrix {
private:
	int rowCount;
	int colCount;
	vector <vector <T>> arr; 
public:
	Matrix(){}
	Matrix<T> operator = (const Matrix<T>& a) {
		arr.swap(a.arr);
		rowCount = a.rowCount;
		colCount = a.rowCount;
		return (*this); 
	}
	Matrix<T> operator + (const Matrix<T>& a) {
		if (rowCount == a.rowCount && colCount == a.colCount) {
			vector <vector <T>> res;
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					res[i][j] = arr[i][j] + a.arr[i][j];
			return res;
		}
		else
			throw exception("Matrices have different sizes")
	}
	Matrix<T> operator - (const Matrix<T>& a) {
		if (rowCount == a.rowCount && colCount == a.colCount) {
			vector <vector <T>> res;
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					res[i][j] = arr[i][j] - a.arr[i][j];
			return res;
		}
		else
			throw exception("Matrices have different sizes")
	}

	Matrix<T> operator * (const Matrix<T> & a);

	friend ostream& operator << (ostream os, const Matrix<T>& a);

	friend istream& operator << (istream os, const Matrix<T>& a);

};