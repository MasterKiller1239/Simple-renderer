#pragma once
#include "float4.h"
#include "Vec3.h"
class float4x4
{
public:
	float4 column[4];
	float4x4() {};
	float4x4(float4 a, float4 b, float4 c, float4 d) { column[0] = a; column[1] = b; column[2] = c; column[3] = d;}
	float4& operator[](int idx) { return column[idx]; }
	//float4x4 mul(const float4x4& m, float4x4 b);
	float dot(const float4& a, const float4& b);
	float4 mult(float4x4 m, const  float4& );
	float4x4 mul(const float4x4& m, float4x4 b)
	{
		float4x4 a = transpose(m);
		float4x4 r = float4x4(
			float4(dot(a[0], b[0]), dot(a[1], b[0]), dot(a[2], b[0]), dot(a[3], b[0])),
			float4(dot(a[0], b[1]), dot(a[1], b[1]), dot(a[2], b[1]), dot(a[3], b[1])),
			float4(dot(a[0], b[2]), dot(a[1], b[2]), dot(a[2], b[2]), dot(a[3], b[2])),
			float4(dot(a[0], b[3]), dot(a[1], b[3]), dot(a[2], b[3]), dot(a[3], b[3]))
		);
		return r;
	}
	Vec3 mult(float4x4 m, const  Vec3& v)
	{
		Vec3 v0(m[0].x, m[1].x, m[2].x);
		Vec3 v1(m[0].y, m[1].y, m[2].y);
		Vec3 v2(m[0].z, m[1].z, m[2].z);
		
		
		return Vec3(v0.Dot(v), v1.Dot(v), v2.Dot(v));
	}
	float4 dot(float4& a, float b)
	{
		return float4(a.x * b, a.y * b, a.z * b, a.w * b);
	}
	float4x4 transpose(float4x4 m)
	{

		float4x4 r;
		r[0]= float4(m[0].x, m[1].x, m[2].x, m[3].x);
		r[1] = float4(m[0].y, m[1].y, m[2].y, m[3].y);
		r[2] = float4(m[0].z, m[1].z, m[2].z, m[3].z);
		r[3] = float4(m[0].w, m[1].w, m[2].w, m[3].w);
		return r;

	}

};

