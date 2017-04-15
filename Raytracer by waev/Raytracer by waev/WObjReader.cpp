#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iterator>
#include "WVector3.h"
#include "WObjReader.h"

WObjReader::WObjReader()
{
}


WObjReader::~WObjReader()
{
}

std::vector<WGeometricObject*> WObjReader::readFile(std::string filename)
{
	std::ifstream input;
	std::string text;
	std::vector<WVector3> vertexList;
	std::vector<WVector3> normalList;
	std::vector<WTriangle> triangleList;

	std::vector<WGeometricObject*> objects;

	input.open(filename.c_str());

	if (!input) {
		std::cout << "Could not open file";
	}

	for (; ; ) {

		std::getline(input, text);

		if (input.eof()) {
			break;
		}

		//std::cout << "\n" << text;

		if (text[0] == '#') {
			continue;
		}
		if (text[0] == '$') {
			continue;
		}

		//faces
		if (text[0] == 'f' || text[0] == 'F') {
			std::vector<std::string> v = split(text, '  ');
			int vertexIndices[3];
			int normalIndices[3];
			for (int i = 0; i < 3; i++) {
				int ind ;
				if (v.size() > 5) ind = i * 2 + 2;
				else ind = i+1;
				std::vector<std::string> v2 = split(v[ind], '//'); //TODO
				vertexIndices[i] = stoi(v2[0]) - 1;
				normalIndices[i] = stoi(v2[2]) - 1;
			}

			int v0ind = vertexIndices[0];
			int v1ind = vertexIndices[1];
			int v2ind = vertexIndices[2];
			int vnind = normalIndices[0];
			WVector3 v0 = WVector3(vertexList[v0ind]);
			WVector3 v1 = WVector3(vertexList[v1ind]);
			WVector3 v2 = WVector3(vertexList[v2ind]);
			WVector3 n = WVector3(normalList[vnind]);
			WColor c = randomColor();

			WTriangle* t = new WTriangle(v0, v1, v2, n, c);
			objects.push_back(t);
		}

		//vertex normals
		else if ((text[0] == 'v' || text[0] == 'V') &&
			(text[1] == 'n' || text[1] == 'N')) {
			std::vector<std::string> v = split(text, '  ');
			WVector3 vec;
			if (v.size() > 4) {
				WVector3 vec = WVector3(stof(v[2]), stof(v[4]), stof(v[6]));
			}
			else {
				WVector3 vec = WVector3(stof(v[1]), stof(v[2]), stof(v[3]));
			}
			normalList.push_back(vec);
		}

		//geometric vertex
		else if (text[0] == 'v' || text[0] == 'V') {
			std::vector<std::string> v = split(text, '  ');
			WVector3 vec;
			if (v.size() > 4) {
				WVector3 vec = WVector3(stof(v[2]), stof(v[4]), stof(v[6]));
			}
			else {
				WVector3 vec = WVector3(stof(v[1]), stof(v[2]), stof(v[3]));
			}
			vertexList.push_back(vec);
		}

	}

	input.close();

	return objects;

}

std::vector<std::string> WObjReader::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

WColor WObjReader::randomColor()
{	
	float randfloat1 = (float)(rand() % 99 + 1) / 100.0f;
	float randfloat2 = (float)(rand() % 99 + 1) / 100.0f;
	float randfloat3 = (float)(rand() % 99 + 1) / 100.0f;
	return WColor(randfloat1, randfloat2, randfloat3);
}
