#include <Servo.h>

//Declaración de objetos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//declaracion de variables
int servomotor = 0;
int angulo = 0;
int anguloAnterior = 0;
void setup() {
  //Inicia la comunicacion serie
  Serial.begin(9600);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  //Definición de la posicion inicial de los servos
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    servomotor = Serial.parseInt();
    angulo = Serial.parseInt();
    Serial.println(servomotor);
    Serial.println(angulo);
  }
  delay(500);
  if () {
    
  }
}
