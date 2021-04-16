#ifndef COORDENADA_H
#define COORDENADA_H

using namespace std;

/*
    Estructura que define una coordenada
    las coordenadas no van a ser negativas
    por tanto podemos definarlas como 
    unsigned short int

    problemas las conversiones de operator + nos dificulta
    los tipos.El unico que nos deja es unsigned.
*/

typedef struct 
{
    int coorX;
    int coorY; 

}tCoor;

/**
 * Compara si dos coordenadas son iguales
 * 
 * @return 
 */
bool operator == (tCoor c1, tCoor c2);

/**
 * compara si dos coordenadas son distintas.
 */
bool operator != (tCoor c1, tCoor c2);

/**
 * devuelve la coordenada resultante de sumar las dos coordenadas dadas por par�metros.
 */
tCoor operator + (tCoor c1, tCoor c2);


#endif
