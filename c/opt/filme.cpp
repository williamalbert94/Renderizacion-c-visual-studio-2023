#include "Scene.h"
#include <iostream>

void Scene::startIteration(){
    indexO = 0;
}
Scene::Scene(Point * vo, Point * no, double f, int No){
    v = vo;
    n = no;

    //calculo el fov en rad
    fov_rad = f * acos(-1) / 180.0;

    *n = (*n) * (1 / (2 * tan(fov_rad / 2.0)));
    Point uo = v->cross(*n);
    uo.normalize();
    u = new Point(uo.x, uo.y, uo.z);
    C = Point(0, 0, 0);
    N = No;

    indexO = 0;
    indexL = 0;
}

Object * Scene::getNextObject(){
    if(indexO == objects.size()) return NULL;
    return objects[indexO++];
}

Point Scene::getNextLight(){
    indexL++;
    return lights[indexL%lights.size()];    
}

void Scene::addObject(Object * o){
    objects.push_back(o);   
}

void Scene::addLight(Point l){
    lights.push_back(l);
}

// Sets the origin of the camera
void Scene::setCamera(Point * c){
    camera = c;
}

Ray Scene::GenerateRay(double xo, double yo){
    double normx = (xo/N)-0.5;
    double normy = (yo/N)-0.5;
 
    Point po = (*u)*normx + (*v)*normy + (* camera) + (*n);
    
    Ray r = Ray(po, (po -(*camera)));
    return r;
}

Scene * Scene::initTestScene(int N, int fov){

    // make new scene with up vector, direction vector and fov
    Scene * ret = new Scene(new Point(0,1.0,0),new Point(0,0,1.0),fov,N);  
    // add sphere
    Material * surface = new Material();
    surface->type = DIFFUSE;
    surface->kr = 0.03;
    surface->ambient = Color(0.0,0.0,0.0,1.0);
    surface->diffuse = Color(0.8,0.8,0.8,1.0);
    surface->specular = Color(0.2,0.2,0.2,1.0);
    
    Material* sphere = new Material();
    sphere->type = DIFFUSE;
    // give sphere some reflectivity;
    sphere->kr = 0.1;
    sphere->ambient = Color(1,0.00,0,1.0);
    sphere->diffuse = Color(1,.0,0,1.0);
    sphere->specular = Color(1,0.0,0,1.0);
    Object * s1 = new Sphere(Point(400.0,130.0,320.0),120.0);
    // Make points for square
    Point p1 = Point(0,0,0);
    Point p2 = Point(550,0,0);
    Point p3 = Point(0,0,560);
    Point p4 = Point(550,0,560);
    Point p5 = Point(560,550,0);
    Point p6 = Point(560,550,560);
    Point p7 = Point(0,550,560);
    Point p8 = Point(0,550,0);
    // make normals for triangle
    Point n1 = Point(0.0,-1.0,0.0);
    Point n2 = Point(0.0,1.0,0.0);
    Point n3 = Point(1.0,0.0,0.0);
    Point n4 = Point(-1.0,0.0,0.0);
    Point n5 = Point(0.0,0.0,-1.0);
    s1->setMaterial(sphere);
    ret->addObject(s1);
    // Add in bottom square
    Object * t1 = new Triangle(p1,p3,p2,n2);
    Object * t2 = new Triangle(p4,p2,p3,n2);
    ret->addObject(t1);
    ret->addObject(t2);
    t1->setMaterial(surface);
    t2->setMaterial(surface);

    ret->addLight(Point(400.0, 800, 320.0));

    // set Camera location
    ret->setCamera(new Point(278,273,-500));

    
    return ret;
}



