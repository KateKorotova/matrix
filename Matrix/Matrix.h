#pragma once
#include <iostream>
#include <vector>

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
		for (int i = 0; i < colCount; i++) 
			tmp.push_back(0);
		for (int j = 0; j < colCount; j++)
			arr[j] = tmp; 
	}

	Matrix<T> operator = (const Matrix<T>& a) {
		arr.swap(a.arr);
		rowCount = a.rowCount;
		colCount = a.rowCount;
		return (*this); 
	}

	Matrix<T> operator + (const Matrix<T>& a) {
		if (rowCount == a.rowCount && colCount == a.colCount) {
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					arr[i][j] = arr[i][j] + a.arr[i][j];
			return (*this);
		}
		else
			throw exception("Matrices have different sizes");
	}

	Matrix<T> operator - (const Matrix<T>& a) {
		if (rowCount == a.rowCount && colCount == a.colCount) {
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					arr[i][j] = arr[i][j] - a.arr[i][j];
			return arr;
		}
		else
			throw exception("Matrices have different sizes")
	}

	Matrix<T> operator * (const Matrix<T> & a) {
		if (colCount == a.rowCount) {
			int size = rowCount*a.colCount;
			Matrix<T> res(rowCount, a.colCount); 
			for (int i = 0; i < rowCount; i++)
				for (int j = 0; j < colCount; j++)
					for (int z = 0; z < colCount; z++)
						res.arr[i][j] = res.arr[i][j] + arr[i][z]*a.arr[z][j];

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