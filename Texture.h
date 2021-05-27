#pragma once
#include "Vec3.h"



class Texture
{
public:
	Texture();
	Texture(const char* filename, unsigned int desiredChannels);

	Vec3 getPixelColor(const unsigned int& x, const unsigned int& y)const;
	Vec3 extractTextureColor(float u, float v)const;
	unsigned int textureWidth=0;
	unsigned int textureHeight=0;
	unsigned char* colorData = nullptr;
};

