#define VELOCIDAD 1700

#include <Servo.h>

#include <IRremote.h>

Servo servomotor;
Servo servomotor2;

int ReceptorIR = 11;

int derecha = 8;

int izquierda = 9;

int posicion = 6;

int posicion2 = 7;

int steps = 13;

int direccion = 9;

int reset = 10;

int pasos = 2000;

IRrecv irrecv(ReceptorIR);
decode_results results;
decode_results Codigos;

void setup()

{

  Serial.begin(9600);

  irrecv.enableIRIn();

  pinMode(derecha, OUTPUT);

  pinMode(izquierda, OUTPUT);

  pinMode(steps, OUTPUT);

  pinMode(direccion, OUTPUT);

  pinMode(reset, OUTPUT);

  servomotor.attach(6); //Asociamos el servomotor al pin 3 del Arduino

  posicion = 0; //Ponemos el servo a 90º al iniciar el programa

}


void loop() // Cuerpo del programa

{

  if (irrecv.decode(&Codigos))

  {

    switch (Codigos.value)

    {

      case 0x10EF10EF:

        posicion = 90;
        Serial.print("Posicion de servomotor angular = ");
        Serial.print(posicion);
        Serial.println("");
        break;

      case 0x10EF807F
          :
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
 
          for (int i = 0; i < pasos; i++)     //Equivale al numero de vueltas (200 es 360º grados) o micropasos
          {
            digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
            digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
            delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

          }

          digitalWrite(reset, LOW);   //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
          delay(100);
          digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
          digitalWrite(direccion, LOW);

          for (int i = 0; i < pasos; i++)     //Equivale al numero de vueltas (200 es 360º grados) o micropasos
          {

            digitalWrite(steps, LOW);   // LOW to HIGH hace que el motor avance ya que da la orden
            digitalWrite(steps, HIGH);    // al A4988 de avanzar una vez por cada pulso de energia.
            delayMicroseconds(VELOCIDAD);         // Regula la velocidad, cuanto mas bajo mas velocidad.
          }

          break;

        case 0x10EFF807:

          digitalWrite(derecha, HIGH);
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
          Serial.print("Giro hacia izquierda");
          Serial.println("");
          break;

        case 0x10EF58A7
            :

          digitalWrite(izquierda, LOW);
          Serial.print("Giro hacia izquierda detenido");
          Serial.println("");
          break;

        }
        servomotor.write(posicion);

        irrecv.resume();

    }

  }
