#include <EEPROM.h>

int Botones[] = {12, 11, 10};
int Rele[] = {5, 4 , 6};
int EstadoRele[] = {0, 0, 0};
int CantidaFoco = 3;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < CantidaFoco; i++) {
    pinMode(Botones[i], INPUT_PULLUP);
    pinMode(Rele[i], OUTPUT);
  }
  Leer();
  Activar();
  Serial.println();
}

void loop() {

  /*Cambia los focos dependiendo de puerto serial
    a - Encender Foco 1
    b - Apagar el Foco 1
    c - Encender Foco 2
    d - Apagar el Foco 2
    e - Encender Foco 3
    f - Apagar el Foco 3
  */
  if (Serial.available()) {
    char Letra = Serial.read();
    switch (Letra) {
      case 'a':
      case 'A':
        EstadoRele[0] = 1;
        break;
      case 'b':
      case 'B':
        EstadoRele[0] = 0;
        break;
      case 'c':
      case 'C':
        EstadoRele[1] = 1;
        break;
      case 'd':
      case 'D':
        EstadoRele[1] = 0;
        break;
      case 'e':
      case 'E':
        EstadoRele[2] = 1;
        break;
      case 'f':
      case 'F':
        EstadoRele[2] = 0;
        break;
    }
    Guardar();
    Activar();
  }

  //Cambia el foco dependiendo de los botones
  for (int i = 0; i < CantidaFoco; i++) {
    if (digitalRead(Botones[i]) == 0) {
      EstadoRele[i] = EstadoRele[i] == 0 ?  1 : 0;
      Guardar();
      Activar();
      while (digitalRead(Botones[i]) == 0) {
        delay(50);
      };
    }
  }
  delay(100);
}

void Guardar() {
  for (int i = 0; i < CantidaFoco; i++) {
    EEPROM.write(i, EstadoRele[i]);
  }
}

void Leer() {
  for (int i = 0; i < CantidaFoco; i++) {
    Serial.print(" Foco ");
    Serial.print(i + 1);
    Serial.print(" E/");
    Serial.print(EEPROM.read(i));
    EstadoRele[i] = EEPROM.read(i) == 0 ? 0 : 1;
  }
}

void Activar() {
  for (int i = 0; i < CantidaFoco; i++) {
    digitalWrite(Rele[i], EstadoRele[i]);
  }
}
