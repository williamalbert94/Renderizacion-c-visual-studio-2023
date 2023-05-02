#ifndef COLOR_H
#include "Color.h"
#endif
#ifndef GEOMETRY_H
#include "geometria.h"
#endif

// creamos nuestros tipos de material
enum Type{
    REFLECTIVO,
    DIFUSO,
    REFRACTIVO
};

//creamos las propiedades de material!
class Material {
    
public:
    Color difuso, ambiente, especular;
    double kr,kt,kd,ior;
    Type type; 
    //"kr", "kt" y "kd" representan los coeficientes de reflexión especular, transmisión y difusa, respectivamente
    Material(){
        kr = 0.0;
        kt = 0.0;
        kd = 0.0;
        ior = 0.0;
    }
    virtual Color retornaambiente(Point p){ return ambiente;}
    Color retornadifuso(Point p){return difuso;}
    Color retornaespecular(Point p){return especular;}
    void defineambiente(Color c){ambiente = c;}
    void defineespecular(Color c){especular = c;}
    void definedifuso(Color c){difuso = c;}
};
