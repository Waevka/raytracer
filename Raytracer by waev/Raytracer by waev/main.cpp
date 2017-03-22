#include <iostream>
#include "WVector2.h"
#include "WVector3.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;
	WVector2 test(2, 2);
	WVector2 test2(3, 3);
	WVector2 test3(test, test2);
	cout << test3.toString();
	cin.get();
	return 0;
}