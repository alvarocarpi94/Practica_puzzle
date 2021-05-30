

/*
*	NOMBRES:
*		Alvaro Carpizo Garcia
*		Jhimmy Ender Candela
*/

#include "Puzzle.h"
#include "UtilidadesSYS.h"
#include "Matriz.h"
#include <fstream>
#include <iostream>
using namespace std;


/*
 * Según el enunciado la implementacion que tenemos en JuepoPM la traemos a Puzzle 
 * por lo tanto es un copia y pega de esa implementacion, organizando/modificando aquello
 * que necesitemos. De esta manera respectamos lo que es de la interfaz Puzzle.h y si necesitamos
 * mostrar algo más que no guarda relacion la pondríamos en el c.pp
 */

//FUNCION AJENAS A LA INTERFAZ Puzzle.h

void infoAccion1D();
void infoAccion2D();


/*
 *OJo: esta funcion hace lo que hacia nuestro antiguo mainJuego 
 * 
 * 1)
 */
void mainPuzzle(tPuzzle& jpm) {

	chcp1252();
	borrar(); //Borramos para que no nos salga el mensaje de chcp1252();
	//Estructura de nuestro juego

	if (jugar(jpm))
	{
		cout << "\n\Reto solucionado\n";
	}
	else
	{
		cout << "\n\nIntentalo de nuevo\n";
	}

}


bool cargar(tPuzzle * jpm, string modo){

	//variables
	bool aperturaFichero = true;
	ifstream ficheroDeEntrada;
	string nombreFichero;

	nombreFichero += RUTA_DIR.c_str();
	nombreFichero += jpm->nombre_fichero;

	ficheroDeEntrada.open(nombreFichero);

	if (ficheroDeEntrada.is_open()) {

		/*
		 cargar(jpm.imagenInicial, ficheroDeEntrada);
		cargar(jpm.imagenObjetivo, ficheroDeEntrada);
		ficheroDeEntrada >> jpm.numMaxAcciones;
		jpm.numAccionActuales = 0; 

		Cambiamos código para optimizar los return y ver si se carga o no el fichero.
		 */

		if (!cargar(jpm->imagenInicial, ficheroDeEntrada) || !cargar(jpm->imagenObjetivo, ficheroDeEntrada)) {
			aperturaFichero = false;
		}
		else {
			ficheroDeEntrada >> jpm->numMaxAcciones;
			jpm->numAccionActuales = 0;
		}

		ficheroDeEntrada.close();
		aperturaFichero = true;
	}

	return aperturaFichero;
	
}

/*
 * Nuestro mostrar debería limpiar nuestra consola y luego mostrar la nueva informacion 
 */
void mostrar(const tPuzzle& jpm) {


	//borrar();
	// 
	//Mostramos las imagenes jugador y Objetivo
	mostrar(jpm.imagenInicial); //Mostrar del módulo Matriz.h
	mostrar(jpm.imagenObjetivo);

	//Debe mostrar los numero de intentos restantes:
	cout << "\n\nTe quedan " << jpm.numMaxAcciones - jpm.numAccionActuales << " intentos\n\n";

}


