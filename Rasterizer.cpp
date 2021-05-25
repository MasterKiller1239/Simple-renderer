#include "Rasterizer.h"
#include <iostream>


inline int min(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
inline int max(int a, int b, int c)
{
	return a < b ? (b < c ? c : b) : (a < c ? c : a);
}
inline int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
inline int min(int a, int b)
{
	if (a > b)
	{
		return b;
	
	}
	else
	{
		return a;
		
	}
}
void Rasterizer::triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3, Vec3 color1, Vec3 color2, Vec3 color3) {

	float y1 = (v1.y + 1) * pic.height * .5f;
	float y2 = (v2.y + 1) * pic.height * .5f;
	float y3 = (v3.y + 1) * pic.height * .5f;

	float x1 = (v1.x + 1) * pic.width * .5f;
	float x2 = (v2.x + 1) * pic.width * .5f;
	float x3 = (v3.x + 1) * pic.width * .5f;
	int minx = (int)min(x1, x2, x3);
	int maxx = (int)max(x1, x2, x3);
	int miny = (int)min(y1, y2, y3);
	int maxy = (int)max(y1, y2, y3);
	minx = max(minx, 0);
	maxx = min(maxx, pic.width - 1);
	miny = max(miny, 0);
	maxy = min(maxy, pic.height - 1);
	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;
	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;
	float lambda1den = 1.f / (-dy23 * dx31 + dx23 * dy31);
	float lambda2den = 1.f / (dy31 * dx23 - dx31 * dy23);

	bool topleft1 = false, topleft2 = false, topleft3 = false;
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { topleft1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { topleft1 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { topleft1 = true; }
	for (int y = maxy; y >= miny; y--)
	{

		for (int x = minx; x <= maxx; x++)
		{
			if ((dx12 * (y - y1) - dy12 * (x - x1) > 0 && !topleft1||
				dx12 * (y - y1) - dy12 * (x - x1) >= 0&&topleft1)
				&&
				(dx23 * (y - y2) - dy23 * (x - x2) > 0 && !topleft2 ||
					dx23 * (y - y2) - dy23 * (x - x2) >= 0 && topleft2)
				&&
				(dx31 * (y - y3) - dy31 * (x - x3) > 0 && !topleft3 ||
					dx31 * (y - y3) - dy31 * (x - x3) >= 0 && topleft3
					)
				)
		/*	if (dx12 * (y - y1) - dy12 * (x - x1) > 0 &&
				dx23 * (y - y2) - dy23 * (x - x2) > 0 &&
				dx31 * (y - y3) - dy31 * (x - x3) >0
				)*/
			{
				float lambda1 = (dy23 * (x - x3) - dx23 * (y - y3)) * lambda1den;
				float lambda2 = (dy31 * (x - x3) - dx31 * (y - y3)) * lambda2den;
				float lambda3 = 1 - lambda1 - lambda2;
			/*	Fragment f(Vec3(v1 * lambda1+ v2* lambda2+v3* lambda3),
					Vec3(v1 * lambda1 + v2 * lambda2 + v3 * lambda3))
				*/
				float depth = v1.z * lambda1 + v2.z * lambda2 + v3.z * lambda3;
				Vec3 c = (color1 * lambda1+ color2 *lambda2+ color3 *lambda3)*255;
				Color color;
				
				color.red = c.x;
				
				color.green = c.y;
				
				color.blue = c.z;
				/*pic.tab[x + y * pic.width] = color;*/
				if (depth < pic.depthbuffor[x + y * pic.width])
				{
					pic.tab[x + y * pic.width] = color;
					pic.depthbuffor[x + y * pic.width] = depth;
				}
				

			} 
		}
	
	}
};
void Rasterizer::trianglen(const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& n1, const Vec3& n2, const Vec3& n3, VertexProc& vp, Vec3 color1, Vec3 color2, Vec3 color3, const  Light& l)
 {

	float y1 = (v1.y + 1) * pic.height * .5f;
	float y2 = (v2.y + 1) * pic.height * .5f;
	float y3 = (v3.y + 1) * pic.height * .5f;

	float x1 = (v1.x + 1) * pic.width * .5f;
	float x2 = (v2.x + 1) * pic.width * .5f;
	float x3 = (v3.x + 1) * pic.width * .5f;
	int minx = (int)min(x1, x2, x3);
	int maxx = (int)max(x1, x2, x3);
	int miny = (int)min(y1, y2, y3);
	int maxy = (int)max(y1, y2, y3);
	minx = max(minx, 0);
	maxx = min(maxx, pic.width - 1);
	miny = max(miny, 0);
	maxy = min(maxy, pic.height - 1);
	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;
	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;
	float lambda1den = 1.f / (-dy23 * dx31 + dx23 * dy31);
	float lambda2den = 1.f / (dy31 * dx23 - dx31 * dy23);

	bool topleft1 = false, topleft2 = false, topleft3 = false;
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { topleft1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { topleft1 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { topleft1 = true; }
	for (int y = maxy; y >= miny; y--)
	{

		for (int x = minx; x <= maxx; x++)
		{
			if ((dx12 * (y - y1) - dy12 * (x - x1) > 0 && !topleft1 ||
				dx12 * (y - y1) - dy12 * (x - x1) >= 0 && topleft1)
				&&
				(dx23 * (y - y2) - dy23 * (x - x2) > 0 && !topleft2 ||
					dx23 * (y - y2) - dy23 * (x - x2) >= 0 && topleft2)
				&&
				(dx31 * (y - y3) - dy31 * (x - x3) > 0 && !topleft3 ||
					dx31 * (y - y3) - dy31 * (x - x3) >= 0 && topleft3
					)
				)
				/*	if (dx12 * (y - y1) - dy12 * (x - x1) > 0 &&
						dx23 * (y - y2) - dy23 * (x - x2) > 0 &&
						dx31 * (y - y3) - dy31 * (x - x3) >0
						)*/
			{
				float lambda1 = (dy23 * (x - x3) - dx23 * (y - y3)) * lambda1den;
				float lambda2 = (dy31 * (x - x3) - dx31 * (y - y3)) * lambda2den;
				float lambda3 = 1 - lambda1 - lambda2;
				Vec3 newColor = (color1 * lambda1 + color2 * lambda2 + color3 * lambda3);
				Vec3 newNormal = (n1 * lambda1 + n2 * lambda2 + n3 * lambda3);
				Vec3 newPos = (v1 * lambda1 + v2 * lambda2 + v3 * lambda3);
				Vec3 shadedColor = Vec3();
				/*Fragment f(Vec3(v1 * lambda1 + v2 * lambda2 + v3 * lambda3),
					Vec3(n1 * lambda1 + n2 * lambda2 + n3 * lambda3),
					color1
					, Vec3(n1 * lambda1 + n2 * lambda2 + n3 * lambda3)
				);*/
					
			//	f = l.calculate(f);
		
				float depth = v1.z * lambda1 + v2.z * lambda2 + v3.z * lambda3;
				Vec3 c = (color1 * lambda1 + color2 * lambda2 + color3 * lambda3) * 255;
				shadedColor += l.calculatep(newNormal, vp, newColor, newPos);
				shadedColor = shadedColor * 255.0f;
				Color color;

				color.red = shadedColor.x;

				color.green = shadedColor.y;

				color.blue = shadedColor.z;

				/*pic.tab[x + y * pic.width] = color;*/
				if (depth < pic.depthbuffor[x + y * pic.width])
				{
					pic.tab[x + y * pic.width] = color;
					pic.depthbuffor[x + y * pic.width] = depth;
				}


			}
		}

	}
};
