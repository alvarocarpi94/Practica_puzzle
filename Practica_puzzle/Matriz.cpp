#include <iostream>
#include <cmath>
#include <iomanip>
#include "Matriz.h"
#include "Coordenada.h"
#include "UtilidadesSYS.h"

using namespace std;

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
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2){
   
    bool swap = false;
    char auxiliar;
    //limites del rango de la matriz es decir que las coordenadas sean válidas.
    if((pos1.coorX >= 0 && pos1.coorX < mat.filas) && (pos1.coorY >= 0 && pos1.coorY < mat.columnas) && 
        (pos2.coorX >= 0 && pos2.coorX < mat.filas) && (pos2.coorY >= 0 && pos2.coorY < mat.columnas)){
            
        auxiliar = mat.matriz[pos1.coorX][pos1.coorY];
        mat.matriz[pos1.coorX][pos1.coorY] = mat.matriz[pos2.coorX][pos2.coorY];
        mat.matriz[pos2.coorX][pos2.coorY] = auxiliar;

        swap = true;
        
    }

    return swap;
}


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

    //Comprobar las dimensiones de la matriz con las filas a intercambiar
   
    if ((f1 >= 0 && f1 < mat.filas) && (f2 >= 0 && f2 < mat.filas)) {

        for (int i = 0; i < mat.columnas; i++) {
            swap(mat,{f1,i},{f2,i});
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

    //Comprobar las dimensiones de la matriz con las columnas a intercambiar

    if ((c1 >= 0 && c1 < mat.columnas) && (c2 >= 0 && c2 < mat.columnas)) {

        for (int i = 0; i < mat.filas; i++) {
            swap(mat, {i,c1}, {i,c2});
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
    int auxDiagonal = d;
    int contador = 0;

    if((mat.filas == mat.columnas) && (d >= 0 && d < mat.columnas)){

        
        for(int filas = 0; filas < mat.filas; filas++){

            for(int columnas = 0; columnas < mat.columnas; columnas++){

                if((filas == auxDiagonal) && (contador < (mat.columnas - d))){
                    swap(mat, {filas,contador}, {contador,filas});
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

    if((f >= 0) && (f < mat.filas)){

        for(int i = 0; i < mat.columnas/2; i++){
                swap(mat, {f,i}, {f, (mat.columnas -1) - i});
        }

        voltearF = true;

    }
    
    return voltearF;
}


/*
 */
bool voltearC(tMatrizChar& mat, int c) {
    
    
    bool voltearC = false;

    if((c >= 0) && (c < mat.columnas)){

        for(int i = 0; i < mat.filas/2; i++){
                swap(mat,{i,c},{(mat.filas -1) - i ,c});
        }

        voltearC = true;

    }
   
    
    return voltearC;
}

/*
 */
bool voltearD(tMatrizChar& mat, int d) {

    bool voltearD = false;

    // comprobamos que sea cuadra y que la dional este en el rango.
    if((mat.filas == mat.columnas) && (abs(d) >= 0 && abs(d) < mat.columnas)){

        if(d >= 0){

            for(int i = 0; i < (mat.filas - d)/2; i++){
                swap(mat, {i,d + i}, {(mat.filas -1) - i - d,(mat.columnas - 1) - i});
            }
        }else{
             for(int i = 0; i < (mat.filas - abs(d))/2; i++){
                swap(mat, { abs(d),i }, { (mat.filas - 1) - i, (mat.columnas - 1) - i - abs(d) });    
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
    Se define un array local con los contenidos 
    {-1,-1},{-1,0}, ...{1,1};
    Entonces tu bucle puede simplemente recorres las ocho posiciones del array sumando 
    esos valores a las coordenadas horizontal y vertical.

    Así en un único bucle de 8 vueltas podrás recorrer todos los vectores

    otra posibilidad es simplemente hacerte un bucle anidado que recorra en el bucle externo
    los valores -1 0 y 1 para los desplazamientos horizontales y en el bucle interno los mismo para
    los verticales.

    El bucle externo daría 3 vueltas y por cada vuelta del bucle externo el bucle interno
    daría 3 vueltas.

    cuando hablamos de un array, te digo que podría estar dentro de la función Ej:
    const tCoord vecinas[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

    Dice las dos soluciones son igual de eficientes.

    Para cada posicion de esas 8 puedes invocar a tu propia función de swap para matrices.

    Como hemos dicho antes, dicha función se ocupará ella solita de comprobar si las posiciones 
    a intercambiar están dentro de rango o no.

    Cuando la invoques estando las coordenas fuera de rango, simplemente no intercambiará nada.

    Por tanto, si invocas a swap, será la propia la qeu se  encargará del problema de que las coordenadas
    podrían salirse del tablero.

    Simplemente no haciendo nada en esos casos ( es decir que devuelvas false desde la funcion swap)
 */
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {

    bool swapAdy = false;
    const tCoor vecinas[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

    //Comprobamos el rango de las coordenadas que nos dan.
      if((pos1.coorX >= 0 && pos1.coorX < mat.filas) && (pos1.coorY >= 0 && pos1.coorY < mat.columnas) && 
        (pos2.coorX >= 0 && pos2.coorX < mat.filas) && (pos2.coorY >= 0 && pos2.coorY < mat.columnas)){

         
        for(int i = 0; i < 8; i++){
            swap(mat, {pos1.coorX + (vecinas[i].coorX),pos1.coorY + (vecinas[i].coorY) }, 
                {pos2.coorX + (vecinas[i].coorX),pos2.coorY + (vecinas[i].coorY) });
        }
        
        swapAdy = true;
    }


   return swapAdy;
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


