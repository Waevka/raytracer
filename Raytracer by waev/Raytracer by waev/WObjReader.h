#pragma once
#include <vector>
#include <list>
#include "WTriangle.h"
class WObjReader
{
public:
	WObjReader();
	~WObjReader();
	std::vector<WTriangle*> readFile(int &elems);
private:
	std::vector<std::string> split(const std::string &s, char delim);
	template<typename Out>
	void split(const std::string &s, char delim, Out result);
	WColor randomColor();
};

template<typename Out>
inline void WObjReader::split(const std::string & s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}
