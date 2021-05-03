/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#ifndef JuegoPM_H
#define JuegoPM_H

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

/*
    MODIFICACIONES DE LA VERSION II
*/


/**
 * que carga los 
 * datos de entrada, muestra el menú y gestiona las opciones seleccionadas por 
 * el usuario. Cuando el usuario pide salir del programa guarda en el fichero el 
 * catálogo de puzzles y libera la memoria dinámica que se haya utilizado.
 */
void mainPuzzlesReunidos();


/**
 *  Menu.
 */
int menu();

/**
 * 
 * Muestra las opciones del menú.
 */
void mostrarMenu();

/**
 * Muestra un rótulo del juego.
 */
void presentacionJuego();

#endif
