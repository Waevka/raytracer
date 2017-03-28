#include <iostream>
#include "WWorld.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;

	WWorld world;
	world.draw();

	cin.get();
	return 0;
}