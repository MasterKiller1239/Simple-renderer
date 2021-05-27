#include "Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // !1
#include <math.h>
#include "Vec3.h"

Texture::Texture()
{
}

Texture::Texture(const char* filename, unsigned int desiredChannels)
{
	int width, height, channels;
	colorData = stbi_load(filename, &width, &height, &channels, desiredChannels);
	textureHeight = height;
	textureWidth = width;
}

Vec3 Texture::getPixelColor(const unsigned int& x, const unsigned int& y) const
{
	unsigned char r, g, b;
	r = colorData[y * textureWidth * 3 + x * 3 + 0];
	g = colorData[y * textureWidth * 3 + x * 3 + 1];
	b = colorData[y * textureWidth * 3 + x * 3 + 2];
	return Vec3(r/ 255.0, g / 255.0, b / 255.0);
}

Vec3 Texture::extractTextureColor(float u, float v)const
{
	int x = (int)((textureWidth - 1) * u);
	int y = (int)((textureHeight - 1) * v);
	while (x > textureWidth - 1)
	{
		x -= textureWidth - 1;
	}
	while (y > textureHeight - 1)
	{
		y -= textureHeight - 1;
	}
	while (x < 0)
	{
		x += textureWidth - 1;
	}
	while (y < 0)
	{
		y += textureHeight - 1;
	}
	return getPixelColor(x, y);
}