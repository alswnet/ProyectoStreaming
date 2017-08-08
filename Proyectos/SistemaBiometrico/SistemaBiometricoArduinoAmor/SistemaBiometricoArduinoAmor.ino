//Librerias del Wifi, Sensor de huella y comunicasion serial UARL
#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include <LiquidCrystal.h>
#include "FPS_GT511C3.h"

//Mombre de la red, contraseña y nombre del servidor
const char MiRed[] = "ALSW 2.4Ghz";
const char MiContra[] = "2124-1324";
const char Servidor[] = "192.168.1.108";

//Variables globales
FPS_GT511C3 Huella(6, 7);//Sensor de huellas
LiquidCrystal Pantalla(11, 12, 5, 4, 3, 2);//Pantalla LCD
int PinBuzzer = 10;//Buzzer

void setup() {
  Serial.begin(9600);
  pinMode(PinBuzzer, OUTPUT);
  ActivarLCD();
  MostrarLCD(0);
  Alerta(0);
  ActivarWifi();
  Alerta(0);
  ActivarHuela();
  Alerta(0);
  esp8266.listen();
}

void loop() {
  BuscarHuella();
}

//Funcion que Abre la comunicacion el con el sensor de huella
void ActivarHuela() {
  Huella.Open();
  Huella.SetLED(true);
}

//Activa la comunicacion con el escudo ESP8266
void ActivarWifi() {
  while (esp8266.begin() != true) {//Verifica que encuentre el escudo o espera
    Serial.println("Error con escudo to ESP8266.");
    MostrarLCD(1);
    delay(1000);
  }
  if (esp8266.status() <= 0) {//Verifica si esta conectado a red sino se conecta
    while (esp8266.connect(MiRed, MiContra) < 0) {//Intenta conectarse, sino espera y reintenta
      Serial.print(".");
      MostrarLCD(1);
      delay(1000);
    }
  }
  Serial.print("Mi ip es: ");
  Serial.println(esp8266.localIP());//Muestra la ip del arduino
}

//Activar la LCD
void ActivarLCD() {
  Pantalla.begin(16, 2);
  Pantalla.clear();
}

void BuscarHuella() {
  Huella.listen();
  if (Huella.IsPressFinger()) {
    Alerta(0);
    Huella.CaptureFinger(false);
    int id = Huella.Identify1_N();
    Alerta(0);
    Huella.SetLED(false);
    if (id < 200) {
      Serial.print("Encontrado ");
      Serial.println(id);
      delay(100);
      EnviarWifi(id);
      Huella.listen();
      delay(100);
    }
    else {
      Serial.println("No te conosco");
      MostrarLCD(7, "No te conosco");
      Alerta(1);
    }
    Huella.SetLED(true);
  }
}

void EnviarWifi(int ID) {
  esp8266.listen();
  ESP8266Client client;
  int retVal = client.connect(Servidor, 80);
  if (retVal > 0) {
    Serial.println("Conecxion correcta!");
    client.print(F("GET /Prueva/dato.php?ID="));
    client.print(ID);
    client.print(F(" HTTP/1.1\nHost: "));
    client.print(Servidor);
    client.print(F("\nConnection: close\n\n"));

    int Respuesta = BuscarInt(client, 'E');
    //char Nombre = BuscarChar(client, 'N');
    switch (Respuesta) {
      case 1:
        Serial.println("Adios :')");
        MostrarLCD(2, "Adios :')");
        Alerta(2);
        break;
      case 2:
        Serial.println("Hola Minion :D");
        MostrarLCD(2, "Hola :D");
        Alerta(3);
        break;
      default:
        Serial.println("Quien erres @_@");
        MostrarLCD(7, "No estas DB");
        Alerta(1);
        break;
    }
  }
  client.stop();
  delay(100);
}

void MostrarLCD(int Mensaje, char Extra[]) {
  MostrarLCD(Mensaje);
  Pantalla.setCursor(0, 1);
  Pantalla.print(Extra);
}

void MostrarLCD(int Mensaje) {
  Pantalla.clear();
  Pantalla.setCursor(0, 0);
  switch (Mensaje) {
    case 0:
      Pantalla.print("Iniciando");
      break;
    case 1:
      Pantalla.print("Error Wifi");
      break;
    case 2:
      Pantalla.print("Actualizado");
      break;
    default:
      Pantalla.print("Error");
      break;
  }

}

char BuscarChar(ESP8266Client client, char Buscar) {
  return "Chepecarlos";
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

void Alerta(int tono) {
  switch (tono) {
    case 0:
      tone(PinBuzzer, 1000);
      delay(250);
      break;
    case 1:
      tone(PinBuzzer, 2000);
      delay(500);
      tone(PinBuzzer, 3000);
      delay(500);
      tone(PinBuzzer, 2000);
      delay(500);
      tone(PinBuzzer, 3000);
      delay(500);
      break;
    case 2:
      tone(PinBuzzer, 500);
      delay(500);
      tone(PinBuzzer, 700);
      delay(500);
      tone(PinBuzzer, 900);
      delay(500);
      tone(PinBuzzer, 1100);
      delay(500);
      tone(PinBuzzer, 1300);
      delay(500);
      tone(PinBuzzer, 1500);
      delay(500);
      tone(PinBuzzer, 1700);
      delay(500);
      tone(PinBuzzer, 1900);
      delay(500);
      break;
    case 3:
      tone(PinBuzzer, 3000);
      delay(1000);
      tone(PinBuzzer, 1000);
      delay(250);
      tone(PinBuzzer, 3000);
      delay(1000);
      break;
  }
  noTone(PinBuzzer);
  delay(250);
}

