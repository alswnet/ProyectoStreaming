#include <Servo.h>
#include <Bridge.h>//Declaración de librerias 
#include <YunServer.h>
#include <YunClient.h>

YunServer server; //Enviara allí todas las peticiones HTTP hechas por el cliente
Servo myservo;

int var = 0; //Declaración de variables 192.168.43.27
int conver = 0;
void setup() {
  myservo.attach(9);
  Bridge.begin();//Se inicia el puente entre el linino y el atmega32U4

  server.begin();//Se inicia el servidor
  server.listenOnLocalhost();
}

void loop() {
  YunClient client = server.accept();             //se le asigna a client las peticiones URL hechas por el cliente
  if (client)                                     //se comprueba si hay cliente
  {
    String comando = client.readStringUntil('/'); //se almacena en la variable comando la palabra que va despues de http://arduino.local/arduino/
    if (comando == "led")                         //se comprueba si la petición realizada es http://arduino.local/arduino/led
    {
      var = client.parseInt();                   //se almacena el siguiente valor entero de la petición URL hecha por el cliente en cada una de las variables
      if (var >= 0 && var <= 255)               //se verifica que los valores que vienen de la URL esten entre 0 y 255
      {
        conver = map(var, 0, 255, 0, 180);
        myservo.write(conver);
        client.print(conver);                       //respuesta del servidor a la pagina con el valor de intensidad aplicado
      }
    }
    client.stop();                                //se detiene la comunicación entre el cliente y el servidor
  }
  delay(50);                                      //retardo de 50 mili segundos --  retardation the 50 mili seconds
}
