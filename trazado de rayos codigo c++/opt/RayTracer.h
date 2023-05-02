#include <vector>
#include <cstdlib>
#include "escena.h"

using namespace std;

class rayTracer {
    escena * Escena; 
    int muestras;   
    int maxdepth;
public:
    rayTracer(escena *,int, int);
    Color Trazarayo(rayo, int);  
    objeto * intersecta(rayo); 

    Color renderiza(int,int); 
    Color EvalPhong(Point,Point,rayo,Material*,objeto *);
};

