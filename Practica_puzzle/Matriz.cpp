#include <iostream>
#include "Matriz.h"
#include "Coordenada.h"

using namespace std;

//hola


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
bool cargar(tMatrizChar & mat, istream& ent){
    
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


/*
 */
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2);
/*
 */
bool swapF(tMatrizChar& mat, int f1, int f2);

/*
 */
bool swapC(tMatrizChar& mat, int c1, int c2);

/*
 */
bool swapD(tMatrizChar& mat, int d);

/*
 */
bool voltearF(tMatrizChar& mat, int f);


/*
 */
bool voltearC(tMatrizChar& mat, int c);

/*
 */
bool voltearD(tMatrizChar& mat, int d);


/*
 */
void voltearV(tMatrizChar& mat);

/*
 */
void voltearH(tMatrizChar& mat);

/*
 */
void rotarD(tMatrizChar& mat);

/*
 */
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);


/*
 */
bool VoltearID(tMatrizChar& mat);


