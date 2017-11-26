#include "Matrix.h"
#include <string>


template <typename T>
ostream& operator << (ostream os, const Matrix<T>& a) {
	cout << "Enter the number of rows in the matrix" << endl;
	cin >> a.rowCount;
	cout << "Enter the number of columns in the matrix" << endl;
	cin >> a.colCount;
	cout << "Enter " << a.rowCount << "rows and " << a.colCount << "columns: " << endl;
	a.arr(a.rowCount - 1, a.colCount - 1);
	for (int i = 0; i < a.rowCount; i++) {
		string tmp;
		cin << tmp;
		if (tmp.size != a.rowCount)
			throw exception("You have entered too many values");
		for (int j = 0; j < a.colCount; j++)
			a.arr[i][j] = tmp[i];
	}
	return os; 
}

template <typename T>
istream& operator << (istream os, const Matrix<T>& a) {
	for (int i = 0; i << a.rowCount; i++) {
		for (int j = 0; j < a.colCount; j++
			cout << "{" << a.arr[i][j] << " ";
		cout <<"}" << endl;
	}
	return os; 
}


int main() {
	Matrix<int> a;
}