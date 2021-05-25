
#include <fstream>
#include <iostream>
#include "Rasterizer.h"
#include "Picture.h"
#include "VectorProc.h"
#include "Sphere.h"
#include "Cone.h"
#include "Torus.h"
#include "PointLight.h"
#include "Spotlight.h"
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class  Image {
public:
	Color* tab;
	int width, height;
	Image(int width, int height)
	{
		this->width = width;
		this->height = height;
		tab = new Color[width*height];
	}
	void Fillimage(Color color)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				tab[x + y*width] = color;
			}
		}
	}

};
int main() {
	int width = 512, height = 255;

	int  nrChannels;
	std::string filename = "wall.jpg";
	Texture tex;
	tex.texture = stbi_load(filename.c_str(), &tex.width, &tex.height, &nrChannels,3);
	int  nrChannels1;
	std::string filename1 = "wall2.jpg";
	Texture tex1;
	tex1.texture = stbi_load(filename1.c_str(), &tex1.width, &tex1.height, &nrChannels1, 3);

	/*if (data != nullptr && width1 > 0 && height1 > 0)
	{
		if (nrChannels == 3)
		{

			std::cout << "First pixel: RGB "
				<< static_cast<int>(data[0]) << " "
				<< static_cast<int>(data[1]) << " "
				<< static_cast<int>(data[2]);
		}
		}*/
	/*cin >> color.red;
	cin >> color.green;
	cin >> color.blue;
	cin >> width;
	cin >> height;*/
	Color color;
	color.blue = 0;
	color.red = 0;
	color.green = 0;
	Picture *obraz = new Picture(width, height);
	ofstream img("picture.ppm");
	img << "P3" << endl;
	img << obraz->width << " " << obraz->height << endl;
	img << "255"<< endl;
	obraz->Fillimage(color);
	VertexProc vp;
	VertexProc test;

	vp.setPerspective(75.f, 3.f / 3.f, 1.f, 1000.f);
	vp.setPerspective(45.f, 2.f, 1.f, 1000.f);
//	vp.setPerspective(120.f, 1.f, 1.f, 1000.f);
	Rasterizer r(*obraz);
	
	test.setPerspective(80.f, 1.f, 1.f, 1000.f);
	test.setLookat(Vec3(0, 0, 5.f), Vec3(0, 0, -1.f), Vec3(1, 1, 0));
	test.setIdentity();
	test.transform();

	test.setIdentity();
	//test.setIdentityView();
	//test.multbyTrans(Vec3(0.5, 0.5, 0.5));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	//test.multbyRot(-80.f, Vec3(0, 1, 0));
	test.transform();

	DirectionalLight light(Vec3(-1, 0, 0), Vec3(0.1f, .1f, .1f), Vec3(0.1f, .1f, .1f), Vec3(.5f, 1.0f, 1.f),10);
	DirectionalLight light2(Vec3(-1, 0, 0), Vec3(0.1f, .1f, .1f), Vec3(0.1f, .1f, .1f), Vec3(.5f, 1.0f, 1.f), 10);
	DirectionalLight light1(Vec3(-1, 0, 0), Vec3(0.1f, .1f, .1f), Vec3(0.5f, .5f, .5f), Vec3(.0f, .0f, 0.f), 0);
	light1.tex = tex;
	light.tex = tex;
	

	test.setIdentity();
	//test.setIdentityView();
	//test.multbyTrans(Vec3(0.5, 0.5, 0.5));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	//test.multbyRot(-80.f, Vec3(0, 1, 0));
	test.transform();

	Torus t(1.0f, 0.15f, 30, 30);
	t.makeNormals();
	test.setIdentity();
	test.multbyTrans(Vec3(1.0f, -1.5f, 0.0f));
	test.multbyRot(180.f, Vec3(-1, 0, 0));
	//test.multbyRot(90.f, Vec3(0, 0, 1));
	//test.multbyRot(45.f, Vec3(1, 1, 0));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	test.transform();
	//t.makeNormals();
//	t.draws(r, test, light);
	////t.draw(r, test);

	test.setIdentity();
	//test.setIdentityView();
	//test.multbyTrans(Vec3(1.5, 1.5, 1.5));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	//test.multbyRot(-80.f, Vec3(0, 1, 0));
	test.transform();
	Sphere s(31, 31);

	//s.draw(r, test);
	s.makeNormals();
	//s.draw(r, test,light);
	//s.draw(r, test, light1);
	test.setIdentity();
	test.multbyTrans(Vec3(-1.5f, 0.0f, 0.0f));
//	test.multbyRot(180.f, Vec3(-1, 0, 0));
	//test.multbyRot(90.f, Vec3(0, 0, 1));
	//test.multbyRot(45.f, Vec3(1, 1, 0));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	test.transform();
	
	//s.draws(r, test, light);
	s.draw(r, test, light);
	light2.tex = tex1;

	light.tex = tex1;
	test.setIdentity();
	
	test.transform();
	Sphere s2(31, 16);

	//s.draw(r, test);
	s2.makeNormals();
	//s.draw(r, test,light);
	//s.draw(r, test, light1);
	test.setIdentity();
	test.multbyTrans(Vec3(0.5f, -1.5f, 0.0f));
	//	test.multbyRot(180.f, Vec3(-1, 0, 0));
		//test.multbyRot(90.f, Vec3(0, 0, 1));
		//test.multbyRot(45.f, Vec3(1, 1, 0));
		//test.Scale(Vec3(0.5, 0.5, 0.5));
	test.transform();
	//s.draw(r, test);
	s2.draw(r, test, light2);


	test.setIdentity();

	test.transform();
	Sphere s3(31, 16);

	//s.draw(r, test);
	s3.makeNormals();
	//s.draw(r, test,light);
	//s.draw(r, test, light1);
	test.setIdentity();
	test.multbyTrans(Vec3(2.5f, -1.5f, 0.0f));
	//	test.multbyRot(180.f, Vec3(-1, 0, 0));
		//test.multbyRot(90.f, Vec3(0, 0, 1));
		//test.multbyRot(45.f, Vec3(1, 1, 0));
		//test.Scale(Vec3(0.5, 0.5, 0.5));
	test.transform();
	//s.draw(r, test);
	s3.draw(r, test, light1);

	test.setIdentity();
	//test.setIdentityView();
	test.multbyTrans(Vec3(2.5, 0.5, 0));
	//test.Scale(Vec3(0.5, 0.5, 0.5));
	//test.multbyRot(-80.f, Vec3(0, 1, 0));
	test.transform();
	
	Cone c(1.0f, 1.0f,20);
	//Sphere c(31, 31);
	//s.draw(r, test);
	c.makeNormals();
	//c.draw(r, test,light);
	test.setIdentity();
	test.multbyTrans(Vec3(1.5f, .0f, 0.0f));

	//test.Scale(Vec3(0.5, 0.5, 0.5));
	test.transform();
	//c.draw(r, test);
	//c.draws(r, test, light);


	for (int y = obraz->height-1; y >= 0; y--)
	{
		for (int x = 0; x < obraz->width; x++)
		{
			
			img << r.pic.tab[x+y*obraz->width].red << " " << r.pic.tab[x+ y * obraz->width].green << " " << r.pic.tab[x+ y * obraz->width].blue << endl;
		}
	}
		
	return 0;

}