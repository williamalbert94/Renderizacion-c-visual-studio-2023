#include <iostream>
#include <fstream>

#include <math.h>
#include "opt/RayTracer.h"
#include <fstream>
#include "stb/stb_image_write.h"


using namespace std;
const int width = 200;
const int height = 200;

int fov = 55;

int sampling = 2;

int depth = 16;

rayTracer* raytracer;


int main(){

	string fileName;

	cout<< "\nResolution: \nWidth: "<< width << "\theight: " << height<< endl;


	cout<< "\nFov: " << fov << endl;

	fileName  = "esfera_sin_sombra_y_ambiente.ppm";
	raytracer = new rayTracer(escena::creaescena(width, fov),sampling, depth);

	cout<< "\nFile saved as: "<< fileName << endl;


    //render function
	float pixels[width][height][3];

	// psudocodigo:
		//Render(film, camera, scene)
			//for each pixel(i, j) in f ilm
				//xn, yn = film.GetSample(i, j)
				//ray = camera.GenerateRay(xn, yn)
				//c = scene.T raceRay(ray)
			//film.SetValue(i, j, c)


    for(int i = 0; i < width; i++){
		for (int j = 0; j < height; j++) {

			Color rad = raytracer->renderiza(i, j);
			std::cout << rad.r<< rad.g << rad.b << std::endl;

			pixels[i][j][0] = rad.r; 
			pixels[i][j][1] = rad.g; 
			pixels[i][j][2] = rad.b; 
		}
    }


	ofstream testimage;
	testimage.open(fileName, ios::binary | ios::out);
	testimage << "P3\n" << width << " " << height << endl << width - 1 << endl;
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++)
			{
				testimage << int(pixels[i][j][k] * (width - 1)) << " ";
			}
			testimage << "\t";	
		}
		testimage << "\n";	}

	testimage.close();


	return 0;
}
