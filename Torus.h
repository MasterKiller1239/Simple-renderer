#pragma once
#include "Mesh.h"

class Torus : public Mesh
{
public:
	Torus(float r1, float r2, int nSegs, int nSides)
	{


		vSize = nSegs * nSides*2*3;
		tSize = nSegs * nSides * 2;
		vertices = new Vertex[vSize];
		indices = new int3[tSize];
		float segStep = twoPi / nSegs;
		float sideStep = twoPi / nSides;

		float currTheta = 0.0f;
		float nextTheta = segStep;
		float currPhi = 0.0f;
		float nextPhi = sideStep;
		int q = 0;
		int p = 0;
		for (int i = 0; i < nSegs; ++i)
		{
			for (int j = 0; j < nSides; ++j)
			{
			
	
				//nSides*i +j+q
				this->vertices[q].position = pOnTorus(currPhi, currTheta, r1, r2);
				q++;
				this->vertices[q].position = pOnTorus(nextPhi, currTheta, r1, r2);
				q++;
				this->vertices[q].position = pOnTorus(currPhi, nextTheta, r1, r2);
					indices[p] = int3(
				q-2,
				q-1,q
			);
					p++;
					q++;
				this->vertices[q].position = pOnTorus(currPhi, nextTheta, r1, r2);
				q++;
				this->vertices[q].position = pOnTorus(nextPhi, currTheta, r1, r2);
				q++;
				this->vertices[q].position = pOnTorus(nextPhi, nextTheta, r1, r2);
				
				indices[p] = int3(
					q - 2,
					q - 1, q
				);
				q++;
				p++;
				currPhi += sideStep;
				nextPhi += sideStep;
			}
			currTheta += segStep;
			nextTheta += segStep;
		}



	}
	Vec3 pOnTorus(float phi, float theta, float r1, float r2)
	{
		return { std::cos(theta) * (r1 + std::cos(phi) * r2),
			std::sin(theta) * (r1 + std::cos(phi) * r2),
			std::sin(phi) * r2 };
	}
	virtual ~Torus() {};
protected:
private:

};

