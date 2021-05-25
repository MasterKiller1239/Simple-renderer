#include "Vec3.h"

Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
void Vec3::normalizeDo(void)
{
	float len = sqrt(x * x + y * y + z * z);
	if (len > epsilon) { x /= len; y /= len, z /= len; }
	else x = y = z = 0;
}

Vec3 const Vec3::zero = Vec3(0, 0, 0);
Vec3 const Vec3::one = Vec3(1, 1, 1);