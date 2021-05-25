#pragma once
#define PI 3.1415926
#include "float4x4.h"
#include "float4.h"
#include "Vec3.h"
#include<iostream>


class VertexProc
{
protected:
	float4x4 obj2World, world2view, view2proj;
	float4x4 obj2proj, obj2view;
	
public:
	Vec3 viewDirection;
	Vec3 viewDirectio;
	void setPerspective(float fovy, float aspect, float near, float far)
	{
		fovy *= PI / 360;
		//std::cout << fovy << std::endl;
		float f = cos(fovy) / sin(fovy);
		view2proj[0] = float4(f / aspect, 0, 0, 0);
		//std::cout << view2proj[0] .x << "," << view2proj[0] .y << "," << view2proj[0] .z << "," << view2proj[0].w << std::endl;
		view2proj[1] = float4(0, f, 0, 0);
		//std::cout << view2proj[1].x << "," << view2proj[1].y << "," << view2proj[1].z << "," << view2proj[1].w << std::endl;
		view2proj[2] = float4(0, 0, (far+near)/(near-far),-1);
		//std::cout << view2proj[2].x << "," << view2proj[2].y << "," << view2proj[2].z << "," << view2proj[2].w << std::endl;
		view2proj[3] = float4(0, 0,2* far * near / (near - far), 0);
		//std::cout << view2proj[3].x << "," << view2proj[3].y << "," << view2proj[3].z << "," << view2proj[3].w << std::endl;


	}
	void setIdentity(void)
	{
		obj2World[0] = float4(1.f, 0, 0, 0);
		obj2World[1] = float4(0, 1.f, 0, 0);
		obj2World[2] = float4(0, 0, 1.f, 0);
		obj2World[3] = float4(0, 0, 0, 1.f);
	}
	void setIdentityView(void)
	{
		world2view[0] = float4(1.f, 0, 0, 0);
		world2view[1] = float4(0, 1.f, 0, 0);
		world2view[2] = float4(0, 0, 1.f, 0);
		world2view[3] = float4(0, 0, 0, 1.f);
	}
	Vec3 tr(const Vec3& v)
	{
		float4 r = view2proj.mult(obj2proj, float4(v.x, v.y, v.z, 1));
		//std::cout << r.x << "," << r.y << "," << r.z << "," << std::endl;
		return Vec3(r.x / r.w, r.y / r.w, r.z / r.w);

	}
	Vec3 tr_obj2view4(const Vec3& v)
	{
		float4 r = obj2view.mult(obj2view, float4(v.x, v.y, v.z, 1));
		return Vec3(r.x , r.y, r.z );

	}
	Vec3 tr_obj2view3(const Vec3& v)
	{
		Vec3 r = obj2view.mult(obj2view, v);
		return r;

	}
	void setLookat(Vec3 eye, Vec3 center, Vec3 up)
	{
		viewDirectio = eye;
		Vec3 f = center - eye;
		 f.normalizeDo();
		 viewDirection = f;
		up.normalizeDo();
		Vec3 s;
		s=s.cross(f,up);
		Vec3 u;
		u=u.cross(s, f);

		world2view[0] = float4(s.x, u.x, -f.x, 0);
		world2view[1] = float4(s.y, u.y, -f.y, 0);
		world2view[2] = float4(s.z, u.z, -f.z, 0);
		world2view[3] = float4(0, 0, 0, 1.f);
		float4x4 m(float4(1.f, 0, 0, 0), float4(0, 1.f, 0, 0), float4(0, 0, 1.f, 0), float4(-eye.x, -eye.y, -eye.z, 1.f));
		world2view=world2view.mul(world2view, m);

	}
	void multbyTrans(Vec3 v)
	{
		float4x4 m(float4(1, 0, 0, 0), float4(0, 1, 0, 0), float4(0, 0, 1, 0), float4(v.x, v.y, v.z, 1));
		obj2World=obj2World.mul(obj2World, m);
	}
	void Scale(Vec3 v)
	{
		float4x4 m(float4(v.x, 0, 0, 0), float4(0, v.y, 0, 0), float4(0, 0, v.z, 0), float4(0, 0, 0, 1));
		obj2World = obj2World.mul(obj2World, m);
	}
	void transform(void)
	{
		obj2view=obj2view.mul(world2view, obj2World);
		obj2proj=obj2proj.mul(view2proj, obj2view);
	}
	void multbyRot(float a, Vec3 v)
	{
		float s = sin(a * PI / 180), c = cos(a * PI / 180);
		v.normalizeDo();
		float4x4 m(
			float4(v.x*v.x*(1-c)+c, v.y * v.x * (1 - c) + v.z*s, v.x * v.z * (1 - c) - v.y * s, 0),
			float4(v.x * v.y * (1 - c) - v.z*s, v.y * v.y * (1 - c) + c,  v.y*v.z+(1-c)+v.y*s, 0),
			float4(v.x * v.z * (1 - c) - v.y *s, v.y*v.z * (1 - c)-v.x*s, v.z * v.z * (1 - c) + c, 0),
			float4(0, 0, 0, 1));
		obj2World=obj2World.mul(obj2World, m);
	}
};


