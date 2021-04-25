#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;
#include <string>
#include "Matriz.h"


/*
En este módulo se definen los tipos y funciones necesarios para manejar la información 
correspondiente a un puzzle y resolverlo.

Declara un tipo estructurado tPuzzle con el nombre del puzzle y el nombre del fichero 
en que se encuentra, el tipo de puzzle, el número de movimientos máximo y las matrices 
inicial y final. Este tipo sustituye al tipo tJuegoPM del módulo JuegoPM de la práctica 
anterior. 
*/

typedef struct{
    string nombre_puzzle;
    string nombre_fichero;
    string tipo;
    int movimientos_maximos;
    tMatrizChar imagenInicial;
    tMatrizChar imagenObjetivo;
}tPuzzle;


/*
Declara en este módulo las siguientes funciones que se encontraban en el módulo 
JuegoPM y elimínalas de aquel. No es necesario modificar la implementación realizada 
de estas funciones en la primera parte aunque modificaremos el nombre de la función 

mainJuegoPM ya que ahora no se encuentra en ese módulo. Sobrecarga los operadores 
relacionales que necesites sobre el tipo Puzzle para realizar las operaciones de inserción 
ordenada y búsqueda del módulo ListaPuzzles


*/



 /**
  * función que resuelve un puzzle. Corresponde a la antigua
  * función mainJuegoPM. Dependiendo de la implementación realizada por el alumno en 
  * la primera parte puede necesitar algún pequeño ajuste en el código.
  */
void mainPuzzle();

/**
 * abre el fichero que corresponda y llama a la funci�n cargar del m�dulo Matriz.
 */
bool cargar(tPuzzle & jpm, string tipo); 


/**
 *  muestra el estado del reto utilizando las facilidades del m�dulo utilidadesSYS.
 * Debe mostrar primero la imagen que se est� modificando y a continuaci�n la imagen objetivo.
 * Debe mostrar tambi�n el n�mero de intentos que quedan.
 */
void mostrar(const tPuzzle & jpm);


/**
 *  permite realizar las acciones necesarias para jugar y controla si se ha llegado al l�mite 
 * de acciones permitidas;
 */
bool jugar(tPuzzle & jpm);


/**
 * seg�n el comando de acci�n tecleado por el usuario, llama a la acci�n correspondiente 
 * definida en el m�dulo Matriz;
 */
bool accion(tPuzzle & jpm);  




/*
bool accion2D(tJuegoPM& jpm);

bool accion1D(tJuegoPM& jpm);

void infoAccion1D();

void infoAccion2D();
*/


#endif