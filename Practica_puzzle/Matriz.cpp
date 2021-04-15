#include <iostream>
#include <cmath>
#include <iomanip>
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
    cout << "   ";
    for(int i = 0; i < mat.columnas; i++){
        if(i < 10){
            cout << i  << " ";
        }else{
            cout << i;
        }
    }

    cout << endl;

    for(int fila = 0; fila < mat.filas; fila++){
        cout << setw(2) << right << fila << " ";
        for (int columna = 0; columna < mat.columnas; columna++) {
                colorCTA(15, int(mat.matriz[fila][columna]) - int('0'));
                cout << ' ' << ' ';
        }
        colorCTA(15, 0);
        cout << endl;
    }

    colorCTA(15, 0);
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
                    matricesIguales = false;
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
   
    if ((f1 >= 0 && f1 < mat.filas) && (f2 >= 0 && f2 < mat.filas)) {

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

    if ((c1 >= 0 && c1 < mat.columnas) && (c2 >= 0 && c2 < mat.columnas)) {

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
  Def: una matriz es cuadrada cuando tiene mismo numero de filas que de columnas

 */
bool swapD(tMatrizChar& mat, int d) {
    bool swapD = false;
    char auxiliar;
    int auxDiagonal = d;
    int contador = 0;

    if((mat.filas == mat.columnas) && (d >= 0 && d < mat.columnas)){

        
        for(int filas = 0; filas < mat.filas; filas++){

            for(int columnas = 0; columnas < mat.columnas; columnas++){

                if((filas == auxDiagonal) && (contador < (mat.columnas - d))){
                    auxiliar = mat.matriz[filas][contador];
                    mat.matriz[filas][contador] = mat.matriz[contador][filas];
                    mat.matriz[contador][filas] = auxiliar;
                    auxDiagonal++;
                    contador++;
                }

            }
        }

        swapD = true;

    }

    return swapD;
}

/*
     * dar la vuelta a la fila f con respecto al eje vertical central de la imagen.
 * Devuelve falso si la fila no pertenece al rango de la matriz.
 */
bool voltearF(tMatrizChar& mat, int f) {
    
    bool voltearF = false;
    char auxiliar;

    if((f >= 0) && (f < mat.filas)){

        /*
        * 
        * for(int filas = 0; filas < mat.filas; filas++){

            for(int columnas = 0; columnas < mat.columnas; columnas++){
                
                if((filas == f) && (contador < (mat.columnas/2))){
                    auxiliar = mat.matriz[filas][contador];
                    mat.matriz[filas][contador] = mat.matriz[filas][auxColumnas];
                    mat.matriz[filas][auxColumnas] = auxiliar;
                    auxColumnas--;
                    contador++;
                }
            }
        }
        
        */

        for(int i = 0; i < mat.columnas/2; i++){
                auxiliar = mat.matriz[f][i];
                mat.matriz[f][i] = mat.matriz[f][(mat.columnas -1) - i];
                mat.matriz[f][(mat.columnas -1) - i] = auxiliar;
        }

        voltearF = true;

    }
    
    return voltearF;
}


/*
 */
bool voltearC(tMatrizChar& mat, int c) {
    
    
    bool voltearC = false;
    char auxiliar;

    if((c >= 0) && (c < mat.columnas)){

        for(int i = 0; i < mat.filas/2; i++){
                /*
                    01 = x

                */
                auxiliar = mat.matriz[i][c];
                mat.matriz[i][c] = mat.matriz[(mat.filas -1) - i][c];
                mat.matriz[(mat.filas - 1) - i][c] = auxiliar;
        }

        voltearC = true;

    }
   
    
    return voltearC;
}

/*
 */
bool voltearD(tMatrizChar& mat, int d) {

    bool voltearD = false;

    char auxiliar;

    // comprobamos que sea cuadra y que la dional este en el rango.
    if((mat.filas == mat.columnas) && (abs(d) >= 0 && abs(d) < mat.columnas)){

        if(d >= 0){

            for(int i = 0; i < (mat.filas - d)/2; i++){
                // mat[0][1]
                auxiliar = mat.matriz[i][d + i];
                // mat[0][1] = [2][3]
                mat.matriz[i][d + i] = mat.matriz[(mat.filas -1) - i - d][(mat.columnas - 1) - i];
                mat.matriz[(mat.filas - 1) - i - d][(mat.columnas - 1) - i] = auxiliar;
            }
        }else{
             for(int i = 0; i < (mat.filas - abs(d))/2; i++){
                // mat[1][0]
                auxiliar = mat.matriz[abs(d)][i];
                // mat[1][0] = [3][2]
                mat.matriz[abs(d)][i] = mat.matriz[(mat.filas - 1) - i][(mat.columnas - 1) - i - abs(d)];
                mat.matriz[(mat.filas - 1) - i][(mat.columnas - 1) - i - abs(d)] = auxiliar;
            }

        }

        voltearD = true;

   }

    return voltearD;
}


//Funciones de 2D.

/*
 */
void voltearV(tMatrizChar& mat) {
    for(int i = 0 ;  i < mat.columnas ; i++){
        voltearF(mat, i);
    }
}

/*
 */
void voltearH(tMatrizChar& mat) {
    for(int i = 0; i < mat.columnas ; i++){
        voltearC(mat, i);
    }
}

/*
 */
void rotarD(tMatrizChar& mat){

    tMatrizChar auxiliar = mat;
    mat.filas = auxiliar.columnas;
    mat.columnas = auxiliar.filas;


    for(int filas = 0; filas < auxiliar.filas; filas++){
        for(int columnas = 0; columnas < auxiliar.columnas; columnas++){ 

            // [1][7]                                             //[4][1]      
            mat.matriz[columnas][(auxiliar.filas - 1) - filas] = auxiliar.matriz[filas][columnas];
        }
    }
}

/*
 */
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    return false;
}


/*
 */
bool VoltearID(tMatrizChar& mat){
    bool voltearID = false;
    //matriz cuadrada
    if(mat.columnas == mat.filas){
        tMatrizChar auxiliar = mat;
        for(int filas = 0; filas < mat.filas; filas++){
            for(int columnas = 0; columnas < mat.columnas; columnas++){ 

                //[0][0]  -> [0][0]
                //[0][1]  _> [1][0]                          
                mat.matriz[filas][columnas] = auxiliar.matriz[columnas][filas];
            }
        }   
        voltearID = true;
    }

    return voltearID;
}


