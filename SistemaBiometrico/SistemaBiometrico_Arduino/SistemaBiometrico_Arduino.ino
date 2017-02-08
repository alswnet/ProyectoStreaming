#include <LiquidCrystal.h>
#include "FPS_GT511C3.h"
//#include "SoftwareSerial.h"
#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

const char MiRed[] = "ALSW 2.4Ghz";
const char MiContra[] = "2124-1324";

const String MiServidor = "192.168.1.108";

String http1 = "GET Prueva/dato.php?ID=";
String http2 = " HTTP/1.1\n"
               "Host: " + MiServidor + "\n"
               "Connection: close\n\n";


LiquidCrystal Pantalla(12, 11, 5, 4, 3, 2);
FPS_GT511C3 Huella(6, 7);

int PinBuzzer = 10;

String Nombre[10] = {"Hector", "Eduardo", "Stanley"};

void setup() {
  Serial.begin(9600);
  Serial.println("Hola iniciando :)");
  pinMode(PinBuzzer, OUTPUT);
  Pantalla.begin(16, 2);
  Pantalla.clear();
  tone(PinBuzzer, 1000);
  delay(500);
  noTone(PinBuzzer);

  ActivarESP8266();
  
  Huella.Open();
  Huella.UseSerialDebug = true;
  Huella.SetLED(true);
  delay(1000);
  Huella.SetLED(false);
  delay(1000);
  Huella.SetLED(true);
  delay(500);
  delay(3000);

}

void loop() {

  if (Huella.IsPressFinger()) {
    Serial.println("Huella encontrada");
    Huella.CaptureFinger(false);
    int ID =  Huella.Identify1_N();
    if (ID < 200) {
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.print("Hola ");
      Pantalla.print(Nombre[ID]);
      MandarDatos(ID);
    }
    else {
      Pantalla.clear();
      Pantalla.setCursor(0, 0);
      Pantalla.print("No te cososco");
    }
  }
}

void ActivarESP8266() {

  while (esp8266.begin(9600, ESP8266_SOFTWARE_SERIAL) != true) {
    Serial.println("Fallo fatal revise el escudo");
    Pantalla.setCursor(0, 0);
    Pantalla.clear();
    Pantalla.print("Fallo el escudo");
    delay(1000);
  }
  Serial.println("Escudo encontrado");

  esp8266.setMode(ESP8266_MODE_STA);
  if (esp8266.status() <= 0) {
    while (esp8266.connect(MiRed, MiContra) < 0) {
      Serial.println("...");
      Pantalla.setCursor(0, 1);
      Pantalla.print("No encontada Wifi");
      delay(1000);
    }
  }
  Serial.print("Mi ip es ");
  Serial.println(esp8266.localIP());
  Pantalla.print("Bienvenido");
  Pantalla.setCursor(0, 1);
  Pantalla.print("Ponga el Dedo");
}


void MandarDatos(int ID) {
  ESP8266Client Cliente;

  if (Cliente.connect(MiServidor, 80) <= 0) {
    Serial.println("Fallo la conexion");
    Pantalla.clear();
    Pantalla.setCursor(0, 0);
    Pantalla.print("No Servidor");
    return;
  }

  Serial.println("Preparando");

  Cliente.print(http1);
  Cliente.print(ID);
  Cliente.print(http2);

  while (Cliente.available()) {
    Serial.write(Cliente.read());
  }

  if (Cliente.connected())
    Cliente.stop();

}
