#include <Servo.h>

int CantidaMotor = 3;
int PinServo[3] = {2, 3, 4};
int ServoPosicion[3] = {0, 0, 0};
int ServoPosicionFutura[3] = {0, 0, 0};
int ServoMaxima[3] = {180, 180, 180};
int ServoMinima[3] = {0, 0, 0};
int Cambia = 0; //Cambiar 1 Motor, Cambiar 2 Theta, cambiar esta 0
int CambiarMotor = -1;
Servo ServoBraso[3];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < CantidaMotor; i++) {
    ServoBraso[i].attach(PinServo[i]);
  }
}

void loop() {
  ActualizarSenal();
  for (int i = 0; i < CantidaMotor; i++) {
    Serial.print(" M");
    Serial.print(i);
    Serial.print(" An ");
    Serial.print(ServoPosicionFutura[i]);
    ServoBraso[i].write(ServoPosicionFutura[i]);
  }
  Serial.println();
}

void ActualizarSenal() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'm' || Letra == 'M') {
      Cambia = 1;
      CambiarMotor = 0;
    }
    else if (Letra == 't' || Letra == 'T') {
      Cambia = 2;
      ServoPosicionFutura[CambiarMotor] = 0;
    }
    else if (Letra >= '0' && Letra <= '9') {
      int Numero = int(Letra - '0');
      if (Cambia == 2) {
        ServoPosicionFutura[CambiarMotor]  = ServoPosicionFutura[CambiarMotor] * 10 + Numero;
      }
      else if (Cambia == 1) {
        CambiarMotor = CambiarMotor * 10 + Numero;
      }
    }
  }
}

