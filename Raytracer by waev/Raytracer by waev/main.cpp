#include <iostream>
#include "WVector2.h"
#include "WVector3.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;
	WVector3 test(2, 2, 3);
	WVector3 norm(0, -1, 0);
	test = test * test;
	cout << test.toString();
	test = test.reflect(norm);
	cout << test.toString();
	cin.get();
	return 0;
}