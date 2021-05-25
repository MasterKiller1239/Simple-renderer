#include "Picture.h"


	
	Picture::Picture(int width, int height)
	{
		this->width = width;
		this->height = height;
		tab = new Color[width * height];
	}
	Picture::Picture(Picture& picture)
	{
		color = picture.color;
		this->width = picture.width;
		this->height = picture.height;
		tab = new Color[width * height];
		depthbuffor = new float[width * height];
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				depthbuffor[x + y * width] =depth;

				tab[x + y * width] = picture.tab[x + y * width];
			}
		}
	};
	void Picture::Fillimage(Color color)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				tab[x + y*width] = color;
			}
		}
	}

