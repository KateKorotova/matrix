#include "Matrix.h"
#include <iostream>

int main()
{
	//Matrix<Rational> a;
	//Matrix<Rational> b;

	//cout << "Matrix A:" << endl;
	//cout << a << endl; 
	//cout << "Matrix B:" << endl; 
	//cout << b << endl; 
	//cout << "Matrix A+B:" << endl; 
	//cout << a + b << endl;
	//cout << "Matrix A-B:" << endl; 
	//Matrix<Rational> c = (a - b); 
	//cout << c << endl; 
	//cout << "Matrix A*B:" << endl; 
	//cout << a * b << endl; 
	//Matrix<Rational> res1;
	//Matrix<Rational> res2;
	//res1 = a*a - b*b; 
	//res2 = a*a - b*b;
	//cout << res1 << endl; 
	//cout << res2 << endl;
	Matrix<Rational> a;
	Matrix<Rational> b;
	cin >> a; 
	cin >> b; 
	cout << Gaussian(a,b);
	system("pause");
	return 0;
}