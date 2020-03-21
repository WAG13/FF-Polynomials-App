#include<iostream>
#include<vector>
#include<string>
#include"Polynom.h"
#include<RootsNumber.hpp>
using std::cout;
using std::endl;
using std::cin;

int main() {
	Polynom a(2, { -7, 4, 2 });
	Polynom b(3, { 1, 1, -3, 5 });
	a.show();
	b.show();
	cout << "   +" << endl;
	(a+a).show();
	(b+b).show();
	cout << "   -" << endl;
	(a-a).show();
	(b-b).show();

	return 0;
}