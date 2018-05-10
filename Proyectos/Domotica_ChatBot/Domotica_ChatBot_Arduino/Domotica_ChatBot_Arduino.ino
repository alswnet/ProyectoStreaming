#include <EEPROM.h>

int Botones[] = {12, 11, 10};
int Rele[] = {4, 5, 6};
int EstadoRele[] = {0, 0, 0};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(Botones[i], INPUT_PULLUP);
    pinMode(Rele[i], OUTPUT);
    if (EEPROM.read(i) > 0) {
      EstadoRele[i] = 1;
    }
    else {
      EstadoRele[i] = 0;
    }
    digitalWrite(i, EstadoRele[i]);
  }

}
/*
   a - Encender Foco 1
   b - Apagar el Foco 1
   c - Encender Foco 2
   d - Apagar el Foco 2
   e - Encender Foco 3
   f - Apagar el Foco 3
*/
void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    switch (Letra) {
      case 'a':
        digitalWrite(Rele[0], 1);
        break;
      case 'b':
        digitalWrite(Rele[0], 0);
        break;
      case 'c':
        digitalWrite(Rele[1], 1);
        break;
      case 'd':
        digitalWrite(Rele[1], 0);
        break;
      case 'e':
        digitalWrite(Rele[2], 1);
        break;
      case 'f':
        digitalWrite(Rele[2], 0);
        break;
    }
  }

  for (int i = 0; i < 3; i++) {
    if (digitalRead(Botones[i]) == 0) {
      if (EstadoRele[i] == 0)
        EstadoRele[i] == 1;
      else
        EstadoRele[i] == 0;
      digitalWrite(i, EstadoRele[i]);
    }
  }

  for (int i = 0; i < 3; i++) {
    GuardadEstado(i, EstadoRele[i]);
  }
}
void GuardadEstado(int i, int estado) {
  EEPROM.write(i, estado);
}
