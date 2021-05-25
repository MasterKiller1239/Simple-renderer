#pragma once
#include "Light.h"
#include "Vec3.h"
class PointLight : public Light
{
public:
	PointLight(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular,float shininess) :
		Light(position, ambient, diffuse, specular,shininess) {}
	virtual ~PointLight() {};
	Vec3 calculate(Fragment& f, VertexProc& vp) const
	{

		Vec3 N = Vec3::normalize(vp.tr_obj2view3(f.normal));
		Vec3 V = vp.tr_obj2view4((-f.position));
		Vec3 L = position-V;
		L.normalizeDo();
		V.normalizeDo();
		Vec3 R = Vec3::normalize(L.reflect(L, N));
		float diff = L.saturate((L).Dot(N));
		Vec3 texSample(1, 1, 1);
		if (tex.height != NULL)
		{
			unsigned int c = static_cast<int>(tex.texture[int(f.tex.x * (tex.width - 1)) + int(f.tex.y * (tex.height - 1)) * tex.width]);
			unsigned int c1 = static_cast<int>(tex.texture[int(f.tex.x * (tex.width - 1)) + int(f.tex.y * (tex.height - 1)) * tex.width + 1]);
			unsigned int c2 = static_cast<int>(tex.texture[int(f.tex.x * (tex.width - 1)) + int(f.tex.y * (tex.height - 1)) * tex.width + 2]);
			texSample = Vec3(c/ 255.0, c1/ 255.0, c2/255.0);
			//std::cout << N.x << N.y << N.z << std::endl;
		}
		//std::cout << L.saturate((L).Dot(N)) << std::endl;
		float spec = pow(L.saturate(R.Dot(V)), shininess);
		//if (spec != 0)
			//std::cout << spec << std::endl;
		return L.saturate((ambient + diffuse * diff) * texSample + specular * spec);
	}
	Vec3 calculatep(Vec3 normal, VertexProc& vp, Vec3 pixelColor, Vec3 pixelPosition) const
	{
		Vec3 norm = Vec3::normalize(normal);
		Vec3 lightDir = Vec3::normalize(position- pixelPosition);
		Vec3 viewDir = Vec3::normalize(vp.viewDirectio - pixelPosition);
		Vec3 reflectDir = (lightDir).reflect(-lightDir, norm);
	
		float diff = lightDir.saturate(lightDir.Dot(norm));
		
		////std::cout << N.x << N.y << N.z << std::endl;

		////std::cout << diff << std::endl;
		float spec = pow(lightDir.saturate(viewDir.Dot(reflectDir)), shininess);
		return lightDir.saturate((ambient + diffuse * diff)+ specular * spec);
	}
protected:
private:



};

