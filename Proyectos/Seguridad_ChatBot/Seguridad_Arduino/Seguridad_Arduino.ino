#include <EEPROM.h>
int Sensor = A0;
int EstadoAlarma = 1;

void setup() {
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
  Leer();
  Guardad();
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'A') {
      EstadoAlarma = 0;
      Guardad();
    }
    else  if (Letra == 'E') {
      EstadoAlarma = 1;
      Guardad();
    }
  }



  if (EstadoAlarma == 1) {
    if (analogRead(Sensor) > 500) {
      Serial.println("A");
      delay(5000);
    }
  }
}

void Leer() {
  Serial.print("Estado ");
  Serial.print(EEPROM.read(0));
  EstadoAlarma = EEPROM.read(0) == 0 ? 0 : 1;
}

void Guardad() {
  EEPROM.write(0, EstadoAlarma);
}
