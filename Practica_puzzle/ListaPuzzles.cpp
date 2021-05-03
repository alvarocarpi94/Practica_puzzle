/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#include "ListaPuzzles.h"
#include <fstream>
#include <iostream>
using namespace std;


/*
 * Debemos poner las direcciones de memoria a null 
 * e inicializar los contadores
 */
void inicializar(tPuzzlesReunidos& jr){

	for(int i = 0 ; i < MODO_JUEGO; i++){
		jr[i].contador = 0;
	}

	for(int i = 0; i < MODO_JUEGO; i++){
		for(int j = 0; j < MAX_PUZZLES; j++){
			jr[i].listaPuzzle[j] = NULL;
		}
	}

}

/*
 * Partimos de la idea de que dos puzzle en una lista de dos.
 * 
 * Es decir por una lado cargamos los ficheros de los puzzles 1D y otro los de 2D
 * en el mismo fichero.
 * 
 * Estructura del fichero de inicio
 * 
 * 7			-> indica cuandos ficheros leemos tanto el nombre como el fichero de donde esta alojado
 * Torre
 * torre1_1D.txt
 * ...
 * 5
 * Rotar a la derecha
 * patitoRD_2D.txt
 * 
 */
bool cargar(tPuzzlesReunidos& jr){

	ifstream fichero;
	bool exitoCargar = true;

	fichero.open(NAME_FILE);

	if(!fichero.is_open()){

		exitoCargar = false;
	}else{

		//primero 1D y luego 2D
		for(int i = 0 ; i < MODO_JUEGO; i++)
		{
			fichero >> jr[i].contador;
			fichero.ignore();

			for(int j = 0; j < jr[i].contador; j++)
			{
				jr[i].listaPuzzle[j] = new tPuzzle;
				getline(fichero, jr[i].listaPuzzle[j]->nombre_puzzle);
				fichero >> jr[i].listaPuzzle[j]->nombre_fichero;
				jr[i].listaPuzzle[j]->tipo = tModoJuego[i];

				if(!cargar(*jr[i].listaPuzzle[j], jr[i].listaPuzzle[j]->tipo)){
					exitoCargar = false;
				}
				fichero.ignore();
			}
		}
	
		fichero.close();
	}


	return exitoCargar;
}


/*
 * Estructura del fichero a Guardar (copia y pega de cargar)
 * 
 * 7			-> indica cuandos ficheros leemos tanto el nombre como el fichero de donde esta alojado
 * Torre
 * torre1_1D.txt
 * ...
 * 5
 * Rotar a la derecha
 * patitoRD_2D.txt
 * 
 */
void guardar(const tPuzzlesReunidos& listas){

	ofstream fichero;

	fichero.open(NAME_FILE1);

	if (fichero.is_open()) 
	{

		//primero 1D y luego 2D
		for (int i = 0; i < MODO_JUEGO; i++)
		{
			fichero << listas[i].contador;
			fichero << endl;

			for (int j = 0; j < listas[i].contador; j++)
			{
				fichero << listas[i].listaPuzzle[j]->nombre_puzzle;
				fichero << endl;
				fichero << listas[i].listaPuzzle[j]->nombre_fichero;
				fichero << endl;
			}
		}

		fichero.close();
	}

}

/*
 *Partimos de que nos dan la lista a mostrar por lo tanto tenemos un contador
 * donde poder fijar nuestro recorrido.
 * 
 * Nos fijaremos en las paginas 1 y 2 en concreto en las tablas 1 y 2 para
 * rellenar los literales del for.
 */
int elegirPuzzle(tListaPuzzles& lp){

	int opcion;

	cout << "\nEn esta versión están disponibles los siguientes retos\n";
	
	//mostramos la lista 
	mostrarListaInfo(lp);

	cout << "\n0 Salir\n";
	cout << "-1 Mostrar la lista ordenada de mayor a menor\n";
	cout << "-2 Mostrar la lista ordenada de menor a mayor\n\n";

	cout << "Elige un reto:";
	cin >> opcion;

	while(opcion < -2 || opcion > lp.contador -1){
		cout << "\n\nERROR al eligir un reto\n";
		cout << "Elige un reto\n";
		cin >> opcion;
	}

	return opcion;
}



void mostrarListaInfo(const tListaPuzzles& lp)
{
	for (int i = 0; i < lp.contador; i++)
	{
		//OJO HAY QUE COMPROBAR ESTO
		cout << i + 1 << " ";
		mostrarInfo(*lp.listaPuzzle[i]);
	}
}


