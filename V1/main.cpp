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
using namespace std;
//----------------CONSTANTES---------------//
#define IZQUIERDA 'a'
#define DERECHA 'd'
#define MOVIMIENTO 30
#define MOVIMIENTO_BOLA 10
#define WIDTH 700
#define HEIGHT 700
//----------------GLOBAL-------------------//
cJug* jug = new cJug();
cBola* bola = new cBola();
//----------------FUNCIONES----------------//
void verificaciones (int *puntos);
void guardarPuntos(int puntos);
//----------------MAIN---------------------//
int main () {
	srand (time(NULL));
	int puntos = 0;
	initwindow (WIDTH, HEIGHT);
	bola->setDir (rand () % 3);
	setbkcolor (BLUE);

	while (true) {
		delay (30);
		cleardevice();
		jug->pintarJug();
		bola->pintarBola();

		if (kbhit()) {
			jug->setTecla(getch());

			if (jug->getTecla() == 'a' || jug->getTecla() == 'A' && (jug->getX1()) - 13 >= 0) { jug->setX1(jug->getX1() - MOVIMIENTO); jug->setX2(jug->getX2() - MOVIMIENTO); }
			if (jug->getTecla() == 'd' || jug->getTecla() == 'D' && (jug->getX2() + 13) <= getmaxx()) { jug->setX1(jug->getX1() + MOVIMIENTO); jug->setX2(jug->getX2() + MOVIMIENTO); }
		}

		switch (bola->getDir()) {
			case 0: bola->setX(bola->getX() - MOVIMIENTO_BOLA); bola->setY(bola->getY() - MOVIMIENTO_BOLA); break; // <- ^
      case 1: bola->setX(bola->getX() + MOVIMIENTO_BOLA); bola->setY(bola->getY() - MOVIMIENTO_BOLA); break; // -> ^
      case 2: bola->setX(bola->getX() - MOVIMIENTO_BOLA); bola->setY(bola->getY() + MOVIMIENTO_BOLA); break; // <- _
      case 3: bola->setX(bola->getX() + MOVIMIENTO_BOLA); bola->setY(bola->getY() + MOVIMIENTO_BOLA); break; // -> _
		}
		verificaciones(&puntos);

		//GAME OVER//
		if (bola->getY() > jug->getY1()) { break; exit (0);}
	}

	guardarPuntos (puntos);
	getch();
	delay(0);
	closegraph();
	delete jug;
	delete bola;
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
}
//------------------------------------GUARDAR PUNTOS--------------------------//
void guardarPuntos (int puntos) {
	ofstream fichero;
	fichero.open ("files/scores.txt", ios::app);
	fichero << puntos << endl;
	fichero.close();
}
