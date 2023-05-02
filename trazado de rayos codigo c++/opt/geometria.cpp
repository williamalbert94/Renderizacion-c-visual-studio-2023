#include "geometria.h"

Point Point::Infinite(){
    return Point(1E20,1E20,1E20);
}
Point Point::cross(Point p){
    return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);   
}


void Point::normalize(){
    double l = this->length();
    x /= l;
    y /= l;
    z /= l;
}

Point::Point(double xo, double yo, double zo){
    x = xo;
    y = yo;
    z = zo;
}

Point Point::operator- (Point p){
    return Point(x-p.x,y-p.y,z-p.z);   
}

Point Point::operator*(double s){
    return Point(x*s,y*s,z*s);   
}

Point Point::operator+(Point p){
    return Point(p.x+x,p.y+y,p.z+z);   
}

bool Point::operator < (Point p){
    return (this->length() < (p).length());
}

// Dot product
double Point::operator* (Point p){
    return x*p.x+y*p.y+z*p.z;   
}

double Point::length(){
    return sqrt(x*x+y*y+z*z);
}

rayo::rayo(){
}

rayo::rayo(Point po, Point vo){
    p = po;
    v = vo;
    v.normalize();
    float length_v = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    d.x = -v.x / length_v;
    d.y = -v.y / length_v;
    d.z = -v.z / length_v;
}

rayo rayo::reflexion(Point normal, Point m){
    rayo ret;
    double tmp = -(normal*v);
    
    Point vo = v+(normal*tmp*2.0);
    
    Point p = Point(m.x,m.y,m.z);
    return rayo(p,vo);
}

rayo rayo::refraccion(Point normal, Point m, float n1, float n2) {
    rayo ret;
    float cos_theta1 = -(normal * v);
    float sin_theta1 = sqrt(1 - cos_theta1 * cos_theta1);
    float sin_theta2 = n1/n2 * sin_theta1;
    if (sin_theta2 > 1.0) {
        // Total internal reflection
        return reflexion(normal, m);
    }
    float cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);

    Point refract_dir = Point(
        (n1 / n2) * v.x + ((n1 / n2) * cos_theta1 - cos_theta2) * normal.x,
        (n1 / n2) * v.y + ((n1 / n2) * cos_theta1 - cos_theta2) * normal.y,
        (n1 / n2) * v.z + ((n1 / n2) * cos_theta1 - cos_theta2) * normal.z
    );

    Point p = Point(m.x, m.y, m.z);
    return rayo(p, refract_dir);
}
