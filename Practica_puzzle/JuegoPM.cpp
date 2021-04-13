#include <iostream>
#include "JuegoPM.h"
#include "Matriz.h""
using namespace std;

/*
 * Al comenzar el juego aparece un menú para seleccionar entre las versiones del juego 
 * modo 1D, modo 2D y la opción de salir. A continuación, se pide el nombre de 
 * fichero que contiene las imágenes inicial y objetivo. Además, el último elemento de 
 * este fichero es el número de acciones o intentos que se tienen para conseguir que la 
 * imagen inicial sea la imagen objetivo.
 */
void mainJuegoPM() {

	//Estructura de nuestro juego
	tJuegoPM juego;
	bool finJuego = true;
	tModo tipoModo = {"1D", "2D"};
	short int opcion;

	while (!finJuego)
	{
		switch (opcion = menu()) {
		case 1: {
			if (!iniciar(juego, tipoModo[opcion - 1], opcion)) {
				cout << "Error al iniciar el juego en modo " << tipoModo[opcion - 1] << endl;
			}
		} break;
		case 2: {
			if (!iniciar(juego, tipoModo[opcion - 1], opcion)) {
				cout << "Error al iniciar el juego en modo " << tipoModo[opcion - 1] << endl;
			}

		} break;
		case 0: {
			finJuego = false;
		} break;
		}
	}
}


/*
 * /_//
 */
int menu(){

	int opcion;

	mostrarMenu();
	cin >> opcion;

	while (opcion < 0 && opcion > 2) {
		cout << "Error...";
		mostrarMenu();
		cin >> opcion;
	}

	return opcion;
}

/*
 * /_//
 *  
 */
void mostrarMenu() {

	cout << "1- Modo 1D" << endl;
	cout << "2- Modo 2D" << endl;
	cout << "0- Salir" << endl;
	cout << "Elija una opcion: ";
}

/*
 * typedef struct{
  tMatrizChar imagenInicial;
  tMatrizChar imagenObjetivo;
  short int numMaxAcciones = 0;
  short int numAccionActuales = 0;
  short int modo;
}tJuegoPM;
 */
bool iniciar(tJuegoPM & jpm, string modo, int num){
	
	bool iniciar = true;
	jpm.modo = num;
	if(cargar(jpm));
	
}

/*
 */
bool cargar(tJuegoPM& jpm);

/*
 */
void mostrar(tJuegoPM const& jpm);

/*
 */
bool jugar(tJuegoPM& jpm);

/*
 */
bool accion(tJuegoPM& jpm);
