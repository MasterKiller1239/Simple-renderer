#pragma once
#include "Vec3.h"
class Vertex
{
public:
	 Vec3  position, normal,hPos, tex;
	 Vec3 color;

	Vertex(){
		
			position = Vec3(0, 0, 0);
			 normal = Vec3(0, 0, 0);
			 tex = Vec3(0, 0, 0);
			 color = Vec3(1, 1, 1);
	}
	Vertex(const Vec3 & position, const Vec3& normal){
		{

			this->position = position;
			this->normal = normal;
		}
	}
	Vertex(const Vec3& position, const Vec3& normal, const Vec3& color, const Vec3& hPos) {
		{

			this->position = position;
			this->normal = normal;
			this->hPos = hPos;
			this->color = color;
		}
	}

};

//struct Vertexx
//{
//	Vec3 pos;
//};
//
//struct Vertex_C
//{
//	Vec3 pos;
//	Color col;
//};
//
//struct Vertex_N
//{
//	Vec3 pos;
//	Vec3 norm;
//};
//
//struct Vertex_NC
//{
//	Vec3 pos;
//	Vec3 norm;
//	Color col;
//};
typedef Vertex Fragment;