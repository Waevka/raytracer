#include <iostream>
#include "WWorld.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;

	WWorld world;
	world.draw();
	cout << "\n All finished.";
	cin.get();
	return 0;
}