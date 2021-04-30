
/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#include <iostream>
#include <fstream> //Uso de ficheros
#include <string>	//uso de strings
#include "JuegoPM.h"
#include "Matriz.h"
#include "UtilidadesSYS.h"
#include "Coordenada.h"


/*
 * Al comenzar el juego aparece un men� para seleccionar entre las versiones del juego 
 * modo 1D, modo 2D y la opci�n de salir. A continuaci�n, se pide el nombre de 
 * fichero que contiene las im�genes inicial y objetivo. Adem�s, el �ltimo elemento de 
 * este fichero es el n�mero de acciones o intentos que se tienen para conseguir que la 
 * imagen inicial sea la imagen objetivo.
 */

int main() {

	mainJuegoPM();
	
	system("pause");
	return 0;
}
void mainJuegoPM() {

	chcp1252();
	borrar(); //Borramos para que no nos salga el mensaje de chcp1252();
	//Estructura de nuestro juego
	tJuegoPM juego;
	bool finJuego = false;
	short int numOpc;

	presentacionJuego();

	while (!finJuego)
	{
		switch (numOpc = menu()) {
		case 1: {
			string modoJ = "1D";
			if (!iniciar(juego, modoJ, numOpc)) {
				cout << "Error al iniciar el juego en modo " << "1D" << endl;
			}

			empezarJugar(juego);
	
		} break;
		case 2: {
			string modoJ = "2D";
			if (!iniciar(juego,modoJ, numOpc)) {
				cout << "Error al iniciar el juego en modo " << "2D" << endl;
			}

			empezarJugar(juego);
	
		} break;
		case 0: {
			finJuego = true;
			cout << "\nSaliendo del juego..." << endl;
			cout << "Hasta pronto" << endl << endl;
		} break;
		}

	}
}




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

*/

mainPuzzlesReunidos


/*
 * /_//
 */
int menu(){

	int opcion;

	presentacionJuego();
	mostrarMenu();
	cin >> opcion;

	while (opcion < 0 || opcion > 2) {
		cout << "Error, opci�n no v�lida..." << endl << endl;
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
	cout << "3. Añadir un puzzle al catálgo" << endl;
	cout << "0. Salir" << endl;
	cout << "Elige una opcion: ";
}
