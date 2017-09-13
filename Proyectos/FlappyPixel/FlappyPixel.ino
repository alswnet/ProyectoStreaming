#include "Cuadrito.h"
#include <Wire.h>
#include <SPI.h>
#include <SFE_MicroOLED.h>

#define DC_JUMPER 1
#define PIN_RESET 12

MicroOLED Pantalla(PIN_RESET, DC_JUMPER);
Cuadrito Flappy(Pantalla.getLCDWidth());
int Botton = 4;
float Tiempo;

void setup() {
  Serial.begin(115200);
  Pantalla.begin();
  Pantalla.clear(PAGE);
  Pantalla.display();
  Flappy.begin(10, 10);

  pinMode(Botton, INPUT);

  // Global variables to help draw the clock face:
  int MIDDLE_Y = Pantalla.getLCDHeight() ;
  int MIDDLE_X = Pantalla.getLCDWidth() ;
  Serial.println(MIDDLE_Y);
  Tiempo = millis();
}

void loop() {
  if (digitalRead(Botton) == 0) {
    delay(100);
    Serial.println("UP");
    Flappy.Up();
  }
  if (millis() - Tiempo > 500) {
    Tiempo = millis();
    Flappy.Actualizar();
    Flappy.Mostrar(Pantalla);
    Pantalla.display();
  }
}
