#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include "FPS_GT511C3.h"

const char MiRed[] = "ALSW2";
const char MiContra[] = "2124-1324";
const char Servidor[] = "192.168.43.97";

FPS_GT511C3 Huella(6, 7);

void setup() {
  Serial.begin(9600);
  ActivarWifi();
  ActivarHuela();
  esp8266.listen();
}

void loop() {
  BuscarHuella();
}

void ActivarHuela() {
  Huella.Open();
  Huella.SetLED(true);
}

void ActivarWifi() {
  while (esp8266.begin() != true) {
    Serial.println("Error con escudo to ESP8266.");
    delay(1000);
  }
  if (esp8266.status() <= 0) {
    while (esp8266.connect(MiRed, MiContra) < 0) {
      Serial.print(".");
      delay(1000);
    }
  }
  Serial.print("Mi ip es: ");
  Serial.println(esp8266.localIP());
}

void BuscarHuella() {

  Huella.listen();
  if (Huella.IsPressFinger())
  {
    Huella.CaptureFinger(false);
    int id = Huella.Identify1_N();
    if (id < 200)
    {
      Huella.SetLED(false);
      Serial.print("Encontrado ");
      Serial.println(id);
      delay(500);
      EnviarWifi(id);
      Huella.listen();
      delay(500);
      Huella.SetLED(true);
    }
    else {
      Serial.println("No te conosco");
    }
  }
}

void EnviarWifi(int ID) {
  esp8266.listen();
  ESP8266Client client;
  int retVal = client.connect(Servidor, 80);
  if (retVal > 0) {
    Serial.println("Conecxion correcta!");
    client.print("GET /Prueva/dato.php?ID=");//?ID=");
    client.print(ID);
    client.print(" HTTP/1.1\nHost: ");
    client.print(Servidor);
    client.print("\nConnection: close\n\n");

    int V = BuscarInt(client, 'E');
    if (V == 1) {
      Serial.println("Adios");
    }
    else if (V == 2) {
      Serial.println("Hola");
    }
  }
  client.stop();
  delay(1000);
}

int BuscarInt(ESP8266Client client, char Buscar) {
  int Valor = 0;
  int Estado = 0;
  while (client.available()) {
    char Letra = client.read();
    //Serial.print(Letra);
    switch (Estado) {
      case 0:
        if (Letra == '<') {
          Estado = 1;
        }
        break;
      case 1:
        if (Buscar == Letra) {
          if (Valor == 0 ) {
            Estado = 2;
          }
          else {
            Estado = 4;
          }
        }
        break;
      case 2:
        if (Letra == '>') {
          Estado = 3;
        }
        break;
      case 3:
        if (Letra >= '0' && Letra <= '9') {
          Valor = Valor * 10 + int(Letra - '0');
        }
        else if (Letra == '<') {
          Estado = 1;
        }
        break;
      case 4:
        if (Letra == '>') {
          return Valor;
        }
        break;
    }
  }
  return -1;
}
