#pragma once
#include <math.h>
#include <xkeycheck.h>
const float epsilon = 0.000001f;
class Vec3
{
public:

	float x, y, z;
Vec3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}
Vec3()
	: x(0), y(0), z(0)
{
}
Vec3 operator+(Vec3 v) { return Vec3(x + v.x, y + v.y, z + v.z); }
Vec3 operator-(Vec3 v) { return Vec3(x - v.x, y - v.y, z - v.z); }
Vec3 operator*(float f){ return Vec3(x * f,y * f,z * f); }
void operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

Vec3 cross(const Vec3& a, const Vec3& b);

void normalizeDo(void);
 static Vec3 normalize(Vec3 vector) 
{
	
	float len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	if (len > epsilon) { vector.x /= len; vector.y /= len, vector.z /= len; }
	else vector.x = vector.y = vector.z = 0;
	return vector;
}

 Vec3 operator-() const
 {
	 return Vec3(-x, -y, -z);
 }

 double Dot(Vec3 vec) const
 {
	 return x * vec.x + y * vec.y + z * vec.z;
 }
 Vec3 reflect(Vec3 v, Vec3 n) const
 {
	
	 return v-n*n.Dot(v)*2;
 }

  Vec3 operator*(const Vec3& v) const 
 {
	 return Vec3(x * v.x, y * v.y, z * v.z);
 }
 Vec3 operator*(const float& v) const
 {
	 return Vec3(x * v, y * v, z * v);
 }
 Vec3 operator/(const float& v) const
 {
	 return Vec3(x / v, y / v, z / v);
 }
 Vec3 operator+(const Vec3& v) const
 {
	 return Vec3(x + v.x, y + v.y, z + v.z);
 }
 Vec3 operator-(const Vec3& v) const
 {
	 return Vec3(x - v.x, y - v.y, z - v.z);
 }
 Vec3 saturate(Vec3 f) 
 {
	 f.x = f.saturate(f.x);
	 f.y = f.saturate(f.y);
	 f.z = f.saturate(f.z);
	 return f;
 }
 float saturate(float v) 
 {

	 if (v < 0) return 0;
	 else if (v > 1) return 1;
	 else return v;
	 
 }

 static Vec3 const zero;
 static Vec3 const one;
};
struct int3
{
	union {
		struct { int a, b, c; };
		int p[3];
	};
	int3(int a = 0, int b = 0, int c = 0) :a(a), b(b), c(c) {}
	int& operator[](int idx) { return p[idx]; };
};
