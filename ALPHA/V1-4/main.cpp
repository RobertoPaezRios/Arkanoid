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
#define MAX_BLOQUES 10
#define MAX_NIVEL 3
#define WIDTH 700
#define HEIGHT 700
//----------------GLOBAL-------------------//
cJug* jug = new cJug();
cBola* bola = new cBola();
//BLOQUES//
cBloque *bloques[MAX_BLOQUES] = {
	new cBloqueRojo     (0, 100, 140, 150),
	new cBloqueAzul     (140, 100, 280, 150),
	new cBloqueVerde    (280, 100, 420, 150),
	new cBloqueAmarillo (420, 100, 580, 150),
	new cBloqueMorado   (580, 100, 700, 150),
	new cBloqueRojo     (0, 170, 140, 220),
	new cBloqueAzul     (140, 170, 280, 220),
	new cBloqueVerde    (280, 170, 420, 220),
	new cBloqueAmarillo (420, 170, 580, 220),
	new cBloqueMorado   (580, 170, 700, 220),
 };
//----------------FUNCIONES----------------//
void verificaciones (int *puntos, bool *victoria);
void guardarPuntos(int puntos);
void pintarFinal ();
void pintarInicio ();
void pintarVictoria ();
void pintarVidas (int vidas);
void cargarBloques ();
void pintarBloques ();
//----------------MAIN---------------------//
int main () {
	srand (time(NULL));
	int puntos = 0;
	int vidas = 3;
	int nivel = 1;
	int cont = 0;
	ofstream fichero;
	bool victoria = false;

	initwindow (WIDTH, HEIGHT);

	pintarInicio ();

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
		cargarBloques ();
		while (victoria == false) {
			delay (0);
			cleardevice();
	    setcolor(15);
			//PINTAR JUGADOR//
			jug->pintarJug();
			//PINTAR BOLA//
			bola->pintarBola();
			pintarBloques ();
			//PINTAR VIDAS//
			setcolor (2);
			pintarVidas(vidas);

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
			verificaciones(&puntos, &victoria);
			for (int i = 0; i < MAX_BLOQUES; i++) {	cout << bloques[i]->getToques() << " | "; }
			cout << endl;
			cout << vidas << " | ";
			//VIDA MENOS//
			if (bola->getY() > jug->getY1()) { vidas--;break;}
			//GUARDAR LOS DATOS DE LA PARTIDA//
			fichero.open("files/registro.txt", ios::app);
			for (int i = 0; i < MAX_BLOQUES; i++) { cont++; fichero << bloques[i]->getToques() << " | "; if (cont == 5) { cont = 0;fichero << endl; }}
			fichero.close();
		}
	}

	if (vidas <= 1) pintarFinal();
	else pintarVictoria();

	for (int i = 0; i < MAX_BLOQUES; i++) { cout << bloques[i]->getToques(); }
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
void verificaciones (int *puntos, bool *victoria) {
	int cont = 0;
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
	//VICTORIA//
	for (int i = 0; i < MAX_BLOQUES; i++) { if (bloques[i]->getEstado() == false) { cont++; if (cont == MAX_BLOQUES) { *victoria = true; *puntos+=1000; }}}
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
//------------------------------------PINTAR FINAL----------------------------//
void pintarFinal () {
	//SONIDO//
	Beep (1000, 500);
	Beep (800, 500);
	Beep (600, 500);
	Beep (400, 500);
	Beep (200, 500);
	Beep (100, 500);
	//IMAGEN//
	settextstyle (3, 0, 30);
	setcolor (14);
	outtextxy (150, 350, "GAME OVER");
}
//-----------------------------------PINTAR INICIO----------------------------//
void pintarInicio () {
	settextstyle (3, 0, 20);
	setcolor (4);
	outtextxy (50, 350, "ARKANOID");
	circle (340, 200, 100);
	setfillstyle (1, 4);
	floodfill (340 + 1, 200 + 1, 4);
	while (true) {
		if (kbhit()) break;
		Beep (100, 500);
		Beep (200, 500);
		Beep (400, 500);
		Beep (600, 500);
		Beep (800, 500);
		Beep (1000, 500);
		Beep (800, 500);
		Beep (600, 500);
		Beep (400, 500);
		Beep (200, 500);
		Beep (100, 500);
	}
}
//----------------------------------PINTAR VICTORIA---------------------------//
void pintarVictoria () {
	Beep (100, 500);
	Beep (200, 500);
	Beep (400, 500);
	Beep (600, 500);
	Beep (800, 500);
	Beep (1000, 500);
	settextstyle (3, 0, 20);
	setcolor (14);
	outtextxy (50, 350, "VICTORIA");
	getch();
}
//-----------------------------------PINTAR VIDAS-----------------------------//
void pintarVidas (int vidas) {
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
}
//-----------------------------------CARGAR BLOQUES---------------------------//
void cargarBloques () {
	//CARGAR BLOQUES//
	for (int i = 0; i < MAX_BLOQUES; i++) {
		bloques[i]->setToques (0);
		bloques[i]->setEstado (true);
	}
	//FILA 1//
	//BLOQUE ROJO//
	bloques[0]->setX1 (0);
	bloques[0]->setY1 (100);
	bloques[0]->setX2 (140);
	bloques[0]->setY2 (150);
	bloques[0]->setColor (4);
	//BLOQUE AZUL//
	bloques[1]->setX1 (140);
	bloques[1]->setY1 (100);
	bloques[1]->setX2 (280);
	bloques[1]->setY2 (150);
	bloques[1]->setColor (9);
	//BLOQUE VERDE//
	bloques[2]->setX1 (280);
	bloques[2]->setY1 (100);
	bloques[2]->setX2 (420);
	bloques[2]->setY2 (150);
	bloques[2]->setColor (2);
	//BLOQUE MORADO//
	bloques[3]->setX1 (420);
	bloques[3]->setY1 (100);
	bloques[3]->setX2 (580);
	bloques[3]->setY2 (150);
	bloques[3]->setColor (5);
	//BLOQUE AMARILLO//
	bloques[4]->setX1 (580);
	bloques[4]->setY1 (100);
	bloques[4]->setX2 (700);
	bloques[4]->setY2 (150);
	bloques[4]->setColor (14);
	//FILA 2//
	//BLOQUE ROJO//
	bloques[5]->setX1 (0);
	bloques[5]->setY1 (170);
	bloques[5]->setX2 (140);
	bloques[5]->setY2 (220);
	bloques[5]->setColor (4);
	//BLOQUE AZUL//
	bloques[6]->setX1 (140);
	bloques[6]->setY1 (170);
	bloques[6]->setX2 (280);
	bloques[6]->setY2 (220);
	bloques[6]->setColor (9);
	//BLOQUE VERDE//
	bloques[7]->setX1 (280);
	bloques[7]->setY1 (170);
	bloques[7]->setX2 (420);
	bloques[7]->setY2 (220);
	bloques[7]->setColor (2);
	//BLOQUE MORADO//
	bloques[8]->setX1 (420);
	bloques[8]->setY1 (170);
	bloques[8]->setX2 (580);
	bloques[8]->setY2 (220);
	bloques[8]->setColor (5);
	//BLOQUE AMARILLO//
	bloques[9]->setX1 (580);
	bloques[9]->setY1 (170);
	bloques[9]->setX2 (700);
	bloques[9]->setY2 (220);
	bloques[9]->setColor (14);
}
//----------------------------------PINTAR BLOQUES----------------------------//
void pintarBloques () {
	//PINTAR BLOQUES//
	bloques [0] -> pintar (0, 100, 140, 150);
	bloques [1] -> pintar (140, 100, 280, 150);
	bloques [2] -> pintar (280, 100, 420, 150);
	bloques [3] -> pintar (420, 100, 580, 150);
	bloques [4] -> pintar (580, 100, 700, 150);
	bloques [5] -> pintar (0, 170, 140, 220);
	bloques [6] -> pintar (140, 170, 280, 220);
	bloques [7] -> pintar (280, 170, 420, 220);
	bloques [8] -> pintar (420, 170, 580, 220);
	bloques [9] -> pintar (580, 170, 700, 220);
}
