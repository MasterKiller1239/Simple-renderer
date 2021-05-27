#pragma once
#include "Mesh.h"
class Sphere: public Mesh
{
public:
	Sphere(int horiz, int vert)
	{
		vSize = vert * (horiz + 2);
		tSize = 2 * vert * horiz;
		vertices = new Vertex[vSize];
		indices = new int3[tSize];
		const float pi = 3.1415926f;
		int yy;
		
		for (yy = 0; yy <= horiz + 1; ++yy)
		{
			float y = cos(pi / (horiz + 1.f) * (float)yy);
			float r = sqrt(1 - y * y);
			for (int rr = 0; rr < vert; ++rr)
			{
				float x = r * cos(2.f * pi / vert * rr);
				float z = r * sin(2.f * pi / vert * rr);
				this->vertices[rr + yy * vert].position = Vec3(x, y, z);
				this->vertices[rr + yy * vert].tex = Vec3(
					 float(rr) / float(vert ),
					 float(yy) / float(horiz ), 0
				);
			}
		}
		
		for (yy = 0; yy < horiz ; ++yy)
		{	
			for (int rr = 0; rr < vert; ++rr)
			{
				indices[rr + 2 * yy * (vert)] = int3(
				(rr+1)%vert +yy*vert,
					rr+vert+yy*vert,(rr+1)%vert+vert+yy*vert
				);
				indices[rr + vert + 2 * yy * (vert)] = int3(
					rr +  vert +  yy * vert,
					rr + 2 * vert + yy * vert, (rr + 1) % vert + vert + yy * vert
				);
			}

		}


	}
	virtual ~Sphere(){};
	protected:
private:
};

