#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);

//Mensaje M1A100 Motor 1 Angulo 100

int CantidaMotor = 3;
int PinServo[3] = {9, 8, 4};
int ServoPosicion[3] = {0, 0, 0};
int ServoPosicionFutura[3] = {0, 0, 0};
int ServoMaxima[3] = {180, 180, 180};
int ServoMinima[3] = {0, 0, 0};
int Cambia = 0; //Cambiar 1 Motor, Cambiar 2 Theta, cambiar esta 0
int CambiarMotor = -1;
Servo ServoBraso[3];

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  for (int i = 0; i < CantidaMotor; i++) {
    ServoBraso[i].attach(PinServo[i]);
  }
}

void loop() {
  ActualizarSenal();
  for (int i = 0; i < CantidaMotor; i++) {
    Serial.print(" M");
    Serial.print(i);
    Serial.print("A");
    Serial.print(ServoPosicionFutura[i]);
    ServoBraso[i].write(ServoPosicionFutura[i]);
  }
  Serial.println();
}

void ActualizarSenal() {
  if (BTSerial.available()) {
    char Letra = BTSerial.read();
    if (Letra == 'm' || Letra == 'M') {
      Cambia = 1;
      CambiarMotor = 0;
    }
    else if (Letra == 'a' || Letra == 'A') {
      Cambia = 2;
      ServoPosicionFutura[CambiarMotor] = 0;
    }
    else if (Letra >= '0' && Letra <= '9') {
      int Numero = int(Letra - '0');
      if (Cambia == 2) {
        ServoPosicionFutura[CambiarMotor]  = ServoPosicionFutura[CambiarMotor] * 10 + Numero;
        ServoPosicionFutura[CambiarMotor] = constrain(ServoPosicionFutura[CambiarMotor], 0, 180);
      }
      else if (Cambia == 1) {
        CambiarMotor = CambiarMotor * 10 + Numero;
      }
    }
  }
}

