
/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#include <iostream>
#include <fstream> //Uso de ficheros
#include <string>	//uso de strings
#include "JuegoPM.h"
#include "UtilidadesSYS.h"
#include "ListaPuzzles.h"
using namespace std;


void intentarJugar(tListaPuzzles& lp);
bool tryToAdd(tPuzzlesReunidos & puzzles);

/*
 * Al comenzar el juego aparece un men� para seleccionar entre las versiones del juego 
 * modo 1D, modo 2D y la opci�n de salir. A continuaci�n, se pide el nombre de 
 * fichero que contiene las im�genes inicial y objetivo. Adem�s, el �ltimo elemento de 
 * este fichero es el n�mero de acciones o intentos que se tienen para conseguir que la 
 * imagen inicial sea la imagen objetivo.
 */



/*
	MODIFICACIONES DE LA VERSION II
*/

/*
En  este  módulo  dejamos  las  funciones  que  se  encargan  de  la  gestión  del  catálogo  
de puzzles. 

●Se mantiene la constante numOpc.

●Se modifica la función menu para que muestre el nuevo menú.

●Se  implementa  una  nueva  función mainPuzzlesReunidos()que  carga  los 
datos de entrada, muestra el menú y gestiona las opciones seleccionadas por el usuario. 
Cuando el usuario pide salir del programa guarda en el fichero el catálogo de puzzles y 
libera la memoria dinámica que se haya utilizado.

●El  resto  de  tipos  y  funciones  que  había  en  este  módulo  en  la  práctica  1  
se eliminan de él.

IMPORTANTE:

	Pasos para la construccion del main:

	1) inicializamos nuestro array estatico a memoria dinámica
	2) cargamos el fichero datosPuzzles.txt al tPuzzlesReunidos.
	3) si todo sale bien mostramos menu y realizamos accion sino, mostrarmos un mensaje de error.

*/


int main(){

	mainPuzzlesReunidos();

	return 0;
}



void mainPuzzlesReunidos() {

	//chcp1252();
	//borrar(); //Borramos para que no nos salga el mensaje de chcp1252();
	//Estructura de nuestro juego
	// Establecer el idioma a español
	

	tPuzzlesReunidos puzzles;
	bool finJuego = false;
	short int numOpc;


	inicializar(puzzles);
	//cargamos los datos de entrada.

	if (cargar(puzzles))
	{
		while (!finJuego)
		{
			switch (numOpc = menu())
			{
			case 1:
				intentarJugar(puzzles[numOpc - 1]);
				break;
			case 2:
				intentarJugar(puzzles[numOpc - 1]);
				break;
			case 3:

				if (tryToAdd(puzzles)) {
					cout << "\nSe ha anadido el nuevo puzzle\n";
				}
				else{
					cout << "\nError al anadir el nuevo puzzle\n";
				}

				break;

				
			case 0:

				/*
				 * Si el usuario desea salir de la aplicación (opción 0), el estado de las listas de los puzzles
					reunidos, con posibles nuevos retos, se guardará para las próximas partidas.
					Recordad que antes de terminar la ejecución del programa se debe devolver al sistema
					toda la memoria dinámica que se haya reservado.
				 */
				guardar(puzzles);
				eliminarMemoriaDinamica(puzzles);
				finJuego = true;
				break;
			}
		}
	}
	else
	{
		cout << "\n\nNo se ha podido cargar el fichero : " << NAME_FILE << endl;
	}
}



/*
 * /_//
 */
int menu(){

	int opcion;

	presentacionJuego();
	mostrarMenu();
	cin >> opcion;

	while (opcion < 0 || opcion > 3) {
		cout << "Error, opcion no valida..." << endl << endl;
		mostrarMenu();
		cin >> opcion;
	}

	return opcion;
}

void presentacionJuego() {

	cout << "\n\n-----------------------" << endl;
	cout << "PUZZLE CON MATRICES V.2" << endl;
	cout << "-----------------------\n\n" << endl;
}

/*
 * /_//
 *  
 */
void mostrarMenu() {

	cout << "1. Resolver un puzzle 1D" << endl;
	cout << "2. Resolver un puzzle 2D" << endl;
	cout << "3. Anadir un puzzle al catalogo" << endl;
	cout << "0. Salir" << endl;
	cout << "Elige una opcion: ";
}


/*
 * Vemos que para la opcion 1 y 2 del switch repetimos mucho codigo
 * por lo tanto vamos a implementar un funcion que dada una lista implemente lo propio
 * de esa lista
 * 
 * si elijo un  puzzle debo sabe si es válido o no.
 * 
 * 1) comprobamos si estamos primero en el rango -> lo hace elegirPuzzle(lp)
 * 2) si estamos en el rango comprobamos que no sea -1 o -2
 * 3) por ultimo que pasa con el amigo el cero!
 *
 */
