#include <iostream>
#include "WVector2.h"
#include "WVector3.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;
	WVector2 test(2, 2);
	cout << test.toString();
	cin.get();
	return 0;
}