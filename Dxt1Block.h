#include "Vec3.h"
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include "float4.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma once 

class Dxt1Block
{
	unsigned int r0 : 5;
	unsigned int g0 : 6;
	unsigned int b0 : 5;
	unsigned int r1 : 5;
	unsigned int g1 : 6;
	unsigned int b1 : 5;
	unsigned int idx;

	unsigned int operator[](int i)
	{
		return 0x3 & (idx >> (i << 1));
	}
	Vec3 getColor0()
	{
		return Vec3(float(r0) / 31.f, float(g0) / 63.f, float(b0) / 31.f);
	}
	Vec3 getColor1()
	{
		return Vec3(float(r1) / 31.f, float(g1) / 63.f, float(b1) / 31.f);
	}
	int load(const char* fname, int w, int h)
	{
		unsigned int header[124 / 4];
		FILE* f = fopen(fname, "rb+");
		if (NULL == f) return -1;

		char filecode[4];
		fread(filecode, 1, 4, f);
		if (strncmp(filecode, "DDS ", 4) != 0)
		{
			fclose(f);
			return 2;
		}
		if (124 / 4 != fread(header, 4, 124 / 4, f))
		{
			return -3;
		}
		if (*(unsigned int*)&header[6]!=1)
		{
			return -4;
		}
		if (*(unsigned int*)&header[20] != 0x31545844)
		{
			return -5;
		}
		if (w!= header[3] || h != header[2]) return -6;
		Dxt1Block* buffer=new Dxt1Block[(w / 4) *(h / 4) ];
		fread(buffer, sizeof(Dxt1Block), (w / 4) * (h / 4),f);
			fclose(f);
			Vec3 c[4];
			for (int i = 0; i < (w / 4) * (h / 4); ++i)
			{
				c[0] = buffer[i].getColor0();
				c[1] = buffer[i].getColor1();
				c[2] = (c[0] + c[0] + c[1]) / 3.f;
				c[3] = (c[0] + c[1] + c[1]) / 3.f; int x = (i % (w / 4)) * 4;
				int y = (i / (w / 4)) * 4;
				for (int j = 0; j < 16; ++j)
				{
				int ox = j % 4;
				int oy = j / 4;
				int pos = (x + ox) + (h - 1 - y - oy) * w;
				Vec3 color = c[buffer[i][j]] * 255.f;
				/* col[pos] = 0xff000000 |
				((unsigned char)color.z) << 16 | 
					((unsigned char)color.y) << 8 |
					((unsigned char)color.x);*/
				}
			}
			delete[] buffer;
			return 0;
	}
};

