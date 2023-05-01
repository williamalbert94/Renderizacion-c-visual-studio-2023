#include <vector>
#include <cstdlib>
#include "objeto.h"
#include <cmath>
using namespace std;

class escena {
    //variables para generar el rayo
    Point * n;
    double fov_rad;
    double fov;

    Point * delta_v;
    Point * delta_u;

    // localizacion de la camara virtual
    Point C;


    // Currently this rayo tracer only supports square N x N images
    // where N is the number of pixels in one direction.
    int N;
    

    //lista de objetos
    vector<objeto *> objetos;


    int indexL,indexO;
public:
    //lista de luces
    vector<Point> luces;
    Point * camara;
    escena(Point*,Point*,double,int);
    void inicializacion(void);
    objeto * retorna_objetos(void);
    Point retorna_luces(void);
    void adicionaobjeto(objeto *);
    void adicionaluz(Point);
    void definecamara(Point *);
    rayo generarayo(double,double);
    static escena* creaescena(int, int);
    static escena* creaescena1(int, int);

    
};

