#include "FPS_GT511C3.h"
#include <SoftwareSerial.h>

int Solenoide = 12;
boolean EstadoPuesta = true;

FPS_GT511C3 Huella(6, 7);

void setup() {

  Huella.Open();
  Huella.SetLED(true);
  pinMode(Solenoide, OUTPUT);
  digitalWrite(Solenoide, EstadoPuesta);
}

void loop() {

  if (Huella.IsPressFinger()) {
    Huella.CaptureFinger(false);
    int ID = Huella.Identify1_N();
    if (ID == 3) {
      EstadoPuesta = !EstadoPuesta;
      digitalWrite(Solenoide, EstadoPuesta);
      delay(100);
    }
  }
}
