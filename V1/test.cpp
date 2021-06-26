#include <graphics.h>
#include <iostream>
#include <conio.h>
//#include "src/cBloqueRojo.class"
//#include "src/cBloqueAzul.class"
using namespace std;

#define WIDTH 1920
#define HEIGHT 1080

class cBloque {
  private:
    int largo, ancho;
    int x1, y1, x2, y2;
    int color;
    bool estado;
    int resistencia;
    int toques;
  public:
    //SETS//
    void setX1 (int x1) { this->x1 = x1; }
    void setY1 (int y1) { this->y1 = y1; }
    void setX2 (int x2) { this->x2 = x2; }
    void setY2 (int y2) { this->y2 = y2; }
    void setLargo (int largo) { this->largo = largo; }
    void setAncho (int ancho) { this->ancho = ancho; }
    void setColor (int color) { this->color = color; }
    void setEstado (bool estado) { this->estado = estado; }
    void setResistencia (int resistencia) { this->resistencia = resistencia; }
    void setToques (int toques) { this->toques = toques; }
    //GETS//
    int getX1 () { return x1; }
    int getY1 () { return y1; }
    int getX2 () { return x2; }
    int getY2 () { return y2; }
    int getColor () { return color; }
    bool setEstado () { return estado; }
    int getResistencia () { return resistencia; }
    int getToques () { return toques; }
    int getLargo () { return largo; }
    int getAncho () { return ancho; }
};
class cBloqueAzul : public cBloque {
  public:
    //CONSTRUCTOR//
      cBloqueAzul (int x1, int y1, int x2, int y2) {
      setLargo (15);
      setAncho (30);
      setColor(9);
      setEstado (true);
      setResistencia (4);
      setX1 (x1);
      setY1 (y1);
      setX2 (x2);
      setY2 (y2);
    }
    //METODOS//
    void pintarBloqueAzul (){
      setcolor (getColor());
      rectangle (getX1(), getY1(), getX2(), getY2());
      setfillstyle (1, getColor());
      floodfill (getX1() + 1, getY1() + 1, getColor());
    }
};
class cBloqueRojo : public cBloque {
  private:
    int x1, y1, x2, y2;
  public:
    //CONSTRUCTOR//
    cBloqueRojo (int x1, int y1, int x2, int y2) {
      setLargo (15);
      setAncho (30);
      setColor(4);
      setEstado (true);
      setResistencia (4);
      this->x1 = x1;
      this->y1 = y1;
      this->x2 = x2;
      this->y2 = y2;
    }
    //SETS//
    void setX1 (int x1) { this->x1 = x1; }
    void setY1 (int y1) { this->y1 = y1; }
    void setX2 (int x2) { this->x2 = x2; }
    void setY2 (int y2) { this->y2 = y2; }
    //GETS//
    int getX1 () { return x1; }
    int getY1 () { return y1; }
    int getX2 () { return x2; }
    int getY2 () { return y2; }
    //METODOS//
    void pintarBloqueRojo (){
      setcolor (getColor());
      rectangle (this->getX1(), this->getY1(), getX2(), getY2());
      setfillstyle (1, getColor());
      floodfill (this->x1 + 1, this->y1 + 1, getColor());
    }
};
class cBloqueVerde : public cBloque {
  public:
    //CONSTRUCTOR//
      cBloqueVerde (int x1, int y1, int x2, int y2) {
      setLargo (15);
      setAncho (30);
      setColor(2);
      setEstado (true);
      setResistencia (4);
      setX1 (x1);
      setY1 (y1);
      setX2 (x2);
      setY2 (y2);
    }
    //METODOS//
    void pintarBloqueVerde (){
      setcolor (getColor());
      rectangle (getX1(), getY1(), getX2(), getY2());
      setfillstyle (1, getColor());
      floodfill (getX1() + 1, getY1() + 1, getColor());
    }
};
class cBloqueAmarillo : public cBloque {
  public:
    //CONSTRUCTOR//
      cBloqueAmarillo (int x1, int y1, int x2, int y2) {
      setLargo (15);
      setAncho (30);
      setColor(14);
      setEstado (true);
      setResistencia (4);
      setX1 (x1);
      setY1 (y1);
      setX2 (x2);
      setY2 (y2);
    }
    //METODOS//
    void pintarBloqueAmarillo (){
      setcolor (getColor());
      rectangle (getX1(), getY1(), getX2(), getY2());
      setfillstyle (1, getColor());
      floodfill (getX1() + 1, getY1() + 1, getColor());
    }
};

int main () {
  initwindow (WIDTH, HEIGHT);

    bloques [10];
  cBloqueRojo* bloqueRojo = new cBloqueRojo(0, 0, 50, 30);
  cBloqueAzul* bloqueAzul = new cBloqueAzul (51, 0, 100, 30);
  cBloqueVerde* bloqueVerde = new cBloqueVerde (101, 0, 150, 30);
  cBloqueAmarillo* bloqueAmarillo = new cBloqueAmarillo (151, 0, 200, 30);

  for (int i = 0; i <= 10; i++) { bloques[i] = new cBloque(); }

  bloques[0] = new cBloqueRojo(0, 0, 50, 30);
  bloques[0]->pintarBloqueRojo();

  getch();
  delay (0);
  closegraph();

  //FINAL DEL PROGRAMA//
  system("pause");
  return 0;
}
