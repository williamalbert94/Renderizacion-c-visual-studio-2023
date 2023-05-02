#include <iostream>
#include <fstream>
#include <math.h>
#include "RayTracer.h"
#include <fstream>
#include ""
using std::ofstream;
using std::ifstream;

// store width and height of the render
int width = 100;
int height = 100;

int fov = 55;

int depth = 12;

int superSampling = 4;

// Our ray tracer
RayTracer * rt;

int main(){

	string fileName;

	cout<< "\nResolution: \nWidth: "<< width << "\theight: " << height<< endl;


	cout<< "\nFov: " << fov << endl;

	fileName  = "escena1.ppm";
	rt = new RayTracer(Scene::initTestScene(width, fov),depth,superSampling);

	

	cout<< "\nFile saved as: "<< fileName << endl;

	cout<< "\nDepth level: "<< depth << endl;

	cout<< "\nSuperSampling level: "<< superSampling << endl;

    float pixels[width][height][4];
 //   for(int ctr = 0; ctr < height*width; ctr++){
 //   	int i = ctr % width;
 //   	int j = ctr / width;
 //   	Color rad = rt->calculate(i,j); // Calculate Ray Trace
 //   	pixels[i][j][0] = rad.r; //Red
 //   	pixels[i][j][1] = rad.g; //Green
 //   	pixels[i][j][2] = rad.b; //Blue
 //   	pixels[i][j][3] = 1.0; //Alpha
 //   }
 //   // once we are done calculating, we will write to file.
 //   ofstream testimage;
	//testimage.open(fileName,ios::binary | ios::out);
	//	testimage << "P3\n" << width << " " << height << endl << width-1 << endl;
	//for(int j = height-1; j >=0 ; j-- ) {
	//    for(int i = 0; i< width; i++){
	//		for(int k = 0; k < 3; k++)
	//		{
	//			// normalize color value to 0-255.
	//			// This assumes that the color values are in the
	//			// range [0,1].
	//			//char c = int(pixels[i][j][k]*255);
	//			testimage << int(pixels[i][j][k]*(width-1)) << " ";
	//			//testimage << c;
	//		}
	//		testimage << "\t";	// write tab
	//	} 
	//	testimage << "\n"; // Write new line
	//}
	//testimage.close();
    return 0;   
}
