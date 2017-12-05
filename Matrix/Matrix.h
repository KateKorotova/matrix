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


	Matrix<Rational> operator ~() {		
		if (rowCount != colCount)
			throw exception("Impossible");
		int n = rowCount;
		Matrix <double> A(n,2*n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A.arr[i][j] = double((*this).arr[i][j]);
			}
		}
		for (int i = 0; i < n; i++)
			A.arr[i][n + i] = 1;

		for (int i = 0; i < n; i++) {
			double maxEl = abs(A.arr[i][i]);
			int maxRow = i;
			for (int k = i + 1; k<n; k++) {
				if (abs(A.arr[k][i]) > maxEl) {
					maxEl = abs(A.arr[k][i]);
					maxRow = k;
				}
			}			
			swap(A.arr[i], A.arr[maxRow]);

			for (int j = i+1; j < 2*n; j++) {
				A.arr[i][j] = A.arr[i][j] / A.arr[i][i];
			}			
			A.arr[i][i] = 1;

			for (int k = i + 1; k < n; k++) {
				double c = -A.arr[k][i];
				for (int j = i; j < 2*n; j++) {
					if (i == j) {
						A.arr[k][j] = 0;
					}
					else {
						A.arr[k][j] = A.arr[k][j] + c * A.arr[i][j];
					}
				}
			}
		}

		// triangle
		for (int i = n - 1; i > 0; i--) {
			for (int k = i - 1; k >= 0; k--) {
				double c = -A.arr[k][i];
				A.arr[k][i] = 0;
				for (int j = n; j < 2*n; j++)
					A.arr[k][j] = A.arr[k][j] + c * A.arr[i][j];
			}
		}
		Matrix<Rational> res(n,n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				res.arr[i][j] = Rational(A.arr[i][n + j]);
			}
		}
		return res;
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

	friend Matrix<T> Gaussian(Matrix<T> a, Matrix<T> b) {
		if (a.rowCount != a.colCount)
			throw exception("First matrix is not square.");
		if (!(b.rowCount == a.rowCount && b.colCount==1))
			throw exception("Second vector must be colomn and have equal element count as first.");

		int n = a.rowCount;

		Matrix<double> matrix(n, n + 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix.arr[i][j] = double(a.arr[i][j]);
			}
		}
		for (int i = 0; i < n; i++) {
			matrix.arr[i][n] = double(b.arr[i][0]);
		}

		for (int i = 0; i<n; i++) {
			// Search for maximum in this column
			double maxEl = abs(matrix.arr[i][i]);
			int maxRow = i;
			for (int k = i + 1; k<n; k++) {
				if (abs(matrix.arr[k][i]) > maxEl) {
					maxEl = abs(matrix.arr[k][i]);
					maxRow = k;
				}
			}

			// Swap maximum row with current row (column by column)
			swap(matrix.arr[i], matrix.arr[maxRow]);

			// Make all rows below this one 0 in current column
			for (int k = i + 1; k < n; k++) {
				double c = -double(matrix.arr[k][i]) / double(matrix.arr[i][i]);
				for (int j = i; j < n + 1; j++) {
					if (i == j) {
						matrix.arr[k][j] = 0;
					}
					else {
						matrix.arr[k][j] = matrix.arr[k][j] + c * matrix.arr[i][j];
					}
				}
			}
		}

		Matrix<double> x(n, 1);
		for (int i = n - 1; i >= 0; i--) {
			x.arr[i][0] = matrix.arr[i][n] / matrix.arr[i][i];
			for (int k = i - 1; k >= 0; k--) {
				matrix.arr[k][n] = matrix.arr[k][n] - matrix.arr[k][i] * x.arr[i][0];
			}
		}
		Matrix<T> ans(n, 1);
		for (int i = 0; i < n; i++)
			ans.arr[i][0] = T(x.arr[i][0]);
		return ans;
	}
};