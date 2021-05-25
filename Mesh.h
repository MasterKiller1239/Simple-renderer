#pragma once
#include "Vertex.h"
#include "Rasterizer.h"

#include "VectorProc.h"
#include "Light.h"
#include "DirectionalLight.h"
#include <vector>

constexpr float pi = 3.14159265358979323846f;
constexpr float twoPi = 6.283185307179586f;
constexpr float oneOverPi = 0.3183098861837906f;
constexpr float piOver180 = 0.017453292519943f;



class Mesh
{
public:
	Mesh() {};
	virtual ~Mesh() {};
	virtual void draw( Rasterizer& r,  VertexProc& vp)
	{
		for (int i = 0; i < tSize; ++i)
		{
			
			r.triangle(vp.tr(vertices[indices[i].a].position),
				vp.tr(vertices[indices[i].b].position), 
				vp.tr(vertices[indices[i].c].position),
				Vec3(1.0f, .0f, 1.f), Vec3(.0f, 1.0f, 1.0f), Vec3(.0f, 1.0f, 0.f));
		

		}
	}
	virtual void draw(Rasterizer& r, VertexProc& vp,const  Light& l)
	{
		for (int i = 0; i < tSize; ++i)
		{

			r.triangle(vp.tr(vertices[indices[i].a].position),
				vp.tr(vertices[indices[i].b].position),
				vp.tr(vertices[indices[i].c].position),
				l.calculate(vertices[indices[i].a], vp),
				l.calculate(vertices[indices[i].b], vp),
				l.calculate(vertices[indices[i].c], vp));
			
			
	


		}
	}
	virtual void draws(Rasterizer& r, VertexProc& vp, const  Light& l)
	{
		Vec3 Color = Vec3(0.5f, 0.5f, 0.5f);
		for (int i = 0; i < tSize; ++i)
		{

			r.trianglen(vp.tr(vertices[indices[i].a].position),
				vp.tr(vertices[indices[i].b].position),
				vp.tr(vertices[indices[i].c].position),
				(vertices[indices[i].a].normal),
				(vertices[indices[i].b].normal),
				(vertices[indices[i].c].normal),
				vp,
				Color,
				Color,
				Color, l);


			;


		}
	}
	virtual void makeNormals()
	{
		for (int i = 0; i < vSize; ++i)
		{
			vertices[i].normal = Vec3::zero;
		}
		for (int i = 0; i < tSize; ++i)
		{
			Vec3 n = n.normalize(n.cross(
				vertices[indices[i].c].position - vertices[indices[i].a].position,
				vertices[indices[i].b].position - vertices[indices[i].a].position
			)

			);
			vertices[indices[i].a].normal += n;
			vertices[indices[i].b].normal += n;
			vertices[indices[i].c].normal += n;
		}
		for (int i = 0; i < vSize; ++i)
		{
			vertices[i].normal.normalizeDo();
		}

	}
protected:
	int vSize, tSize;
	Vertex* vertices;
	//std::vector<Triangle> triangles;
	int3* indices;
private:
};

