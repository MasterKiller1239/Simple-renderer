#pragma once

#ifndef Picture_H
#define Picture_H

struct Color {
	int red, blue, green;
	Color()
	{
		red = green = blue = 0;
	}
	Color(int r, int g, int b)
	{
		red = r;
		green = g;
		blue = b;
	}
};
class Picture
{
public:
	Color color;
	Color* tab;
	float* depthbuffor;
	int width, height;
	float depth = 1.0f;
	Picture(int width, int height);
	Picture(Picture& picture);
	void Fillimage(Color color);

	
};


#endif