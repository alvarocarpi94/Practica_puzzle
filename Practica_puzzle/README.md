# RESUMEN DE LA PRACTICA I "PUZZLE CON MATRICES"



## Dos modos de juego

1. 1D se pueden realizar acciones que a fectan a filas y columnas y diagonales.
2. 2D se pueden realizar acciones que afectan a la propia imagen o partes de la imagen.



## Menu

* modo 1D
* mode 2D
* salir



## Acciones de cada modo:

### Modo 1D



* SF a b: intercambiar las filas a y b de la matriz. 
* SC a b: intercambiar las columnas a y b de la matriz. 
* SD a: intercambiar las diagonales a y -a. Las diagonales positivas se numeran en los índices de las columnas, mientras que las diagonales negativas se numeran en los índices de las filas. La diagonal cero es la diagonal principal. Por ejemplo, la diagonal 1 está formada por los elementos [0,1], [1,2], [2,3], etc. mientras que la diagonal -1 está formada por los elementos [1,0], [2,1], [3,2], etc. 
* VF a: voltear la fila a. Dar la vuelta a la fila a con respecto al eje vertical central de la imagen.
*  VC a: voltear la columna a. Dar la vuelta a la columna a con respecto al eje horizontal central de la imagen. 
* VD a: voltear la diagonal a. Dar la vuelta a la diagonal a con respecto al centro de eje perpendicular de dicha diagonal.



### Modo 2D



* VV: dar la vuelta a la imagen completa con respecto a su eje vertical central. VH: dar la vuelta a la imagen completa con respecto a su eje horizontal central. 

* RD: rotar una imagen 90 grados en el sentido de las agujas del reloj.

* SA a b c d: intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y [c,d]. 
* VD: Dar la vuelta a la imagen completa respecto a la diagonal principal



## Formato archivo de entrada a cada reto



4 4					 // Número de filas y columnas de la primera matriz (inicial)	      NF NC
1 6 6 6         	  // los dígitos de la primera fila    														 D1 D2 … DNC 
6 2 6 6			   … // NF - 2 filas de la primera matriz
6 6 3 6               … // los dígitos de la última fila
6 6 6 4

4 4				   // Número de filas y columnas de la segunda matriz (objetivo)         NF NC
1 6 6 6            // los dígitos de la primera fila																  D1 D2 … DNC 
6 6 6 2        	 … // NF-2 filas de la segunda matriz
6 6 3 6			… // los dígitos de la última fila
6 4 6 6

3					 // número máximo de acciones del reto												M







## Organización de los módulo

1. Coordenada.cpp y coordenada.h
2. Matriz.cpp y Matriz.h
3. JuegoPM.cpp y juegoPm.h
4. UtilidadesSys.cpp y UtilidadesSys.h







# RESUMEN DE LA PRACTICA II "PUZZLE CON MATRICES"



## Nuevo menu principal



1. Resolver un puzzle 1D
2. Resolver un puzzle 2D
3. Añadir un puzzle al catálogo

0. Salir

   Elige un opción

*Importante ya no se carga uno a uno los ficheros, en la v2 se crean cargan todos los ficheros.



## Submenu:



### 1D



Elige una opción: 1

En esta versión están disponibles los siguientes retos

1 Torre con un máximo de 2 movimientos

2 Intercambiar columnas con un máximo de 3 movimientos

3 Intercambiar diagonales con un máximo de 3 movimientos

4 Intercambiar filas con un máximo de 3 movimientos

5 Voltear columna con un máximo de 4 movimientos

6 Voltear diagonal con un máximo de 4 movimientos

7 Voltear fila con un máximo de 4 movimientos

0 salir-

1 Mostrar la lista ordenada de mayor a menor-

2 Mostrar la lista ordenada de menor a mayor



### 2D

Elige una opción: 2

En esta versión están disponibles los siguientes retos

1 Rotar a la derecha con un máximo de 1 movimientos

2 Voltear respecto a la horizontal con un máximo de 1 movimientos

3 Voltear respecto a la vertical con un máximo de 1 movimientos

4 Intercambiar las posiciones vecinas de las posiciones con un máximo de 3 movimientos

5 Voltear respecto a la diagonal principal con un máximo de 3 movimientos

0 salir-

1 Mostrar la lista ordenada de mayor a menor

2 Mostrar la lista ordenada de menor a mayor





## Nuevos modulos respecto V1



Manejan los tipos y funciones necesarios para manejar el catálogo de puzzles.

1)  Puzzle.cpp y Puzzle.h

2) ListaPuzzle.cpp y ListaPuzzle.h





## Formato del archivo de entrada "dataPuzzle.txt"





7															    // Número de puzzles del tipo               N1D   		
Torre														//Nombre del puzzle 1 de tipo 1D        N1
torre1_1D.txt									   	//FIchero que contiene el puzzle 1		F1
Intercambiar columnas                         //....
fichSC_1D.txt
Intercambiar diagonales
fichSD_1D.txt
Intercambiar filas
fichSF_1D.txt
Voltear columna
fichVC_1D.txt
Voltear diagonal
fichVD_1D.txt
Voltear fila
fichVF_1D.txt
5															//Número de puzzle del tipo 2D 					N2D
Rotar a la derecha					      	//Nombre del puzzle 1 de tipo 2D				 N2
patitoRD_2D.txt                                    //Fichero que contiene el puzzle 1               F2
Voltear respecto a la horizontal		//...
patitaVH_2D.txt
Voltear respecto a la vertical
patitaVV_2D.txt
Intercambiar las posiciones vecinas
fichSA_2D.txt
Voltear respecto a la diagonal principal
fichVD_2D.txt



## Implementaciones importantes

1) Un array estático de punteros a variables dinámicas de tipo tPuzzle (ojito)

2) Un arary tPuzzleReunidos, de 2 posiciones, cada una de ella de tipo tListaPuzzles.	

​	2.1 -> La primera lista representa el catálogo de puzzles de tipo 1D

​    2.2 -> La segunda lista representa el catálogo del puzzle de tipo 2D













