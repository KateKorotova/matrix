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

	friend Matrix<T> Gaussian(const Matrix<T> &a, const Matrix<T>& b) {
		if (a.rowCount != a.colCount)
			throw exception("First matrix is not square.");
		if (!(b.rowCount == a.rowCount && b.colCount==1))
			throw exception("Second vector must be colomn and have equal element count as first.");

		int n = a.rowCount;

		Matrix<T> matrix(n, n + 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix.arr[i][j] = a.arr[i][j];
			}
		}
		for (int i = 0; i < n; i++) {
			matrix.arr[i][n] = b.arr[i][0];
		}

		for (int i = 0; i<n; i++) {
			// Search for maximum in this column
			double maxEl = abs(double(matrix.arr[i][i]));
			int maxRow = i;
			for (int k = i + 1; k<n; k++) {
				if (abs(double(matrix.arr[k][i])) > maxEl) {
					maxEl = abs(double(matrix.arr[k][i]));
					maxRow = k;
				}
			}

			// Swap maximum row with current row (column by column)
			for (int k = i; k<n + 1; k++) {
				double tmp = matrix.arr[maxRow][k];
				matrix.arr[maxRow][k] = matrix.arr[i][k];
				matrix.arr[i][k] = tmp;
			}

			// Make all rows below this one 0 in current column
			for (int k = i + 1; k<n; k++) {
				T c = -matrix.arr[k][i] / matrix.arr[i][i];
				for (int j = i; j<n + 1; j++) {
					if (i == j) {
						matrix.arr[k][j] = 0;
					}
					else {
						matrix.arr[k][j] = matrix.arr[k][j] + c * matrix.arr[i][j];
					}
				}
			}
		}

		Matrix<T> x(n, 1);
		for (int i = n - 1; i >= 0; i--) {
			x.arr[i][0] = matrix.arr[i][n] / matrix.arr[i][i];
			for (int k = i - 1; k >= 0; k--) {
				matrix.arr[k][n] = matrix.arr[k][n] - matrix.arr[k][i] * x.arr[i][0];
			}
		}
		return x;
	}
};