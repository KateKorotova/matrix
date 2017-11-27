#include "Matrix.h"
#include <iostream>


int main()
{
	Matrix<int> a;
	Matrix<int> b;
	cin >> a; 
	cin >> b; 

	//cout << a + b << endl;
	cout << a * b << endl; 
	system("pause");
	return 0;
}