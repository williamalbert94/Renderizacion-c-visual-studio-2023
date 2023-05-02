#include <vector>
#include <cstdlib>

#include "Material.h"
using namespace std;

// Objetos geometricos
class objeto {
protected:
    Material * m;
    bool esluz;
public:
    Material * retornamaterial(){return m;}
    void definematerial(Material *);
    bool luzdorigen(){ return esluz; }
    virtual Point retornainterseccion(rayo) = 0;
    virtual Point retornanormal(Point) = 0;
};


class triangulo : public objeto {
    
public:
    Point p1,p2,p3,n;
    Point retornainterseccion(rayo);
    Point retornanormal(Point);
    triangulo(Point, Point, Point, Point);
};

// A sphere object
class esfera : public objeto {
    Point centro;
    double radio;
public:
    Point retornanormal(Point);
    Point retornainterseccion(rayo);
    esfera(Point,double);
};


