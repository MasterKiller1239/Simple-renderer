#include "float4x4.h"
#include "float4.h"
#include "float4.cpp"
#include <iostream>
float float4x4::dot(const float4& a, const float4& b)
{
	float g = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	/*std::cout <<g<< std::endl;*/
	return g;
	
}

 float4 float4x4::mult(float4x4 m,const  float4& v)
{
	float4 v0(m[0].x, m[1].x, m[2].x, m[3].x);
	//std::cout << v0.x << "," << v0.y << "," << v0.z << "," << v0.w << std::endl;
	float4 v1(m[0].y, m[1].y, m[2].y, m[3].y);
	float4 v2(m[0].z, m[1].z, m[2].z, m[3].z);
	float4 v3(m[0].w, m[1].w, m[2].w, m[3].w);
	return float4(dot(v0,v),dot(v1, v), dot(v2, v), dot(v3, v));
}

//float4x4 float4x4::mul(const float4x4& m, float4x4 b)
//{
//	float4x4 a = transpose(m);
//	float4x4 r = float4x4(
//		float4(dot(a[0], b[0]), dot(a[1], b[0]), dot(a[2], b[0]), dot(a[3], b[0])),
//		float4(dot(a[0], b[1]), dot(a[1], b[1]), dot(a[2], b[1]), dot(a[3], b[1])),
//		float4(dot(a[0], b[2]), dot(a[1], b[2]), dot(a[2], b[2]), dot(a[3], b[2])),
//		float4(dot(a[0], b[3]), dot(a[1], b[3]), dot(a[2], b[3]), dot(a[3], b[3]))
//		);
//	return r;
//}
