#include <iostream>
#include <time.h>
#include "WWorld.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;

	srand(time(NULL));

	WWorld world;
	world.draw();
	cout << "\n All finished.";
	cin.get();
	return 0;
}