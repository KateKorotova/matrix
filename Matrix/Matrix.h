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
	Matrix<T>(){}
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

	friend istream& operator >> (istream& os, Matrix<T>& a) {
		cout << "Enter the number of rows in the matrix" << endl;
		cin >> a.rowCount;
		cout << "Enter the number of columns in the matrix" << endl;
		cin >> a.colCount;
		cout << "Enter Matrix with " << a.rowCount << " rows and " << a.colCount << " columns: " << endl;
		for (int i = 0; i < a.rowCount; i++)
			a.arr.push_back(vector<T>());
		for (int i = 0; i < a.rowCount; i++) {
			vector<T> tmp;
			for (int i = 0; i < a.rowCount; i++) {
				T k; 
				cin >> k; 
				tmp.push_back(k);
			}
			if (tmp.size() != a.colCount)
				throw exception("You have entered too many values");
			for (int j = 0; j < tmp.size(); j++) 
				a.arr[i].push_back(T(tmp[j]));
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