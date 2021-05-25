#pragma once
#include "Mesh.h"


class Cone : public Mesh
{
public:
	Cone(float r, float h, int sides)
	{

		vSize = sides+2;
		tSize = 2 * sides;
		vertices = new Vertex[vSize];
		indices = new int3[tSize];
		float step = (360.0f / static_cast<float>(sides)) * piOver180;
		int i=0;
		for (float angle = 0.0f; angle < twoPi; angle += step)
		{
			Vec3 p0 = pOnCircleY(angle, r);
			
			this->vertices[i].position = p0; /*Vec3(r * std::cos(angle),0, r * std::sin(angle) );*/
			
			i++;
				}
		
		this->vertices[i ].position = Vec3::zero;
		this->vertices[i + 1].position = Vec3(0.0f, h, 0.0f);
		int q = 0;
		for (int yy = 0; yy < sides; yy++)
		{
			
			indices[q] = int3(
				yy ,
				vSize - 2,( yy + 1) % (sides)
			);
			q++;

		
			indices[q] = int3(
				yy ,
				vSize - 1, (yy + 1) % (sides )
			);
			q++;
		}
		

	
		


	}
	Vec3 pOnCircleY(float angle, float radius, Vec3 center= Vec3::zero)
	{
		return { radius * std::cos(angle) + center.x,
				 center.y,
				 radius * std::sin(angle) + center.z };
	}
	virtual ~Cone() {};
protected:
private:



};

