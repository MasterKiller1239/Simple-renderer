#pragma once

#include "Vec3.h"
#include "Picture.h"
#include "Vertex.h"
#include "Light.h"
class Rasterizer
{
public:
	Picture pic;
	
	
	Rasterizer(Picture& picture) : pic(picture){

	}
	
		
	virtual ~Rasterizer() {}

	virtual void triangle(const Vec3 &v1, const Vec3 &v2 ,const Vec3& v3, Vec3 color1, Vec3 color2, Vec3 color3) ;
	virtual void trianglen(const Vec3& v1, const Vec3& v2, const Vec3& v3, 
		const Vec3& n1, const Vec3& n2, const Vec3& n3, VertexProc& vp, Vec3 color1, Vec3 color2, Vec3 color3,
		const  Light& l);
	void trianglena( Fragment& F,  Fragment& F2,  Fragment& F3, VertexProc& vp, Vec3 color1, Vec3 color2, Vec3 color3, const Light& l);
	
};

