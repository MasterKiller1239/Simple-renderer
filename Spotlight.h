
#pragma once
#include "Light.h"
#include "Vec3.h"

class Spotlight : public Light
{
public:
	Spotlight(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float shininess) :
		Light(position, ambient, diffuse, specular, shininess) {}
	virtual ~Spotlight() {};
	Vec3 calculate(Fragment& f, VertexProc& vp) const
	{
		float constant= 1.0f;
		float linear= 0.09f;
		float quadratic= 0.032f;
		Vec3 L = position;
		Vec3 viewPos =Vec3(0, 0, 5.f);
		Vec3 D = Vec3(0.0f,0.0f,-1.0f);
		float cutOff= cos(Convert(80));
		
		Vec3 lightDir = Vec3::normalize(L - f.position);
		float theta = lightDir.Dot( Vec3::normalize(-D));
		
		if (theta > cutOff)
		{
			//std::cout << theta << std::endl;
			Vec3 N = Vec3::normalize(vp.tr_obj2view3(f.normal));
			//std::cout << lightDir.x << lightDir.y << lightDir.z << std::endl;
			float diff = L.saturate(L.Dot(N));

			Vec3 V = Vec3::normalize(vp.tr_obj2view3((viewPos -f.position)));
			Vec3 R = Vec3::normalize(L.reflect(-lightDir, N));
			
			float spec = pow(L.saturate(R.Dot(V)), shininess);
			// attenuation
			float distance = length(L - f.position);
			float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
			//std::cout << attenuation << std::endl;
			
			diff *= attenuation;
			
			spec *= attenuation;
			return L.saturate(ambient + diffuse * diff + specular * spec);

		}
		else
			return L.saturate(ambient);

		}
	double Convert(double degree)const
	{
		double pi = 3.14159265359;
		 //std::cout << (degree * (pi / 180)) << std::endl;
		return (degree * (pi / 180));
	}
	float  length(Vec3 v)const
	{
		return (v.x * v.x + v.y * v.y + v.z * v.z);
	}
protected:
private:
};