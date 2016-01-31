#ifndef _GEODATA_H
#define _GEODATA_H
//utility data structure

namespace acoross {

struct Point
{
	Point(int ax, int ay) : x(ax), y(ay) {}

	int x, y;
};

} //namespace acoross

#endif //_GEODATA_H