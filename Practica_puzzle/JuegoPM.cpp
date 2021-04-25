
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
	short int opcion;

	presentacionJuego();

	while (!finJuego)
	{
		switch (opcion = menu()) {
		case 1: {
			string modoJ = "1D";
			if (!iniciar(juego, modoJ, opcion)) {
				cout << "Error al iniciar el juego en modo " << "1D" << endl;
			}

			empezarJugar(juego);
	
		} break;
		case 2: {
			string modoJ = "2D";
			if (!iniciar(juego,modoJ, opcion)) {
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

void empezarJugar(tJuegoPM& juego) {

	if (jugar(juego)) {
		cout << "\nHas ganado\n" << endl;	
	}
	else {
		cout << "\nHas perdido\n" << endl;
	
	}
	pausa();
	borrar();

}

/*
 * /_//
 */
int menu(){

	int opcion;

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

	cout << "-------------------" << endl;
	cout << "Puzzle con matrices" << endl;
	cout << "-------------------" << endl;
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
		jpm.modo = modo;
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
	cout << "\nNombre del fichero :";
	cin >> nombreFichero;

	//hay que concatenar la ruta + nombre del fichero + modo
	ruta += nombreFichero;

	if(jpm.modo == "1D"){
		ruta += "_1D.txt";
	}else{
		ruta += "_2D.txt";
	}
 
	ficheroDeEntrada.open(ruta);

	if(ficheroDeEntrada.is_open()){

		cargar(jpm.imagenInicial, ficheroDeEntrada);
		cargar(jpm.imagenObjetivo, ficheroDeEntrada);
		ficheroDeEntrada >> jpm.numMaxAcciones;
		jpm.numAccionActuales = 0;
	}else{
		aperturaFichero = false;
	}

	return aperturaFichero;
}

/*
 *  Partiendo que cada modulo realiza su implementacion
 *	 mostrar -> Matriz.cpp deber�a mostrarla.
 */
void mostrar(tJuegoPM const& jpm){

	borrar();
	//Mostramos las imagenes jugador y Objetivo
	mostrar(jpm.imagenInicial); //Mostrar del m�dulo Matriz.h
	mostrar(jpm.imagenObjetivo); 

	//Debe mostrar los numero de intentos restantes:
	cout << "Intentos maximo: " << jpm.numMaxAcciones << endl;
	cout << "Intentos actuales: " << jpm.numAccionActuales << endl;
	cout << "Intentos restantes: " << jpm.numMaxAcciones - jpm.numAccionActuales << endl << endl;

}

/*
 *	Controlar� quien gana y que no supere los intentos maximos
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
		}else{
			cout << "Comando erroneo\n";
			pausa();
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
		�ndices de las columnas, mientras que las diagonales negativas se numeran en los
		�ndices de las filas. La diagonal cero es la diagonal principal. Por ejemplo, la diagonal
		1 est� formada por los elementos [0,1], [1,2], [2,3], etc. mientras que la diagonal -1 est�
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

	dependiendo de lo que tengamos en jpm.modo se permitir� hacer
	las opciones que quiera el usuario.

 */
bool accion(tJuegoPM& jpm){

	bool accion = false;

	if(jpm.modo == "1D"){
		
		accion = accion1D(jpm);
	}else{
		
		accion = accion2D(jpm);
	}
	
	return accion;
}

bool accion1D(tJuegoPM& jpm){

	//si no encuentro el comando me salgo
	bool accionRealizada = false;

	string comando;

	//imprimimos la informaci�n para la elecci�n del comando
	infoAccion1D();

	//cargo el comando (com�n para 1D y 2D)
	cout << "Introduzca comando :";
	cin >> comando;

	int param1, param2;
	/*
	 * Que queremos conseguir:
	 * SF a b -> SF 1 2
	 * tenemos que trocear nuestro string
	 * SF
	 * 1
	 * 2
	 */
	if(comando == "SF"){ //dos param�tros
		cin >> param1 >> param2;
		accionRealizada = swapF(jpm.imagenInicial, param1, param2);
	}else if(comando == "SC"){
		cin >> param1 >> param2;
		accionRealizada = swapC(jpm.imagenInicial, param1, param2);
	}else if (comando == "SD") {
		cin >> param1;
		accionRealizada = swapD(jpm.imagenInicial, param1);
	}else if (comando == "VF") {
		cin >> param1;
		accionRealizada = voltearF(jpm.imagenInicial, param1);
	}else if (comando == "VC") {
		cin >> param1;
		accionRealizada = voltearC(jpm.imagenInicial, param1);
	}else if (comando == "VD") {
		cin >> param1;
		accionRealizada = voltearD(jpm.imagenInicial, param1);
	}

	return accionRealizada;
}

bool accion2D(tJuegoPM& jpm) {

	//si no encuentro el comando me salgo
	bool accionRealizada = false;

	infoAccion2D();

	//cargo el comando (com�n para 1D y 2D)
	string comando = ""; 

	cout << "Introduzca comando :";
	cin >> comando;

	int param1, param2, param3, param4;
	/*
	 * Que queremos conseguir:
	 * SF a b -> SF 1 2
	 * tenemos que trocear nuestro string
	 * SF
	 * 1
	 * 2
	 */
	if (comando == "VV") { //No tiene parametros
		voltearV(jpm.imagenInicial);
		accionRealizada = true;
	}
	else if (comando == "VH") { //No tiene par�metros
		voltearH(jpm.imagenInicial);
		accionRealizada = true;
	}
	else if (comando == "RD") {//No tiene par�metros
		rotarD(jpm.imagenInicial);
		accionRealizada = true;
	}
	else if (comando == "SA") {//Tiene 4 par�metros
		cin >> param1 >> param2 >> param3 >> param4;
		tCoor pos1, pos2;
		pos1.coorX = param1;
		pos1.coorY = param2;
		pos2.coorX = param3;
		pos2.coorY = param4;

		accionRealizada = swapAdy(jpm.imagenInicial, pos1, pos2);
	}
	else if (comando == "VD") { //No tiene par�metros
		accionRealizada = VoltearID(jpm.imagenInicial);
	}

	return accionRealizada;
}


void infoAccion1D() {

	cout << "--------------------------------------------------" << endl;
	cout << "Ayuda para elegir la acci�n 1D respecto al fichero" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\nSF a b: intercambiar a y b de la matriz" << endl;
	cout << "SC a b: intercambiar las columnas a y b de la matriz" << endl;
	cout << "SD a: intercambiar las diagonales a y -a" << endl;
	cout << "VF a: voltear a la fila a" << endl;
	cout << "VC a: voltear la columna a" << endl;
	cout << "VD a: voltear la diagonal a\n" << endl;
}

void infoAccion2D() {

	cout << "--------------------------------------------------" << endl;
	cout << "Ayuda para elegir la acci�n 2D respecto al fichero" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\nVV: dar la vuelta a la imagen completa con respecto a su eje vertical central" << endl;
	cout << "VH: dar la vuelta a la imagen completa respecto a su eje horizontal central" << endl;
	cout << "RD: rotar una imagen 90 grados en el sentido de las agujas del reloj" << endl;
	cout << "SA: a b c d: intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y [c,d]" << endl;
	cout << "VD: Dar la vuelta a la imagen completa respecto a la diagonal principal\n" << endl;

}



