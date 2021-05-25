#pragma once
#include "Array3.h"
class Point :
	public Float3
{
public:
	Point();
	Point(Float3& mat);
	Point(float x, float y, float z);
	Point(std::initializer_list<float> list);
	~Point();
	friend std::ostream& operator<< (std::ostream& os, Point &mat);
};
typedef Point* PointPtr;

