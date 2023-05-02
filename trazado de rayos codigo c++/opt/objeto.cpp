//calculamos la interseccion de luz objeto
//Comenzamos definiendo el objeto, sus atributos como el material y las componentes, $kr$, $kt$ e $kd$. La idea es que definido el objeto computaremos si el rayoo intersecta el objeto. La ecuacion para esto seria una ecuacion de segundo grado $at2 + bt + c = 0$, donde t se define como la Eq. \ref{eq:7}.
//
//
//\begin{ equation }
//t = -b ± \frac{ \sqrt{b ^ 2 - 4ac)} }{(2a)}
//\label{ eq:7 }
//\end{ equation }
//
//En donde $a = \hat{ d }·\hat{ d }$, $b = 2\hat{ d }·(o - c)$ e $c = (o - c)·(o - c) - r ^ 2$.Dentro de nuestra implementacion debemos evitar la autointerseccion y saber cual es nuestra backface.


#include "objeto.h"
#include <iostream>


void objeto::definematerial(Material * mat){
    m = mat;   
}

triangulo::triangulo(Point v1,Point v2, Point v3, Point no){
    p1 = v1;
    p2 = v2;
    p3 = v3;
    
    n = no;
    esluz = false;
}

esfera::esfera(Point p, double r){
    centro = p;
    radio = r;
    
    esluz = false;
}
#define EPS 1E-6

Point triangulo::retornainterseccion(rayo r)
{
    Point vertice0 = p1;
    Point vertice1 = p2;  
    Point vertice2 = p3;
    Point borde1, borde2, h, s, q;
    Point rayoVector = r.v;
    Point rayoorigen = r.p;

    float a,f,u,v;
    borde1 = vertice1 - vertice0;
    borde2 = vertice2 - vertice0;
    h = rayoVector.cross(borde2);
    a = borde1* (h);
    if (a > -EPS && a < EPS)
        return Point::Infinite();
    f = 1/a;
    s = rayoorigen - vertice0;
    u = f * (s*(h));
    if (u < 0.0 || u > 1.0)
        return Point::Infinite();
    q = s.cross(borde1);
    v = rayoVector * f * q;
    if (v < 0.0 || u + v > 1.0)
        return Point::Infinite();
    // En esta etapa, podemos calcular t para averiguar dónde se encuentra el punto de intersección en la línea.
    float t = borde2 * f  * q;
    if (t > EPS) //interseccion del rayo
    {
        Point opinterseccion = rayoorigen + rayoVector * t; 
        return opinterseccion;
    }
    else // Esto significa que hay una intersección de línea pero no una intersección de rayo.
        return Point::Infinite();
}

Point triangulo::retornanormal(Point p){
    n.normalize();
    return n;
}

Point esfera::retornanormal(Point p){
    Point ret = (p-centro);
    
    ret.normalize();
    return ret;
}

//transformacion geometrica solo para una esfera

Point esfera::translate(double tx, double ty, double tz) {
    double mat[4][4] = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}
    };

    double vec[4] = { tx, ty, tz, 1 };
    double res[4] = { 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i] += mat[i][j] * vec[j];
        }
    }

    return Point(res[0], res[1], res[2]);
}

bool resuelvecuadratica(const double &a, const double &b, const double &c, double &t0, double &t1)
{
    double eq_intersect = b * b - 4.0 * a * c;
    if (eq_intersect < 0) 
        return false;
    else if (eq_intersect == 0) 
    {
        t0 = t1 = - 0.5 * b / a;
    }
    else 
    {
        double q = (b > 0) ?
        -0.5 * (b + sqrt(eq_intersect)) :
        -0.5 * (b - sqrt(eq_intersect));
        t0 = q / a;
        t1 = c / q;
    }

    return true;
} 

Point esfera::retornainterseccion(rayo r){

    double t0 = 0, t1 = 0;
    
    Point p0 = r.p;
    Point direccionVector = r.v;


    Point normal = retornanormal(p0);

    Point len = p0 - centro; 


    double a = direccionVector*direccionVector; // v^2

    double b =  (direccionVector * len ) * 2;

    //c = ||p0 - c||^2 - r^2
    
    double c = len*len - (radio*radio); 

    if (resuelvecuadratica(a, b, c, t0, t1) == false)
    {
        return Point::Infinite();  
    }

    if (t0 > t1) std::swap(t0, t1); 

    double t = t0;

    if (t0 < 0) {
        t0 = t1; // if t0 es negativo, usamos t1 
        if (t0 < 0) return Point::Infinite(); // si son valores negatorivos
    } 

    Point pinterseccion = r.p + (r.v * t);

    return pinterseccion;
}