bool jugar(tPuzzle& jpm) {
	bool hayGanador = true;

	//1) mostramos el juego actual.
	mostrar(jpm);

	/*
	 * 2) Debemos entrar en un bucle donde comprobemos
	 *  -Cuando hemos superado el maximo de intentos.
	 *  -Poner la imagenInicial como la del objetivo
	 */

	while ((jpm.numAccionActuales < jpm.numMaxAcciones) && !(jpm.imagenInicial == jpm.imagenObjetivo)) {

		if (accion(jpm)) {
			jpm.numAccionActuales++;
		}
		else {
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

	if (jpm.numAccionActuales > jpm.numMaxAcciones) {
		hayGanador = false;
	}

	if (!(jpm.imagenInicial == jpm.imagenObjetivo)) {
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

/*
 *Jugamos lo que teniamos en accion1D y accion2D en uno 
 */
bool accion(tPuzzle & jpm) {


	//cargo el comando (común para 1D y 2D)
	string comando = "";
	bool accionRealizada = false;
	int param1, param2, param3, param4;

	if (jpm.tipo == "1D") {

		//imprimimos la información para la elección del comando
		infoAccion1D();

		//cargo el comando (común para 1D y 2D)
		cout << "Introduzca comando :";
		cin >> comando;
		
		/*
		 * Que queremos conseguir:
		 * SF a b -> SF 1 2
		 * tenemos que trocear nuestro string
		 * SF
		 * 1
		 * 2
		 */
		if (comando == "SF") { //dos paramétros
			cin >> param1 >> param2;
			accionRealizada = swapF(jpm.imagenInicial, param1, param2);
		}
		else if (comando == "SC") {
			cin >> param1 >> param2;
			accionRealizada = swapC(jpm.imagenInicial, param1, param2);
		}
		else if (comando == "SD") {
			cin >> param1;
			accionRealizada = swapD(jpm.imagenInicial, param1);
		}
		else if (comando == "VF") {
			cin >> param1;
			accionRealizada = voltearF(jpm.imagenInicial, param1);
		}
		else if (comando == "VC") {
			cin >> param1;
			accionRealizada = voltearC(jpm.imagenInicial, param1);
		}
		else if (comando == "VD") {
			cin >> param1;
			accionRealizada = voltearD(jpm.imagenInicial, param1);
		}
	}
	else {

		infoAccion2D();

		cout << "Introduzca comando :";
		cin >> comando;
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
		else if (comando == "VH") { //No tiene parámetros
			voltearH(jpm.imagenInicial);
			accionRealizada = true;
		}
		else if (comando == "RD") {//No tiene parámetros
			rotarD(jpm.imagenInicial);
			accionRealizada = true;
		}
		else if (comando == "SA") {//Tiene 4 parámetros
			cin >> param1 >> param2 >> param3 >> param4;
			tCoor pos1, pos2;
			pos1.coorX = param1;
			pos1.coorY = param2;
			pos2.coorX = param3;
			pos2.coorY = param4;

			accionRealizada = swapAdy(jpm.imagenInicial, pos1, pos2);
		}
		else if (comando == "VD") { //No tiene parámetros
			accionRealizada = VoltearID(jpm.imagenInicial);
		}
	}

	return accionRealizada;
}


void infoAccion1D() {

	cout << "--------------------------------------------------" << endl;
	cout << "Ayuda para elegir la acción 1D respecto al fichero" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\nSF a b: intercambiar filas a y b de la matriz" << endl;
	cout << "SC a b: intercambiar las columnas a y b de la matriz" << endl;
	cout << "SD a: intercambiar las diagonales a y -a" << endl;
	cout << "VF a: voltear a la fila a" << endl;
	cout << "VC a: voltear la columna a" << endl;
	cout << "VD a: voltear la diagonal a\n" << endl;
}


void infoAccion2D() {

	cout << "--------------------------------------------------" << endl;
	cout << "Ayuda para elegir la acción 2D respecto al fichero" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\nVV: dar la vuelta a la imagen completa con respecto a su eje vertical central" << endl;
	cout << "VH: dar la vuelta a la imagen completa respecto a su eje horizontal central" << endl;
	cout << "RD: rotar una imagen 90 grados en el sentido de las agujas del reloj" << endl;
	cout << "SA: a b c d: intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y [c,d]" << endl;
	cout << "VD: Dar la vuelta a la imagen completa respecto a la diagonal principal\n" << endl;

}


void mostrarInfo(const tPuzzle& jpm){

	cout << jpm.nombre_puzzle;
	cout << " con un maximo de " << jpm.numMaxAcciones;
	cout << " movimientos\n";
}


void mostrarNombre(const tPuzzle& jpm){

	cout << jpm.nombre_puzzle << " Fichero: " << jpm.nombre_fichero << endl;
}

//IMPLEMENTACION DE LAS FUNCIONES DE OPERATOR
/*
 * Para la claves de ordenacion tenemos en cuenta:
 * 1) el maximo de movimiento que tenemos lo primero.
 * 2) el nombre del reto.
 * 
 * Complicacione que pasa si son iguales en el numMaxAcciones pues deberiamos
 * comparar por otra clave de ordenacion o no hacer nada.
 */

/*
 * Comprobamos si dos puzzle son iguales.
 */
bool operator == (const tPuzzle& puzzle1, const tPuzzle& puzzle2){
		
	return ((puzzle1.numMaxAcciones == puzzle2.numMaxAcciones) &&
		(puzzle1.nombre_puzzle == puzzle2.nombre_puzzle));
}

/*
 * Comprobamos si el puzzle 1 es menor que el puzzle 2
 */
bool operator < (const tPuzzle& puzzle1, const tPuzzle& puzzle2){

	
	return ((puzzle1.numMaxAcciones == puzzle2.numMaxAcciones) ?
		(puzzle1.nombre_fichero < puzzle2.nombre_fichero) :
		(puzzle1.numMaxAcciones < puzzle2.numMaxAcciones));
}

/*
 * Comprobamos si el puzzle 1 es mayor que el puzzle 2
 */
bool operator > (const tPuzzle& puzzle1, const tPuzzle& puzzle2){

	return ((puzzle1.numMaxAcciones == puzzle2.numMaxAcciones) ?
		(puzzle1.nombre_fichero > puzzle2.nombre_fichero) :
		(puzzle1.numMaxAcciones > puzzle2.numMaxAcciones));
}

