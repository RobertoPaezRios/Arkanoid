#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include "src/cJug.class"
#include "src/cBola.class"
#include "src/bloques/cBloqueRojo.class"
#include "src/bloques/cBloqueAzul.class"
#include "src/bloques/cBloqueVerde.class"
#include "src/bloques/cBloqueMorado.class"
#include "src/bloques/cBloqueAmarillo.class"
#include "src/bloques/cBloqueMorado.class"
#include "src/cBloque.class"
using namespace std;
//----------------CONSTANTES---------------//
#define IZQUIERDA 'a'
#define DERECHA 'd'
#define MOVIMIENTO 30
#define MOVIMIENTO_BOLA 10
#define MAX_BLOQUES 5
#define WIDTH 700
#define HEIGHT 700
//----------------GLOBAL-------------------//
cJug* jug = new cJug();
cBola* bola = new cBola();
//BLOQUES//
cBloque *bloques[MAX_BLOQUES] = {
	new cBloqueRojo     (0, 250, 140, 300),
	new cBloqueAzul     (140, 250, 280, 300),
	new cBloqueVerde    (280, 250, 420, 300),
	new cBloqueAmarillo (420, 250, 580, 300),
	new cBloqueMorado   (580, 250, 700, 300),
 };
//----------------FUNCIONES----------------//
void verificaciones (int *puntos);
void guardarPuntos(int puntos);
//----------------MAIN---------------------//
int main () {
	srand (time(NULL));
	int puntos = 0;
	int vidas = 3;

	initwindow (WIDTH, HEIGHT);

	setbkcolor (BLUE);

	for (int i = vidas; i >= 0; i--) {
		//CARGAR BOLA//
		bola->setDir (rand () % 3);
		bola->setX (350);
		bola->setY (250);
		//CARGAR JUGADOR//
		jug->setX1 (250);
		jug->setY1 (600);
		jug->setX2 (350);
		jug->setY2 (575);
		//CARGAR BLOQUES//
		for (int i = 0; i < MAX_BLOQUES; i++) {
			bloques[i]->setToques (0);
			bloques[i]->setEstado (true);
		}
	#pragma region CargaDeBloques
		//BLOQUE ROJO//
		bloques[0]->setX1 (0);
		bloques[0]->setY1 (250);
		bloques[0]->setX2 (140);
		bloques[0]->setY2 (300);
		bloques[0]->setColor (4);
		//BLOQUE AZUL//
		bloques[1]->setX1 (140);
		bloques[1]->setY1 (250);
		bloques[1]->setX2 (280);
		bloques[1]->setY2 (300);
		bloques[1]->setColor (9);
		//BLOQUE VERDE//
		bloques[2]->setX1 (280);
		bloques[2]->setY1 (250);
		bloques[2]->setX2 (420);
		bloques[2]->setY2 (300);
		bloques[2]->setColor (2);
		//BLOQUE MORADO//
		bloques[3]->setX1 (420);
		bloques[3]->setY1 (250);
		bloques[3]->setX2 (580);
		bloques[3]->setY2 (300);
		bloques[3]->setColor (5);
		//BLOQUE AMARILLO//
		bloques[4]->setX1 (580);
		bloques[4]->setY1 (250);
		bloques[4]->setX2 (700);
		bloques[4]->setY2 (300);
		bloques[4]->setColor (14);
	#pragma endregion CargaDeBloques
		while (true) {
			delay (20);
			cleardevice();
	    setcolor(15);
			//PINTAR JUGADOR//
			jug->pintarJug();
			//PINTAR BOLA//
			bola->pintarBola();
			//PINTAR BLOQUES//
	    bloques [0] -> pintar (0, 250, 140, 300);
	    bloques [1] -> pintar (140, 250, 280, 300);
	    bloques [2] -> pintar (280, 250, 420, 300);
	    bloques [3] -> pintar (420, 250, 580, 300);
	    bloques [4] -> pintar (580, 250, 700, 300);
			//PINTAR VIDAS//
			setcolor (2);
			//VIDA 1//
			if (vidas >= 1) {
			rectangle (0, 650, 50, 699);
			setfillstyle (1, 2);
      floodfill (1, 651, 2); }
			//VIDA 2//
			if (vidas >= 2) {
			rectangle (60, 650, 110, 699);
			setfillstyle (1, 2);
      floodfill (61, 651, 2); }
			//VIDA 3//
			if (vidas == 3) {
			rectangle (120, 650, 170, 699);
			setfillstyle (1, 2);
      floodfill (121, 651, 2); }

			if (kbhit()) {
				jug->setTecla(getch());

				if (jug->getTecla() == IZQUIERDA && (jug->getX1 () - 10) > 0) { jug->setX1 (jug->getX1() - MOVIMIENTO); jug->setX2 (jug->getX2() - MOVIMIENTO); }
				if (jug->getTecla() == DERECHA && (jug->getX2 () + 20) < WIDTH) { jug->setX1 (jug->getX1() + MOVIMIENTO); jug->setX2 (jug->getX2() + MOVIMIENTO); }
			}

			switch (bola->getDir()) {
				case 0: bola->setX(bola->getX() - MOVIMIENTO_BOLA); bola->setY(bola->getY() - MOVIMIENTO_BOLA); break; // <- ^
	      case 1: bola->setX(bola->getX() + MOVIMIENTO_BOLA); bola->setY(bola->getY() - MOVIMIENTO_BOLA); break; // -> ^
	      case 2: bola->setX(bola->getX() - MOVIMIENTO_BOLA); bola->setY(bola->getY() + MOVIMIENTO_BOLA); break; // <- _
	      case 3: bola->setX(bola->getX() + MOVIMIENTO_BOLA); bola->setY(bola->getY() + MOVIMIENTO_BOLA); break; // -> _
			}
			verificaciones(&puntos);
			for (int i = 0; i < MAX_BLOQUES; i++) {	cout << bloques[i]->getToques() << " | "; }
			cout << endl;
			cout << vidas << " | ";
			//VIDA MENOS//
			if (bola->getY() > jug->getY1()) { vidas--;break;}
		}
	}

	for (int i = 0; i < MAX_BLOQUES; i++) { cout << bloques[i]->getToques() << endl; }
	guardarPuntos (puntos);
	getch();
	delay(0);
	closegraph();
	delete jug;
	delete bola;
	for (int i = 0; i < MAX_BLOQUES; i++) { delete bloques[i]; }
	system("pause");
	return 0;
}
//------------------------------------VERIFICACIONES--------------------------//
void verificaciones (int *puntos) {
	//MAPA//
	if (bola->getY() == 20 && bola->getDir() == 0) { bola->setDir (2); Beep (500, 100);}
	if (bola->getY() == 20 && bola->getDir() == 1) { bola->setDir (3); Beep (500, 100);}
	if (bola->getX() == (WIDTH - 30) && bola->getDir() == 3) { bola->setDir (2); Beep (500, 100);}
	if (bola->getX() == 20 && bola->getDir() == 2) { bola->setDir (3); Beep (500, 100);}
	if (bola->getX() == (WIDTH - 30) && bola->getDir() == 1) { bola->setDir (0); Beep (500, 100);}
	if (bola->getX() == 20 && bola->getDir() == 0) { bola->setDir (1); Beep (500, 100);}
	//JUGADOR//
	for (int i = 0; i <= 100; i++) {
		if (getpixel (jug->getX1() + i, jug->getY2() - 20) == 15 && bola->getDir () == 3) { bola->setDir(1); *puntos += 50; Beep (900, 100);}
		if (getpixel (jug->getX1() + i, jug->getY2() - 20) == 15 && bola->getDir() == 2) { bola->setDir(0); *puntos += 50; Beep (900, 100);}
		if (getpixel (jug->getX1() + i + 1, jug->getY2() - 20) == 15 && bola->getDir () == 3) { bola->setDir(1); *puntos += 50; Beep (900, 100);}
		if (getpixel (jug->getX1() + i - 1, jug->getY2() - 20) == 15 && bola->getDir () == 2) { bola->setDir(0); *puntos += 50; Beep (900, 100);}
	}
  //BLOQUES//
	//COLISIONES//
  for (int i = 0; i < MAX_BLOQUES; i++) {
		for (int a = bloques[i]->getX1(); a < bloques[i]->getX2(); a++) {
			//ABAJO//
			if (getpixel (a, bloques[i]->getY2() + 1) == 15 && bola->getDir() == 0) { bola->setDir (2); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			if (getpixel (a, bloques[i]->getY2() + 1) == 15 && bola->getDir() == 1) { bola->setDir (3); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			//ARRIBA//
			if (getpixel (a, bloques[i]->getY1() - 1) == 15 && bola->getDir() == 2) { bola->setDir (0); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			if (getpixel (a, bloques[i]->getY1() - 1) == 15 && bola->getDir() == 3) { bola->setDir (1); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
		}
		for (int a = bloques[i]->getY1(); a < bloques[i]->getY2(); a++) {
			//DERECHA//
			if (getpixel (bloques[i]->getX2() + 1, a) == 15 && bola->getDir() == 0) { bola->setDir (1); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			if (getpixel (bloques[i]->getX2() + 1, a) == 15 && bola->getDir() == 2) { bola->setDir (3); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			//IZQUIERDA//
			if (getpixel (bloques[i]->getX1() - 1, a) == 15 && bola->getDir() == 1) { bola->setDir (0); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
			if (getpixel (bloques[i]->getX1() - 1, a) == 15 && bola->getDir() == 3) { bola->setDir (2); Beep (1100, 100); bloques[i]->setToques(bloques[i]->getToques() + 1);}
		}
	}
	//DESTRUCCION//
	for (int i = 0; i < MAX_BLOQUES; i++) {
		if (bloques[i]->getToques() == bloques[i]->getResistencia()) {
			bloques[i]->setX1(0);
			bloques[i]->setX2(0);
			bloques[i]->setY1(0);
			bloques[i]->setY2(0);
			bloques[i]->setColor(getbkcolor());
			bloques[i]->setEstado (false);
		}
	}
}
//------------------------------------GUARDAR PUNTOS--------------------------//
void guardarPuntos (int puntos) {
	ofstream fichero;
	fichero.open ("files/scores.txt", ios::app);
	fichero << puntos << endl;
	fichero.close();
}
