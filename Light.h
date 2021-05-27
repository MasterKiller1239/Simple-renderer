#pragma once
#include "Vec3.h"
#include "Vertex.h"
#include "VectorProc.h"
#include "Texture.h"
struct Texture1
{
	unsigned char* texture=nullptr;
	int width=NULL;
	int height = NULL;
};
class Light
{
public:
	Light(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :position{ position },
		ambient{ ambient }, diffuse{ diffuse }, specular{ specular }, shininess{ shininess }
	{
		
	};
	virtual ~Light() {};
	virtual Vec3 calculate( Fragment& f,  VertexProc& vp) const=0;
	virtual Vec3 calculatep(Vec3 normal, VertexProc& vp, Vec3 pixelColor, Vec3 pixelPosition) const = 0;
	Texture1 tex;
	Texture texture;
protected:
	Vec3 position, ambient, diffuse, specular;
	
	float shininess;
};

