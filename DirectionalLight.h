#pragma once
#include "Light.h"
#include "Vec3.h"
#include"stdlib.h"
#include "Texture.h"
class DirectionalLight: public Light
{
public:
	DirectionalLight(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :
		Light( position,  ambient,  diffuse,  specular, shininess){
		this->position.normalizeDo();
	}
	virtual ~DirectionalLight() {};
	 Vec3 calculate( Fragment& f,  VertexProc& vp) const
	{
		Vec3 L = position;
		Vec3 N = Vec3::normalize(vp.tr_obj2view3(f.normal));
		Vec3 V = Vec3::normalize(vp.tr_obj2view3((-f.position)));
		Vec3 R = Vec3::normalize(L.reflect(L,N));
		float diff = L.saturate(L.Dot(N));
		//std::cout << N.x << N.y << N.z << std::endl;
		Vec3 texSample(1,1,1);
		if (texture.textureHeight != 0)
		{
			unsigned int c = static_cast<int>(texture.colorData[int(f.tex.x*(tex.width-1))+ int(f.tex.y * (tex.height - 1)) * tex.width]);
			unsigned int c1 = static_cast<int>(texture.colorData[int(f.tex.x * (tex.width - 1)) + int(f.tex.y * (tex.height - 1)) * tex.width+1]);
			unsigned int c2 = static_cast<int>(texture.colorData[int(f.tex.x * (tex.width - 1)) + int(f.tex.y * (tex.height - 1)) * tex.width+2]);
			texSample = texture.getPixelColor(int(f.tex.x * (tex.width - 1)), int(f.tex.y * (tex.height - 1)) * tex.width);
			texSample = Vec3(c / 255.0, c1 / 255.0, c2 / 255.0);
		//	std::cout << texSample.x << texSample.y << texSample.z << std::endl;
		}
		//std::cout << diff << std::endl;
		float spec = pow(L.saturate(R.Dot(V)), shininess);
		if (shininess > 0)
			f.color = f.color.saturate((ambient + diffuse * diff) * texSample + specular * spec);
		else 	f.color = f.color * texSample;
		return f.color;
	}	 
	 Vec3 calculatep(Vec3 normal, VertexProc& vp, Vec3 pixelColor, Vec3 pixelPosition) const
	{
		 Vec3 norm = Vec3::normalize(normal);
		 Vec3 lightDir = -position ;
		 lightDir.normalizeDo();
		 Vec3 viewDir = Vec3::normalize(vp.viewDirectio - pixelPosition);
		 Vec3 reflectDir = (lightDir).reflect(-lightDir, norm);
		// std::cout << norm.x << norm.y << norm.z << std::endl;
		// std::cout << lightDir.x << lightDir.y << lightDir.z << std::endl;
		float diff =std::max(norm.Dot(lightDir),0.0);


		//std::cout << diff << std::endl;
		float spec = pow(lightDir.saturate(reflectDir.Dot(viewDir)), shininess);
		return lightDir.saturate( ( ambient + pixelColor * diff) + specular * spec);
	}
protected:
private:
};

