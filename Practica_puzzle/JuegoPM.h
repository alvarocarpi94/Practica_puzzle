/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#ifndef JuegoPM_H
#define JuegoPM_H

#include "Matriz.h"
#include <string>
//#include <iostream>
//#include <fstream> //Uso de ficheros


using namespace std;
/*
 * Estructura
 *
 * En el módulo JuegoPM se define el tipo tJuegoPM para 
 * estructurar los elementos del juego: las imágenes
 * (imagen del juegador y la que cargamos desde un fichero (como solucion)), 
 * el número máximo de acciones  y el modo.
 * 
 * OJO: tendríamos que tener un contador de los intentos actuales?
 */

typedef struct{
  tMatrizChar imagenInicial;
  tMatrizChar imagenObjetivo;
  int numMaxAcciones;
  int numAccionActuales;
  string modo;
}tJuegoPM;


 //Cabeceras de las funciones

/*
 * -Se mantiene la constante numOpc.
 * -Se modifica la función menu para que muestre el nuevo menú.
 * -Se implementa una nueva función mainPuzzlesReunidos() que carga los 
 * datos de entrada, muestra el menú y gestiona las opciones seleccionadas por 
 * el usuario. Cuando el usuario pide salir del programa guarda en el fichero el 
 * catálogo de puzzles y libera la memoria dinámica que se haya utilizado.
 * -El resto de tipos y funciones que había en este módulo en la práctica 1 se 
 * eliminan de él. 
*/


/**
 * que carga los 
 * datos de entrada, muestra el menú y gestiona las opciones seleccionadas por 
 * el usuario. Cuando el usuario pide salir del programa guarda en el fichero el 
 * catálogo de puzzles y libera la memoria dinámica que se haya utilizado.
 */
void mainPuzzlesReunidos();


/**
 *  Menu 
 */
int menu();

/**
 * 
 * Muestra las opciones del menú
 */
void mostrarMenu();

#endif
