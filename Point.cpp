#include "Point.h"
#include <iostream>
Point::Point() :Float3()
{
}
Point::~Point()
{
}
Point::Point(Float3& mat) :Float3(mat) {}
Point::Point(float x, float y, float z) : Float3(x, y, z) {}
Point::Point(std::initializer_list<float> list) : Float3(list) {}
std::ostream& operator<< (std::ostream& os, Point &p)
{
	os << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
	return os;
}
