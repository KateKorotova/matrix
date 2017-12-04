#pragma once
#include <iostream>
#include <vector>
#include "Rational.h"

using namespace std;

template <typename T>
class Matrix {
private:
	int rowCount;
	int colCount;
	vector <vector <T>> arr; 
public:
	Matrix<T>() {}
	Matrix<T>(int rc, int cc) {
		rowCount = rc; 
		colCount = cc;
		for (int i = 0; i < rowCount; i++)
			arr.push_back(vector<T>());
		vector<T> tmp; 
		Rational a(0, 1, 1);
		for (int i = 0; i < colCount; i++) 
			tmp.push_back(a);
		for (int j = 0; j < rowCount; j++)
			arr[j] = tmp; 
	}

	Matrix<T> operator = (const Matrix<T>& a) {
		Matrix b(a);
		arr.swap(b.arr);
		rowCount = b.rowCount;
		colCount = b.rowCount;
		return (*this); 
	}

	Matrix<T> operator + (const Matrix<T>& a) {
		Matrix res(*this); 
		if (rowCount == a.rowCount && colCount == a.colCount) {
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					res.arr[i][j] = res.arr[i][j] + a.arr[i][j];
			return res; 
		}
		else
			throw exception("Matrices have different sizes");
	}

	Matrix<T> operator - (const Matrix<T>& a) {
		Matrix res(*this);  
		if (rowCount == a.rowCount && colCount == a.colCount) {
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					res.arr[i][j] = res.arr[i][j] - a.arr[i][j];
			return res;
		}
		else
			throw exception("Matrices have different sizes");
	}

	Matrix<T> operator * (const Matrix<T> & a) {
		if (colCount == a.rowCount) {
			Matrix<T> res(rowCount, a.colCount); 
			for (int i = 0; i < rowCount; i++) {
				int j = 0;
				for (j; j < a.colCount; j++)
					for (int z = 0; z < a.rowCount; z++)
						res.arr[i][j] = res.arr[i][j] + arr[i][z] * a.arr[z][j];
			}
			return res; 
		}
		else
			throw exception("Matrices can`t be multiplied");
	}

	friend istream& operator >> (istream& os, Matrix<T>& a) {
		cout << "Enter the number of rows and columns in the matrix" << endl;
		cin >> a.rowCount >> a.colCount;
		cout << "Enter Matrix with " << a.rowCount << " rows and " << a.colCount << " columns: " << endl;
		for (int i = 0; i < a.rowCount; i++)
			a.arr.push_back(vector<T>());
		for (int i = 0; i < a.rowCount; i++) {
			vector<T> tmp;
			for (int i = 0; i < a.colCount; i++) {
				T k;
				cin >> k;
				tmp.push_back(k);
			}
			if (tmp.size() != a.colCount)
				throw exception("You have entered too many values");
			for (int j = 0; j < a.colCount; j++)
				a.arr[i].push_back(tmp[j]);
		}
		return os;
	}

	friend ostream& operator << (ostream& os, Matrix<T>& a) {
		for (int i = 0; i < a.rowCount; i++) {
			cout << "{";
			for (int j = 0; j < a.colCount; j++)
				cout << a.arr[i][j] << " ";
			cout << "\b}" << endl;
		}
		return os;
	}

};