#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>


class Point {
    
public:
    double x,y,z;
    Point(double,double,double);
    Point(){x = y = z = 0.0;}
    Point cross(Point);
    void normalize(void);
    bool operator < (Point);
    Point operator - (Point);
    double operator * (Point);
    double length(void);
    Point operator * (double);
    Point operator + (Point);
    static Point Infinite(void);
};



class rayo {
    
public:
    rayo();
    rayo(Point,Point);

    rayo reflexion(Point, Point);
    rayo refraccion(Point normal, Point m, float n1, float n2);

    Point p,v,d; 



};

#endif

