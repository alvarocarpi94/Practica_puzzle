#include <iostream>
#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"

using namespace std;

//hola2


/*
    Entender nuestra estructura

    typedef struct{
    //Tamaño máximo de nuestra matriz
    unsigned char matriz[DIM_MAX][DIM_MAX];
    //tamaño de nuestra matriz
    unsigned int filas = 0;
    unsigned int columnas = 0;
    }tMatrizChar;

    Por otro lado entendemos los ficheros
    que debemos cargar:

    7 7
    1 1 1 1 1 1 1
    2 2 2 2 2 2 2
    3 3 3 3 3 3 3
    4 4 4 4 4 4 4
    5 5 5 5 5 5 5
    6 6 6 6 6 6 6
    7 7 7 7 7 7 7

    -------

    Cada imagen tiene una resolución que establece el número 
    de filas y de columnas de la matriz, ambas entre 0 y DIM_MAX.
 */
bool cargar(tMatrizChar& mat, istream& ent) {
    
    //variables locales
    bool cargarExitosa = true;
    short int filas, columnas;
    char cargarCaracter;
    
    //Cargamos tamaño de la matriz
    //primero fila y luego columnas.
    ent >> filas;
    ent >> columnas;

    //Debemos comprobar los limites
    if(( filas < 0  || columnas < 0 || filas > DIM_MAX || columnas > DIM_MAX)){
        cargarExitosa = false;
    }else{

        mat.filas = filas;
        mat.columnas = columnas;

        for(int f = 0; f < filas; f++){
            for(int c = 0; c < columnas; c++){

                ent >> mat.matriz[f][c];
            }
        }
    }

    return cargarExitosa;
}

/*
* 
Debemos colorear el fondo, para ello podemos 
utilizar la siguiente llamada: colorCTA(15, int(matriz[f][c]) - int('0'));
donde matriz[f][c] contiene la figura a mostrar.  

Es importante acordarse de que el tipo uint8 es de tipo char.
Escribimos espacios en blanco ' ' (uno o varios).

*/
void mostrar(const tMatrizChar& mat){

    cout << "\n\n";

    for(int fila = 0; fila < mat.filas; fila++){
        
        for (int columna = 0; columna < mat.columnas; columna++) {
                colorCTA(15, int(mat.matriz[fila][columna]) - int('0'));
                cout << ' ' << ' ';
        }
    }

    cout << "\n\n";

}

/*  
 * Se quiere comprar una mat1 con otroa mat2 
 * Para ello debemos comprobar sus dimensiones y las casillas ij de
 * cada una de ellas es decir mat1[ij] == mat2[ij]
 */
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2){

    bool matricesIguales = true;

    //Comprobación de las dimensiones de las matrices
    if((mat1.filas == mat2.filas) && (mat1.columnas == mat2.columnas)){
        //Debemos comparar cada una de las posiciones ij de la matriz de mat1 y mat2
        //si unas de las posiciones ij no son iguales, pararemos de buscar
        int contadorFilas = 0;
        int contadorColumnas;

        while(contadorFilas < mat1.filas && matricesIguales){
            contadorColumnas = 0;
            while(contadorColumnas < mat2.columnas && matricesIguales){

                //si son iguales las posiciones mat1 ij y mat2 ij seguimos recorriendo la matriz sino nos salimos.
                if(mat1.matriz[contadorFilas][contadorColumnas] == mat2.matriz[contadorFilas][contadorColumnas]){
                    contadorColumnas++;
                }else{

                }
            }

            contadorFilas++;

        }

    }else{
        matricesIguales = false;
    }

    return matricesIguales;
}

//Funciones de 1D.

/*
 */
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2);


/*
 * typedef struct{
    //Tamaño máximo de nuestra matriz
    unsigned char matriz[DIM_MAX][DIM_MAX];
    //tamaño de nuestra matriz
    unsigned int filas = 0;
    unsigned int columnas = 0;
    }tMatrizChar;
 */

/*
* 1 2 3 4 
* 5 6 7 8
* 9 10 11 12 
* 
* SF 1 3
* 
* 9 10 11 12 
* 5 6 7 8
* 1 2 3 4 
*/
bool swapF(tMatrizChar& mat, int f1, int f2){

    //variables
    bool swapf = false;
    char auxiliar;

    //Comprobar las dimensiones de la matriz con las filas a intercambiar
   
    if ((f1 >= 0 && f1 <= mat.filas) && (f2 >= 0 && f2 <= mat.filas)) {

        for (int i = 0; i < mat.columnas; i++) {
            auxiliar = mat.matriz[f1][i];
            mat.matriz[f1][i] = mat.matriz[f2][i];
            mat.matriz[f2][i] = auxiliar;
        }

        swapf = true;
    }
   
    return swapf;

}
    
/*
 */
bool swapC(tMatrizChar& mat, int c1, int c2) {

    //variables
    bool swapc = false;
    char auxiliar;

    //Comprobar las dimensiones de la matriz con las columnas a intercambiar

    if ((c1 >= 0 && c1 <= mat.columnas) && (c2 >= 0 && c2 <= mat.columnas)) {

        for (int i = 0; i < mat.filas; i++) {
            auxiliar = mat.matriz[i][c1];
            mat.matriz[i][c1] = mat.matriz[i][c2];
            mat.matriz[i][c2] = auxiliar;
        }

        swapc = true;
    }

    return swapc;

}

/*
 */
bool swapD(tMatrizChar& mat, int d) {
    return false;
}

/*
 */
bool voltearF(tMatrizChar& mat, int f) {
    return false;
}


/*
 */
bool voltearC(tMatrizChar& mat, int c) {
    return false;
}

/*
 */
bool voltearD(tMatrizChar& mat, int d) {
    return false;
}


//Funciones de 2D.

/*
 */
void voltearV(tMatrizChar& mat) {

}

/*
 */
void voltearH(tMatrizChar& mat) {

}

/*
 */
void rotarD(tMatrizChar& mat){

}

/*
 */
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    return false;
}


/*
 */
bool VoltearID(tMatrizChar& mat){
    return false;
}


