#ifndef Cuadrito_H
#define Cuadrito_H

#include <Wire.h>
#include <SPI.h>
#include <SFE_MicroOLED.h>

class Cuadrito {
  private:
    float PX;//Posicion X
    float PY;//Posicion Y
    float PXs;
    float PYs;
    int PG = 3;
    float G = 0.10;//Gravedad
    float V = 0;//Velocidad
    float VMax = 20;
    float S = 5;
    int H;

  public:
    Cuadrito(int h);//
    void begin(int x, int y);
    void begin(int x, int y, int g);
    void Actualizar();
    void Mostrar(MicroOLED Pantalla);
    void Up();
};
#endif