/*
 * Debemos tener el cuenta el algoritmo a utilizar en este caso
 * la ordenación por insercción es el mas idoneo, por que es estable siempre
 * que utilizemos  < 0 > .
 * 
 * En concreto nos fijamos en el codigo de gestion de lista ordenadas del tema 7 pag 727
 * 
 * OJo cuando tenemos posiciones de memoria tenemos que comparar con los 
 * datos que hace referencia.
 * 
 * Es decir no sé si debemos hacer operaciones operator == y < en Puzzle.h
 */
bool insertarOrdenado(tListaPuzzles& lp, tPuzzle* p){

	//Varibles
	bool insertado = true;
	

	if(lp.contador == MAX_PUZZLES){
		insertado = false;
	}else
	{
		int pos = 0;
		while((pos < lp.contador) && (*lp.listaPuzzle[pos] < *p)){
			pos++;
		}
		//Insetamos en la posicion pos (primer mayor o igual)
		for(int j = lp.contador; j > pos; j--){
			//Desplazamos una posicion a la derecha
			lp.listaPuzzle[j] = lp.listaPuzzle[j - 1];
		}
		//añadimos el nuevo puzzle a la lista.
		lp.listaPuzzle[pos] = p;
		lp.contador++;
	}

	return insertado;
}

//Se implementarán al menos las siguientes funciones no pertenecientes a la interfaz: 

/*
 * Suponemos que la lista esta ordenada de forma creciente o decreciente
 * 
 * Para ello el mejor método de busqueda que hemos aprendido es la busqueda binaria.
 * 
 * inicialmente pos lo vamos inicializar como -1
 */
bool buscar(const tListaPuzzles& lista, tPuzzle* puzzle, int& pos){

	//VARIABLES 
	int ini = 0, fin = lista.contador - 1, mitad;
	pos = -1;
	bool posEncontrada = false;

	/*
	 * Vamos a recorrer la lista como máxim0 con un coste logaritmico, es decir
	 * la mitad de la misma. Mierda no se como va el algoritmo copio el tema 7 pagina 739.
	 * 
	 * OJo cuando tenemos posiciones de memoria tenemos que comparar con los 
	 * datos que hace referencia.
	 * 
	 * Es decir no sé si debemos hacer operaciones operator == y < en Puzzle.h
	 */

	while ((ini <= fin) && !posEncontrada)
	{
		mitad = (ini + fin) / 2; //Division entera
		if (*puzzle == *lista.listaPuzzle[mitad])
		{
			posEncontrada = true;
		}
		else if (*puzzle < *lista.listaPuzzle[mitad])
		{
			fin = mitad - 1;
		}
		else
		{
			ini = mitad + 1;
		}

	}

	if(posEncontrada){
		pos = mitad;
	}

	return posEncontrada;
}


//ASUMIMOS que para ordenar las lista debemos implementar dos métodos una que la ordene
// de forma creciente y otra decreciente por número de movimientos


/*
 * 
 * La ordenacion de va ser de tipo O(n^2) ya que debemos recorrer
 * en el peor caso toda la lista.
 * 
 * claramente debemos usar un algoritmo para esta hermosa tarea
 * ¿Cual elegir hay el kit de la question!? pero revisando el amado tema 7
 * vemos algo muy interesante el método de la burbuja de la pagina 721 
 * 
 * de esta menera tenemos un comportamiento natural, estable ya que mantiene
 * el orden relativo y no hace iteraciones de más.
 */
void ordenarListaMayorAMenor(tListaPuzzles & lista){

	//variables
	//inter de intercambio.
	bool inter = true;
	int i = 0;

	//Desde el 1º hasta el penúltimo si hay intercambios...
	while((i < lista.contador - 1) && inter)
	{
		inter = false;
		for(int j = lista.contador - 1; j > i; j--)
		{
			if(*lista.listaPuzzle[j] > *lista.listaPuzzle[j -1])
			{
				tPuzzle * tmp;
				tmp = lista.listaPuzzle[j];
				lista.listaPuzzle[j - 1] = tmp;
				inter = true;
			}
		}
		if(inter)
		{
			i++;
		}
	}

}

/*
 * Copia y pega de la de ordenarListaMayorAMenor, cambiando ">" por "<"
 */
void ordenarListaMenorAMayor(tListaPuzzles& lista) {

	//variables
	//inter de intercambio.
	bool inter = true;
	int i = 0;

	//Desde el 1º hasta el penúltimo si hay intercambios...
	while ((i < lista.contador - 1) && inter)
	{
		inter = false;
		for (int j = lista.contador - 1; j > i; j--)
		{
			if (*lista.listaPuzzle[j] < *lista.listaPuzzle[j - 1])
			{
				tPuzzle* tmp;
				tmp = lista.listaPuzzle[j];
				lista.listaPuzzle[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter)
		{
			i++;
		}
	}

}

