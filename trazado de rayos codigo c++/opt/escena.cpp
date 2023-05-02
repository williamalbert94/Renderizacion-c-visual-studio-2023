#include "escena.h"
#include <iostream>

void escena::inicializacion(){
    indexO = 0;
}
escena::escena(Point * vo, Point * no, double f, int No){
    delta_v = vo;
    n = no;

    //calculo el fov en rad
    fov_rad = f * acos(-1) / 180.0;

    *n = (*n) * (1 / (2 * tan(fov_rad / 2.0)));
    Point uo = delta_v->cross(*n);
    uo.normalize();
    delta_u = new Point(uo.x, uo.y, uo.z);
    C = Point(0, 0, 0);
    N = No;

    indexO = 0;
    indexL = 0;
}

objeto * escena::retorna_objetos(){
    if(indexO == objetos.size()) return NULL;
    return objetos[indexO++];
}

Point escena::retorna_luces(){
    indexL++;
    return luces[indexL% luces.size()];
}

void escena::adicionaobjeto(objeto * o){
    objetos.push_back(o);   
}

void escena::adicionaluz(Point l){
    luces.push_back(l);
}

// origen camara
void escena::definecamara(Point * c){
    camara = c;
}

rayo escena::generarayo(double xo, double yo){
    double normx = (xo/N)-0.5;
    double normy = (yo/N)-0.5; 
    Point p = (*delta_u)*normx + (*delta_v)*normy + (* camara) + (*n);    
    rayo r = rayo(p, (p -(*camara)));
    return r;
}

