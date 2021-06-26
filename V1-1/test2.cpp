#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "src/bloques/cBloqueRojo.class"
#include "src/bloques/cBloqueAzul.class"
#include "src/bloques/cBloqueVerde.class"
#include "src/bloques/cBloqueMorado.class"
#include "src/bloques/cBloqueAmarillo.class"
#include "src/bloques/cBloqueMorado.class"
#include "src/cBloque.class"

#define WIDTH 1920
#define HEIGHT 1080
#define MAX_BLOQUES 5

using namespace std;

int main () {
  srand(time(NULL));
  initwindow (WIDTH, HEIGHT);

  int x1, y1, x2, y2;
  int i, a;
  //BLOQUES//
  cBloque *bloques[MAX_BLOQUES] = {
    new cBloqueRojo     (0, 0, 0, 0),
    new cBloqueAzul     (0, 0, 0, 0),
    new cBloqueVerde    (0, 0, 0, 0),
    new cBloqueAmarillo (0, 0, 0, 0),
    new cBloqueMorado   (0, 0, 0, 0),
   };


   for (i = 0; i < MAX_BLOQUES; i++) {
     for (a = bloques[i]->getX1(); a < bloques[i]->getX2(); i++) {
       cout << "hola";
     }
   }

  bloques [0] -> pintar (0, 0, 50, 30);
  bloques [1] -> pintar (60, 0, 110, 30);
  bloques [2] -> pintar (120, 0, 170, 30);
  bloques [3] -> pintar (180, 0, 230, 30);
  bloques [4] -> pintar (240, 0, 290, 30);



  getch();
  delay (0);
  closegraph ();
  system ("pause");
  return 0;
}
