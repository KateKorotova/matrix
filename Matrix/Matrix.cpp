#include "Matrix.h"
#include <string>


template <typename T>
ostream& operator << (ostream os, const Matrix<T>& a) {
	cout << "Enter the number of rows in the matrix" << endl; 
	cin >> a.rowCount;
	cout << "Enter the number of columns in the matrix" << endl; 
	cin >> a.colCount;
	cout << "Enter " << a.rowCount << "rows and " << a.colCount << "columns: " << endl;
	for (int i = 0; i < a.rowCount; i++) {
		string tmp;
		cin << tmp;
		if (tmp.size != a.rowCount)
			throw exception("You have entered too many values")
		for (int j = 0; j < a.rowCount; i++) {

		
	}
}

int main() {
	Matrix<double> a;
	Matrix<double> a;
}