//Librerias del sensor
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include <LiquidCrystal.h>

//Pin del Rele de la puerta
int PinRele = 13;
boolean EstadoRele = false;
//Sensor de Huella
FPS_GT511C3 Huella(6, 7);

//Pantalalas LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciado");
  Huella.Open();
  Huella.SetLED(true);
  pinMode(PinRele, OUTPUT);
  digitalWrite(PinRele, EstadoRele);
  Serial.println("Hola inicie");
}

void loop() {
  if (Huella.IsPressFinger()) {
    Huella.CaptureFinger(false);
    int IdPresona = Huella.Identify1_N();
    if (IdPresona == 2) {//Cambia el numero al ID 
      EstadoRele = !EstadoRele;
      digitalWrite(PinRele, EstadoRele);
      if (EstadoRele) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hola Rojo 1");
        Serial.println("Hola Rojo 1");
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Adios Rojo 1");
        Serial.println("Adions Rojo 1");
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A Usted no lo conosco");
      Serial.println("A Usted no lo conosco");
    }
  }
}
