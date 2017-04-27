#include <EEPROM.h>

int direcionEEPROM = 0;
int Sensor = 2;
int Boton = 3;
int Tiempo = 3;//Segundos
float TiempoPasado = 0;
boolean Estado = false;

void setup() {
  pinMode(Boton, INPUT);
  pinMode(Sensor, INPUT);

  int Valor = EEPROM.read(direcionEEPROM);
  if (Valor == 1 ) {
    Estado = true;
  }
  else {
    Estado = false;
  }

  Serial.begin(9600);
}

void loop() {

  if (digitalRead(Boton) == 0) {
    Serial.println("Boton Precionado");
    Estado = !Estado;
    if (Estado) {
      EEPROM.write(direcionEEPROM, 1);
    }
    else {
      EEPROM.write(direcionEEPROM, 0);
    }
    TiempoPasado = millis();
    if (Estado) {
      do {
        Serial.print("..");
      } while (millis() - TiempoPasado < Tiempo  * 1000 );
      delay(500);
    }
  }

  if (Estado) {
    int ValorSensor = digitalRead(Sensor);
    Serial.println(ValorSensor);
    delay(100);
  }
}
