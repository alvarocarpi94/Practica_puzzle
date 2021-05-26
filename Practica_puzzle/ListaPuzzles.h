/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/


#ifndef LISTA_PUZZLES_H
#define LISTA_PUZZLES_H
#include "Puzzle.h"
using namespace std;


/*
Define una constante MAX_PUZZLES de valor 100, que representa el número máximo de 
puzzles
*/

const int MAX_PUZZLES = 100;

const short int MODO_JUEGO = 2;

const string NAME_FILE = "ficheros_retos/datosPuzzles.txt";
const string NAME_FILE1 = "ficheros_retos/datosPuzzlesBackup.txt";

/*
 * que contiene un array estático de punteros a 
 * variables dinámicas de tipo tPuzzle.
 * 
 * El tamaño máximo del array es el número máximo 
 *  de puzzles. Esta lista se mantiene siempre ordenada en orden creciente del número de 
 *  intentos máximo para realizar el puzzle.
 * 
 * Si el usuario pide verla en orden inverso, 
 * opción -1 o -2, según corresponda, los punteros que contiene el array se modifican 
 * convenientemente, pero nunca se deben intercambiar o sobreescribir los datos de tipo 
 * tPuzzle, pues perderíamos eficiencia.
 * 
 * Declara también un array, tPuzzlesReunidos, de 2 posiciones, cada una de ellas de 
 * tipo tListaPuzzles. La primera lista representa el catálogo de puzzles de tipo 1D y la 
 * segunda lista el catálogo de puzzles de tipo 2D. 
*/

typedef tPunteroPuzzle tArrayPuzzle[MAX_PUZZLES];



typedef struct {

    tArrayPuzzle listaPuzzle;
    short int contador;

}tListaPuzzles;




/*
 * Declara  también  un  array, tPuzzlesReunidos,  de  2  posiciones,  cada  una  de  ellas  
 * de tipo tListaPuzzles. La primera lista representa el catálogo de puzzles de tipo 1D y la 
 * segunda lista el catálogo de puzzles de tipo 2D.
*/

typedef tListaPuzzles tPuzzlesReunidos[MODO_JUEGO];


/**
 *  inicializa las dos listas de puzzles.
 */
void inicializar(tPuzzlesReunidos & jr);

/**
 *  carga los datos contenidos en el fichero 
 * datosPuzzles.txt. Los datos se encuentran ordenados en el fichero en el mismo 
 * orden en que deben estar en la lista, en orden creciente del número de intentos 
 * máximo para realizar el puzzle y a igualdad de intentos por orden alfabético del 
 * nombre del puzzle. 
 * 
 * N1D  // Número de puzzles del tipo 1D
   N1   // Nombre del puzzle 1 de tipo 1D
   F1   // Fichero que contiene el puzzle 1
    …   // 2 N1D - 2 filas con los nombres y ficheros de los puzzles 1D
  N2D   // Número de puzzles del tipo 2D
  N2    // Nombre del puzzle 1 de tipo 2D
  F2    // Fichero que contiene el puzzle 1
    …   // 2 N2D - 2 filas con los nombres y ficheros de los puzzles 2D
 */


bool cargar(tPuzzlesReunidos & jr);


/**
 * guarda en el fichero 
    datosPuzzles.txt la lista de puzzles 1D y 2D con el mismo formato del fichero 
    de entrada, y ordenados según están en las listas.

 */
void guardar(const tPuzzlesReunidos & listas);

/**
 *  muestra la lista de puzzles y permite al usuario 
 * legir uno de ellos. Debe dar la opción de mostrar la lista de mayor a menor 
 * número de movimientos o a la inversa.
 */
int elegirPuzzle(tListaPuzzles & lp);

/**
 * Inserta ordenado en la 
 * lista de puzzles un nuevo puzzle.
 */
bool insertarOrdenado(tListaPuzzles & lp, const tPuzzle & p);

//Se implementarán al menos las siguientes funciones no pertenecientes a la interfaz: 

/**
 *  busca en una lista ordenada de puzzles un puzzle.
 */
bool buscar(const tListaPuzzles & lista, tPuzzle* puzzle, int & pos);


/**
 * Ordenamos la lista de forma decreciente por numero de movimientos.
 */
void ordenarListaMayorAMenor(tListaPuzzles & lista);


/**
 * Ordenamos la lista de forma creciente por numero de movimientos.
 */
void ordenarListaMenorAMayor(tListaPuzzles& lista);


    //CABECERAS EXTRAS

void mostrarListaInfo(const tListaPuzzles& lp);

void mostrarListaNombre(const tListaPuzzles& lp);

void eliminarMemoriaLista(tListaPuzzles & lp);

#endif