void intentarJugar(tListaPuzzles& lp){

	int opcionLista;

	opcionLista = elegirPuzzle(lp);

	while(opcionLista == -1 || opcionLista == -2){
	
		if(opcionLista == -1){
			ordenarListaMayorAMenor(lp);
		}else{
			ordenarListaMenorAMayor(lp);
		}
	
		borrar();
		opcionLista = elegirPuzzle(lp);
	}

	if(opcionLista != 0){
		mainPuzzle(*lp.listaPuzzle[opcionLista - 1]);
	}
}


/*
Si el usuario selecciona añadir un puzzle al catálogo, el sistema mostrará un listado con
todos los puzzles, primero mostrará el listado de los puzzles 1D y después el listado de
los puzzles 2D.

Ambos listados estarán ordenados, en orden creciente, por número de
	intentos y a igualdad de número de intentos en orden creciente del nombre del puzzle
	(es decir, en el orden en que se mantiene el catálogo durante toda la ejecución del
	programa).

A continuación pedirá el nombre del nuevo puzzle y el nombre del fichero
	en que se encuentra, cargará las matrices del fichero y el máximo número de intentos, y
	si el proceso es correcto se añadirá la información a la lista ordenada del catálogo.

Por último mostrará la lista de todos los puzzles que hay en el catálogo del tipo del nuevo
puzzle. El puzzle que se ha añadido debe figurar en este listado.
*
* 1) Pedir el nombre del fichero (no comporobamos nada)
* 2) pedimos el nombre del fichero -> (asumiendo la ruta de donde estan todos los demás)
* 2.1) comprobamos la extension del fichero si es 1D.txt o 2D.txt
* 3) cargamos el nuevo puzzle a la lista.
* 4) si no existe verificamos la lista donde quiero añadirla. ¿que lista ojito con esto?
* 4.1) comprobar que tipo de puzzle es y si puedo añadirlo lo añado.
* 5) mostrar errores si no he podido cargar el fichero.
*/

/*
 * Funcion sin terminar 
 */
bool tryToAdd(tPuzzlesReunidos& puzzles){

	tPuzzle nuevoPuzzle;
	string nombrePuzzle, nombreFichero, aux;
	bool addpuzzle = false;
	int idLista, auxPos;

	//organizamos y mostramos la lista
	for (int i = 0; i < MODO_JUEGO; i++) {
		ordenarListaMenorAMayor(puzzles[i]);
		mostrarListaNombre(puzzles[i]);
	//	mostrarListaInfo(puzzles[i]);
		cout << endl;
	}

	//NOmbre del fichero
	cout << "Nombre del fichero: ";
	cin >> nombreFichero;

	cin.sync();

	//Como cargar el nombre del puzzle 
	cout << "Nombre puzzle : ";
	cin >> aux;
	getline(cin, nombrePuzzle);
	
	nombrePuzzle = aux + nombrePuzzle; //lucas/n
	//punto de depuracion
	cout << nombrePuzzle;

	if( (nombreFichero.find(tModoJuego[0])) < nombreFichero.size() || (nombreFichero.find(tModoJuego[1])) < nombreFichero.size())
	{
		
		//Cargamos en la estrucutra los campos nombre y fichero
		nuevoPuzzle.nombre_puzzle = nombrePuzzle;
		nuevoPuzzle.nombre_fichero = nombreFichero;

		//cargar el modo al puzzle
		if(nombreFichero.find(tModoJuego[0]))
		{
			nuevoPuzzle.tipo = tModoJuego[0];
		}else
		{
			nuevoPuzzle.tipo = tModoJuego[1];
		}

		//Identificamos a que lista vamos a cargar el puzzle
		// lista[0] -> lista de 1D, lista[1] -> lista de 2D
		idLista = (nuevoPuzzle.tipo == tModoJuego[0]) ? 0 : 1;


		//Antes de cargar debería comprobar si el fichero ya existe en nuestra lista.
		//si existe nos salimos de la ejecución y sino pues seguimos con el procedimiento 
		//que llevamos
		//creamos un reserva de memoria dinamica.

		if(!buscar(puzzles[idLista], &nuevoPuzzle, auxPos))
		{
		
			//Intentamos cargar el fichero con la informacion correspondiente
			//¿que tiene? -> puzzle inicio y puzzle objetivo -> Mn*n y los intentos maximos.
			if (cargar(&nuevoPuzzle, nuevoPuzzle.tipo)) 
			{
				if (insertarOrdenado(puzzles[idLista], nuevoPuzzle)) 
				{
					addpuzzle = true;
				}
			}
		}else{
			addpuzzle = false;
		}

	}

	return addpuzzle;
}


/*
	Eliminamos la memoria dinámica seleccionando
	cada array de puzzle y eliminando cada puzzle

	Además se pone la variable puntero a nullptr 
	y luego nuestro lp.contador = 0;
*/
void eliminarMemoriaDinamica(tPuzzlesReunidos & puzzles){

	for (int i = 0; i < MODO_JUEGO; i++) {
		eliminarMemoriaLista(puzzles[i]);
	}
}