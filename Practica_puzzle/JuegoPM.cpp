#include <iostream>
#include <fstream> //Uso de ficheros
#include <string>
#include "JuegoPM.h"
#include "Matriz.h"
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

	if(num < 1 && num > 2){
		iniciar = false;
	}else{
		jpm.modo = num;
		iniciar = cargar(jpm);
	}

	return iniciar;
}

/*
 *	Cargamos el fichero correspondiente
	* typedef struct{
	tMatrizChar imagenInicial;
	tMatrizChar imagenObjetivo;
	short int numMaxAcciones = 0;
	short int numAccionActuales = 0;
	short int modo; -> esto lo sabemos
	}tJuegoPM;
 */
bool cargar(tJuegoPM& jpm){
	//variables
	bool aperturaFichero = true;
	ifstream ficheroDeEntrada;
	string ruta = "ficheros_retos/";
	string nombreFichero;

	//el usuario solo se preocupa por el nombre
	cout << "Nombre del fichero " << endl;
	cin >> nombreFichero;

	//hay que concatenar la ruta + nombre del fichero + modo
	ruta += nombreFichero;

	if(jpm.modo == 1){
		ruta += "_1D.txt";
	}else{
		ruta += "_2D.txt";
	}
 
	ficheroDeEntrada.open(ruta);

	if(ficheroDeEntrada.is_open()){

		cargar(jpm.imagenInicial, ficheroDeEntrada);
		cargar(jpm.imagenObjetivo, ficheroDeEntrada);
		ficheroDeEntrada >> jpm.numMaxAcciones;
	}else{
		aperturaFichero = false;
	}

	return aperturaFichero;
}

/*
 *  Partiendo que cada modulo realiza su implementacion
 *	 mostrar -> Matriz.cpp debería mostrarla.
 */
void mostrar(tJuegoPM const& jpm){

	//Mostramos las imagenes jugador y Objetivo
	mostrar(jpm.imagenInicial);
	mostrar(jpm.imagenObjetivo);

	//Debe mostrar los numero de intentos restantes:
	cout << "Intentos maximo: " << jpm.numMaxAcciones;
	cout << "Intentos actuales: " << jpm.numAccionActuales;
	cout << "Intentos restantes: " << jpm.numMaxAcciones - jpm.numAccionActuales;

}

/*
 *	Controlará quien gana y que no supere los intentos maximos
 */
bool jugar(tJuegoPM & jpm){
		
	bool hayGanador = true;

	//1) mostramos el juego actual.
	mostrar(jpm);

	/*
	 * 2) Debemos entrar en un bucle donde comprobemos 
	 *  -Cuando hemos superado el maximo de intentos.
	 *  -Poner la imagenInicial como la del objetivo
	 */

	 while((jpm.numAccionActuales < jpm.numMaxAcciones) && !(jpm.imagenInicial == jpm.imagenObjetivo)){
		
		if(accion(jpm)){
			jpm.numAccionActuales++;	
		}
		
		mostrar(jpm);	
	 }

	 /*
	  * Mostramos mensajes:
	  * -Si lo conseguimos == imagen
	  * -Si falllamos ==  alcanzamos el maximo de intentos.
	  */

	  if(jpm.numAccionActuales > jpm.numMaxAcciones){
		 hayGanador = false;
	  }

	  if(!(jpm.imagenInicial == jpm.imagenObjetivo)){
		  hayGanador = false;
	  }


	  return hayGanador;
}

/*
 * Las acciones en modo 1D son:
	SF a b: intercambiar las filas a y b de la matriz.
	SC a b: intercambiar las columnas a y b de la matriz.
	SD a: intercambiar las diagonales a y -a. Las diagonales positivas se numeran en los
		índices de las columnas, mientras que las diagonales negativas se numeran en los
		índices de las filas. La diagonal cero es la diagonal principal. Por ejemplo, la diagonal
		1 está formada por los elementos [0,1], [1,2], [2,3], etc. mientras que la diagonal -1 está
		formada por los elementos [1,0], [2,1], [3,2], etc.
	VF a: voltear la fila a. Dar la vuelta a la fila a con respecto al eje vertical central de la
		imagen.
	VC a: voltear la columna a. Dar la vuelta a la columna a con respecto al eje horizontal
		central de la imagen.
	VD a: voltear la diagonal a. Dar la vuelta a la diagonal a con respecto al centro de eje
		perpendicular de dicha diagonal.
 * 
 * Las acciones en el modo 2D son:
	VV: dar la vuelta a la imagen completa con respecto a su eje vertical central.
	VH: dar la vuelta a la imagen completa con respecto a su eje horizontal central.
	RD: rotar una imagen 90 grados en el sentido de las agujas del reloj.
	SA a b c d: intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y
	[c,d].
	VD: Dar la vuelta a la imagen completa respecto a la diagonal principal

	Planteamiento:

	dependiendo de lo que tengamos en jpm.modo se permitirá hacer
	las opciones que quiera el usuario.

 */
bool accion(tJuegoPM& jpm){

	bool accion = false;
	string comando;
	char aux;
	int a, b, c, d;

	cout << "Introduzca un comando :";
	/*
	 * Que queremos conseguir:
	 * SF a b -> SF 1 2
	 * tenemos que trocear nuestro string
	 * SF
	 * 1
	 * 2
	 */
	//submesanio = llamada.llamadas[i].fechaLlamada.substr(3, 7); 
	getline(cin, comando);

	cin >> comando;
	if(comando == "SF"){
		cin >> a >> b ;
	}else if(comando == "LX"){
		cin >> b >> c >> d; 
	
	}

	int p1 = atoi(comando);
	if(jpm.modo == 1){
		infoAccion1D();
		accion1D
	}else{
		infoAccion2D();
		accion2D
	}
	
	return accion;
}


void infoAccion1D() {

	cout << "SF a b: intercambiar a y b de la matriz" << endl;
	cout << "SC a b: intercambiar las columnas a y b de la matriz" << endl;
	cout << "SD a: intercambiar las diagonales a y -a" << endl;
	cout << "VF a: voltear a la fila a" << endl;
	cout << "VC a: voltear la columna a" << endl;
	cout << "VD a: voltear la diagonal a" << endl;
}

void infoAccion2D() {

	cout << "VV: dar la vuelta a la imagen completa con respecto a su eje vertical central" << endl;
	cout << "VH: dar la vuelta a la imagen completa respecto a su eje horizontal central" << endl;
	cout << "RD: rotar una imagen 90 grados en el sentido de las agujas del reloj" << endl;
	cout << "SA: a b c d: intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y [c,d]" << endl;
	cout << "VD: Dar la vuelta a la imagen completa respecto a la diagonal principal" << endl;

}



