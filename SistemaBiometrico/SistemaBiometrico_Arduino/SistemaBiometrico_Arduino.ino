#include <LiquidCrystal.h>
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

LiquidCrystal Pantalla(12, 11, 5, 4, 3, 2);
FPS_GT511C3 Huella(6, 7);

int PinBuzzer = 10;

String Nombre[10] = {"Hector", "Carlos"};

void setup() {
  pinMode(PinBuzzer, OUTPUT);
  Pantalla.begin(16, 2);
  Pantalla.clear();
  Pantalla.print("Bienvenido");
  Pantalla.setCursor(0, 1);
  Pantalla.print("Ponga el Dedo");
  tone(PinBuzzer, 1000);
  delay(500);
  noTone(PinBuzzer);
  Huella.Open();
  Huella.SetLED(true);
}

void loop() {

  if (Huella.IsPressFinger()) {
    Huella.CaptureFinger(false);
    int ID =  Huella.Identify1_N();
    if (ID < 200) {
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.print("Hola");
      Pantalla.print(Nombre[ID]);
    }
    else {
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.print("No te cososco");
    }
  }
}
