#ifndef JuegoPM_H
#define JuegoPM_H

#include "Matriz.h"

//Constantes
const short int NUM_MODOS = 2;

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
  short int numMaxAcciones;
  short int numAccionActuales;
  short int modo;
}tJuegoPM;


typedef string tModo[NUM_MODOS];
 //Cabeceras de las funciones

 /**
  * función principal del juego.
  */
void mainJuegoPM();

/**
 *  Menu 
 */
int menu();

/**
 * 
 * Muestra las opciones del menú
 * seleccionar el tipo de juego(1 o 2) o salir(0)
 */
void mostrarMenu();

/**
 *  inicia los par�metros del juego que correspondan y llama a la funci�n cargar definida a continuaci�n.
 */							
bool iniciar(tJuegoPM & jpm, string modo, int num);

/**
 * abre el fichero que corresponda y llama a la funci�n cargar del m�dulo Matriz.
 */
bool cargar(tJuegoPM& jpm); 

/**
 *  muestra el estado del reto utilizando las facilidades del m�dulo utilidadesSYS.
 * Debe mostrar primero la imagen que se est� modificando y a continuaci�n la imagen objetivo.
 * Debe mostrar tambi�n el n�mero de intentos que quedan.
 */
void mostrar(tJuegoPM const& jpm);

/**
 *  permite realizar las acciones necesarias para jugar y controla si se ha llegado al l�mite de acciones permitidas;
 */
bool jugar(tJuegoPM& jpm);

/**
 * seg�n el comando de acci�n tecleado por el usuario, llama a la acci�n correspondiente definida en el m�dulo Matriz;
 */
bool accion(tJuegoPM& jpm);  

#endif