escena * escena::creaescena(int N, int fov){

    // creo una escena nueva
    escena * escena1 = new escena(new Point(0,1.0,0),new Point(0,0,1.0),fov,N);  
    // esfera

    Material* paredback = new Material();
    paredback->type = DIFUSO;
    paredback->kr = 0.03;
    paredback->kd = 0.44;

    Material* new1 = new Material();
    new1->type = REFLECTIVO;
    new1->kr = 0;
    new1->kd = 0;
    new1->kt = 1.5;


    paredback->ambiente = Color(0.4, 0.25, 0.25, 1.0);
    paredback->difuso = Color(0.3, 0.6, 0.6, 1.0);
    paredback->especular = Color(0.2, 0.2, 0.2, 1.0);

    Material* lateral1 = new Material();
    lateral1->type = DIFUSO;
    lateral1->kr = 0.03;
    lateral1->kd = 0.44;

    lateral1->ambiente = Color(0.4, 0, 0, 1.0);
    lateral1->difuso = Color(0.8, 0, 0, 1.0);
    lateral1->especular = Color(0.2, 0.2, 0.2, 1.0);

    Material* lateral2 = new Material();
    lateral2->type = DIFUSO;
    lateral2->kr = 0.03;
    lateral2->kd = 0.44;

    lateral2->ambiente = Color(0, 0.4, 0, 1.0);
    lateral2->difuso = Color(0, 0, 0.8, 1.0);
    lateral2->especular = Color(0.2, 0.2, 0.2, 1.0);

    Material * surface = new Material();
    surface->type = DIFUSO;
    surface->kr = 0.03;

    surface->ambiente = Color(0.0,0.0,0.0,1.0);
    surface->difuso = Color(0.6,0.6,0.6,1.0);
    surface->especular = Color(0.2,0.2,0.2,1.0);

    Material* sphere2 = new Material();
    sphere2->type = REFLECTIVO;
    // give sphere some reflectivity;
    sphere2->kr = 0.85;
    sphere2->ambiente = Color(0.00, 0.00, 0.00, 1.0);
    sphere2->difuso = Color(0.0, 0.0, 0.0, 1.0);
    sphere2->especular = Color(0.0, 0.0, 0.0, 1.0);



    Material* sphere = new Material();
    sphere->type = DIFUSO;
    // defino las propiedades de mi material
    sphere->kr = 0.03;
    sphere->ambiente = Color(0,0.00,1,1.0);
    sphere->difuso = Color(0,.0,1,1.0);
    sphere->especular = Color(1,1,1,1.0);
    objeto * s1 = new esfera(Point(400.0,130.0,320.0),120.0);
    s1->definematerial(new1);
    escena1->adicionaobjeto(s1);

    Material* caja = new Material();
    caja->type = DIFUSO;
    // defino las propiedades de mi material
    caja->kr = 0.03;
    caja->ambiente = Color(0, 1, 0, 1.0);
    caja->difuso = Color(0, 1, 0, 1.0);
    caja->especular = Color(1, 1, 1, 1.0);


//caja coordenadas
    Point p1 = Point(0, 0, 0);
    Point p2 = Point(550, 0, 0);
    Point p3 = Point(0, 0, 560);
    Point p4 = Point(550, 0, 560);
    Point p5 = Point(560, 550, 0);
    Point p6 = Point(560, 550, 560);
    Point p7 = Point(0, 550, 560);
    Point p8 = Point(0, 550, 0);
    // make normals for triangulo
    Point n1 = Point(0.0, -1.0, 0.0);
    Point n2 = Point(0.0, 1.0, 0.0);
    Point n3 = Point(1.0, 0.0, 0.0);
    Point n4 = Point(-1.0, 0.0, 0.0);
    Point n5 = Point(0.0, 0.0, -1.0);
    
    ////piso
    
    objeto* t1 = new triangulo(p1, p3, p2, n2);
    objeto* t2 = new triangulo(p4, p2, p3, n2);


    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);


    t1->definematerial(surface);
    t2->definematerial(surface);

    //techo 
    t1 = new triangulo(p5, p7, p6, n1);
    t2 = new triangulo(p8, p7, p5, n1);
    t1->definematerial(surface);
    t2->definematerial(surface);

    //lateral2
    t1 = new triangulo(p3, p1, p8, n3);
    t2 = new triangulo(p3, p8, p7, n3);
    t1->definematerial(lateral2);
    t2->definematerial(lateral2);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    // espaldar
    t1 = new triangulo(p4, p3, p7, n5);
    t2 = new triangulo(p4, p7, p6, n5);
    t1->definematerial(paredback);
    t2->definematerial(paredback);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    //lateral1
    t1 = new triangulo(p4, p2, p5, n4);
    t2 = new triangulo(p4, p5, p6, n4);
    t1->definematerial(lateral1);
    t2->definematerial(lateral1);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);


    escena1->adicionaluz(Point(100.0, 800, 320.0));
    escena1->adicionaluz(Point(185.0, 2000.0, 169.0));

    escena1->definecamara(new Point(278,273,-500));

    // Now we will add in smaller box
 /*   Point v1 = Point(100, 165, 65);
    Point v2 = Point(52, 165, 225);
    Point v3 = Point(210, 165, 272);
    Point v4 = Point(260, 165, 114);
    Point v5 = Point(260, 0, 114);
    Point v6 = Point(260, 165, 114);
    Point v7 = Point(210, 165, 272);
    Point v8 = Point(210, 0, 272);
    Point v9 = Point(100, 0, 65);
    Point v10 = Point(100, 165, 65);
    Point v11 = Point(52, 0, 225);

    Point no1 = Point(0.0, 1.0, 0.0);
    Point no2 = Point(0.0, 0.0, -1.0);
    Point no3 = Point(-1.0, 0.0, 0.0);
    Point no4 = Point(1.0, 0.0, 0.0);
    Point no5 = Point(0.0, 0.0, 1.0);

    t1 = new triangulo(v2, v3, v1, no1);
    t2 = new triangulo(v4, v1, v3, no1);
    t1->definematerial(caja);
    t2->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    t1 = new triangulo(v7, v4, v9, no4);
    t2 = new triangulo(v5, v7, v8, no4);
    t1->definematerial(caja);
    t2->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    t1 = new triangulo(v9, v10, v4, no4);
    t2 = new triangulo(v9, v4, v5, no4);
    t1->definematerial(caja);
    t2->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    t1 = new triangulo(v11, v2, v10, no4);
    t2 = new triangulo(v11, v2, v9, no4);
    t1->definematerial(caja);
    t2->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);

    t1 = new triangulo(v8, v7, v2, no4);
    t2 = new triangulo(v8, v7, v11, no4);
    t1->definematerial(caja);
    t2->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);*/



    Point v1 = Point(50, 100, 50);
    Point v2 = Point(50, 100, 250);
    Point v3 = Point(250, 100, 250);
    Point v4 = Point(250, 100, 250);
    Point v5 = Point(200, 300, 200);

    Point n1_ = Point(0.0, -1.0, 0.0);
    Point n2_ = Point(0.0, 0.0, 1.0);
    Point n3_ = Point(1.0, 0.0, 0.0);
    Point n4_ = Point(0.0, 0.0, -1.0);


    t1 = new triangulo(v1, v2, v5, n1_);
    t2 = new triangulo(v2, v3, v5, n2_);
    objeto* t3 = new triangulo(v3, v4, v5, n3_);
    objeto* t4 = new triangulo(v4, v1, v5, n4_);
    t1->definematerial(caja);
    t2->definematerial(caja);
    t3->definematerial(caja);
    t4->definematerial(caja);
    escena1->adicionaobjeto(t1);
    escena1->adicionaobjeto(t2);
    escena1->adicionaobjeto(t3);
    escena1->adicionaobjeto(t4);
    
    return escena1;
}


