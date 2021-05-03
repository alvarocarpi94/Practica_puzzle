
/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

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

const string RUTA_DIR = "ficheros_retos/";

const int TIPOS_JUEGO = 2;


//problema al declarar typedef con typedef
/*
 * Gravedad	Código	Descripción	Proyecto	Archivo	Línea	Estado suprimido
Error	C5208	la clase sin nombre que se usa en el nombre typedef no puede declarar miembros que no sean miembros de datos no estáticos, enumeraciones de miembros o clases de miembros	Practica_puzzle	C:\Users\ssqnsn\Documents\WORKSPACE\GIT\C-C++\Practica_puzzle\Practica_puzzle\Puzzle.h	30	

 */
struct tPuzzle {
    string nombre_puzzle;
    string nombre_fichero;
    //salta error al compilar
    /*
     * Gravedad	Código	Descripción	Proyecto	Archivo	Línea	Estado suprimido
Advertencia	C26495	La variable "tPuzzle::numAccionActuales" no está inicializada. Siempre debe inicializarse una variable miembro (type.6).	Practica_puzzle	C:\Users\ssqnsn\Documents\WORKSPACE\GIT\C-C++\Practica_puzzle\Practica_puzzle\Puzzle.h	38	
    Gravedad	Código	Descripción	Proyecto	Archivo	Línea	Estado suprimido
Advertencia	C26495	La variable "tPuzzle::numMaxAcciones" no está inicializada. Siempre debe inicializarse una variable miembro (type.6).	Practica_puzzle	C:\Users\ssqnsn\Documents\WORKSPACE\GIT\C-C++\Practica_puzzle\Practica_puzzle\Puzzle.h	38	

     */
    string tipo;
    int numMaxAcciones;
    int numAccionActuales;
    tMatrizChar imagenInicial;
    tMatrizChar imagenObjetivo;
};


typedef tPuzzle* tPunteroPuzzle;


/*
 * Comprobamos que estoy funciona (un proyecto aparte y un header.h y sourcer.cpp) 
 * al ser llamado desde un .cpp
 * cout << tModoJuego[0] << tModoJuego[1];
 */
const string tModoJuego[TIPOS_JUEGO] = { "1D", "2D" };

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
void mainPuzzle(tPuzzle & p);

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
 * Muestra informacion del puzzle
 * 1) numero movimientos
 * 2) el nombre del puzzle
 */
void mostrarInfo(const tPuzzle & jpm);

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
 * Despues de hacer la LISTAPUZZLE.cpp nos dimos cuenta que habia que 
 * implementar las operacion operator para manipular puzzle
 * Entre ellas necesitamos ==, <, >;

/**
 * Comprobamos si dos puzzle son iguales.
 */
bool operator == (const tPuzzle& puzzle1, const tPuzzle& puzzle2);

/**
 * Comprobamos si el puzzle 1 es menor que el puzzle 2
 */
bool operator < (const tPuzzle& puzzle1, const tPuzzle& puzzle2);

/**
 * Comprobamos si el puzzle 1 es mayor que el puzzle 2
 */
bool operator > (const tPuzzle& puzzle1, const tPuzzle& puzzle2);

/*
bool accion2D(tJuegoPM& jpm);

bool accion1D(tJuegoPM& jpm);

void infoAccion1D();

void infoAccion2D();
*/


#endif