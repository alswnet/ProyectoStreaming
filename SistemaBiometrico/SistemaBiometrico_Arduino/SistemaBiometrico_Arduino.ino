#include <LiquidCrystal.h>
#include "FPS_GT511C3.h"
#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

const char MiRed[] = "ALSW 2.4Ghz";
const char MiContra[] = "2124-1324";

const String MiServidor = "192.168.1.108";

String http1 = "GET Prueva/dato.php?ID=";
String http2 = " HTTP/1.1\n"
               "Host: " + MiServidor + "\n"
               "Connection: close\n\n";


LiquidCrystal Pantalla(11, 12, 5, 4, 3, 2);
FPS_GT511C3 Huella(6, 7);

int PinBuzzer = 10;

String Nombre[10] = {"Hector", "Eduardo", "Stanley", "Eduardo", "Eduardo", "Eduardo"};

void setup() {
  Serial.begin(9600);
  Serial.println("Hola iniciando :)");
  pinMode(PinBuzzer, OUTPUT);
  Pantalla.begin(16, 2);
  Pantalla.clear();
  tone(PinBuzzer, 1000);
  delay(250);
  noTone(PinBuzzer);

  Huella.Open();
  Huella.listen();
  delay(100);
  Serial.println("Activando Huella");

  // Huella.UseSerialDebug = true;
  Huella.SetLED(true);
  delay(600);
  Huella.SetLED(false);
  delay(600);
  Huella.SetLED(true);
  delay(500);


  while (esp8266.begin() != true) {
    Serial.println("Error connecting to ESP8266.");
    delay(1000);
  }

  esp8266.listen();
  if (esp8266.status() <= 0) {
    while (esp8266.connect(MiRed, MiContra) < 0) {
      Serial.write(".");
      delay(1000);
    }
  }
  Serial.println("Activado Wifi");

  esp8266.listen();
  delay(100);
  Serial.print("Mi ip es ");
  Serial.println(esp8266.localIP());

}

void loop() {

  Huella.listen();
  if (Huella.IsPressFinger()) {
    Serial.println("Huella encontrada");
    Huella.CaptureFinger(false);
    int ID =  Huella.Identify1_N();
    if (ID < 200) {
      Serial.print("Hola ");
      Serial.println(Nombre[ID]);
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.print("Hola ");
      Pantalla.print(Nombre[ID]);
      MandarDatos(ID);
    }
    else {
      Serial.println("No se quien eres :p ");
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.println("No te conozco");
      Pantalla.println("Intenta otra vez");
    }
  }
}


void MandarDatos(int ID) {
  esp8266.listen();
  ESP8266Client Cliente;

  if (Cliente.connect(MiServidor, 80) <= 0) {
    Serial.println("Fallo la conexion");
    Pantalla.clear();
    Pantalla.setCursor(0, 0);
    Pantalla.print("No Servidor");
    return;
  }
  else {
    Serial.println("Servidor encontrado");
  }

  Cliente.print(http1);
  Cliente.print(ID);
  Cliente.print(http2);
  delay(100);
  while (Cliente.available()) {
    Serial.write(Cliente.read());
  }

  if (Cliente.connected())
    Cliente.stop();

}
