#pragma once
#include "Vec3.h"
class float4
{
public:
	float x, y, z,w;
	float p[4];
	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}
	float4()
		: x(0), y(0), z(0), w(1.0f)
	{
		
	}
	
	float &operator[](int idx) { return p[idx]; };
};

