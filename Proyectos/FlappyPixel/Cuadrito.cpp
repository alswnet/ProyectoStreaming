#include "Cuadrito.h"

Cuadrito::Cuadrito(int h) {
  PX = 100;
  PY = 100;
  H = h;
}

void Cuadrito::begin(int x, int y) {
  PX = x;
  PY = y;
}

void Cuadrito::begin(int x, int y, int g) {
  begin(x, y);
  G = g;
}

void Cuadrito::Actualizar() {
  V -= G;

  if (V > VMax) {
    V = VMax;
  }
  else if ( V < -VMax) {
    V = -VMax;
  }

  if (PYs != PY) {
    PYs = PY;
  }
  PY -= V;

  if (PY < 0) {
    PY = 0;
  }
  else if (PY > H) {
    PY = H;
  }
}

void Cuadrito::Up() {
  V += S;
}

void Cuadrito::Mostrar(MicroOLED Pantalla) {
  //Pantalla.pixel(PX, PY);
  Pantalla.circleFill(PX, PYs, PG, BLACK, NORM);
  Pantalla.circleFill(PX, PY, PG, WHITE, NORM);
  Pantalla.circleFill(PX, PY, PG - 1, BLACK, NORM);
  Serial.print("PY ");
  Serial.print(PY);
  Serial.print(" V ");
  Serial.println(V);
}
