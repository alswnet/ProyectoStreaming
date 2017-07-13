#include <Servo.h>
#include <IRremote.h>

#define VELOCIDAD 1700

Servo servomotor;

//PinIR
int ReceptorIR = 11;
//PinMotorDC
int derecha = 53;
int izquierda = 52;
//PinMotorServo
int posicion;
int PosicionPasada;
int PinServo = 6;
//PinMotorPasoPaso
int steps = 13;
int direccion = 9;
int resets = 10;
int pasos = 2000;

IRrecv irrecv(ReceptorIR);
decode_results results;
decode_results Codigos;

void setup() {

  Serial.begin(9600);

  irrecv.enableIRIn();

  pinMode(derecha, OUTPUT);

  pinMode(izquierda, OUTPUT);

  pinMode(steps, OUTPUT);

  pinMode(direccion, OUTPUT);

  pinMode(resets, OUTPUT);

  servomotor.attach(PinServo);

  posicion = 0;
  PosicionPasada = posicion;
}


void loop() {

  if (irrecv.decode(&Codigos))  {

    switch (Codigos.value)    {

      case 0x10EF10EF:

        posicion = 90;
        Serial.print("Posicion de servomotor angular = ");
        Serial.print(posicion);
        Serial.println("");
        break;

      case 0x10EF807F:
        posicion = 0;
        Serial.print("Posicion de servomotor angular = ");
        Serial.print(posicion);
        Serial.println("");
        break;

      case 0x10EFA05F:
        posicion = posicion + 5;
        if (posicion > 180) {
          posicion = 180;
        }

        Serial.print("Posicion angular = ");
        Serial.print(posicion);
        Serial.println("");
        break;

      case 0x10EF00FF:
        posicion = posicion - 5;
        if (posicion < 0) {
          posicion = 0;
        }

        Serial.print("Posicion angular = ");
        Serial.print(posicion);
        Serial.println("");
        break;

      case 0x10EF20DF:

        for (int i = 0; i < pasos; i++)             {
          digitalWrite(steps, HIGH);
          digitalWrite(steps, LOW);
          delayMicroseconds(VELOCIDAD);

        }

        digitalWrite(resets, LOW);
        delay(100);
        digitalWrite(resets, HIGH);
        digitalWrite(direccion, LOW);

        for (int i = 0; i < pasos; i++)
        {

          digitalWrite(steps, LOW);
          digitalWrite(steps, HIGH);
          delayMicroseconds(VELOCIDAD);
        }

        break;

      case 0x10EFF807:

        digitalWrite(derecha, HIGH);
        digitalWrite(izquierda, LOW);
        Serial.print("Giro hacia derecha");
        Serial.println("");
        break;

      case 0x10EF7887:

        digitalWrite(derecha, LOW);
        Serial.print("Giro hacia derecha detenido");
        Serial.println("");

        break;

      case 0x10EFD827:

        digitalWrite(izquierda, HIGH);
        digitalWrite(derecha, HIGH);
        Serial.print("Giro hacia izquierda");
        Serial.println("");
        break;

      case 0x10EF58A7:

        digitalWrite(izquierda, LOW);
        Serial.print("Giro hacia izquierda detenido");
        Serial.println("");
        break;

    }
    if (PosicionPasada != posicion) {
      servomotor.write(posicion);
      PosicionPasada = posicion;
    }
    irrecv.resume();
  }
}
