#include "Coordenada.h"

using namespace std;

/* 
Estructura de la que debemos comparar

typedef struct 
{
    unsigned short int coorX;
    unsigned short int coorY;
}tCoor;
*/


/*
 * Desarollamos la funcionalidad de Coordenada.h 
 */


bool operator == (tCoor c1, tCoor c2){

    bool iguales = false;

    if(c1.coorX == c2.coorX)    
        if(c1.coorY == c2.coorY)
            iguales = true;

    return iguales;
}

/*
 */
bool operator != (tCoor c1, tCoor c2){

    bool iguales = true;

    if(c1.coorX != c2.coorX || c1.coorY != c2.coorY)    
            iguales = false;

    return iguales;
}

/*
    Devolvemos un tCoor por tanto
        coorX
        coorY
*/
tCoor operator + (tCoor c1, tCoor c2){

    return {c1.coorX + c2.coorX, c2.coorY + c2.coorY};
}
