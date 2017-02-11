#include <SoftwareSerial.h> // Include software serial library, ESP8266 library dependency
#include <SparkFunESP8266WiFi.h> // Include the ESP8266 AT library
#include "FPS_GT511C3.h"

const char MiRed[] = "ALSW2";
const char MiContra[] = "2124-1324";

FPS_GT511C3 Huella(6, 7);

void setup() {
  Serial.begin(9600);
  ActivarWifi();
  ActivarHuela();
  esp8266.listen();
}

void loop() {
  //EnviarWifi();
  BuscarHuella();
}

void ActivarHuela() {
  Huella.Open();
  Huella.SetLED(true);
}

void ActivarWifi() {
  while (esp8266.begin() != true) {
    Serial.println("Error connecting to ESP8266.");
    delay(1000);
  }
  if (esp8266.status() <= 0) {
    while (esp8266.connect(MiRed, MiContra) < 0) {
      Serial.write(".");
      delay(1000);
    }
  }
  Serial.print("Mi ip es ");
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
      EnviarWifi(0);
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
  int retVal = client.connect("192.168.43.97", 80); // Connect to sparkfun (HTTP port)
  if (retVal > 0) {
    Serial.println("Conecxion correcta!");
    client.print("GET /Prueva/dato.php?ID=");//?ID=");
    client.print(ID);
    client.print(" HTTP/1.1\nHost: 192.168.43.97\nConnection: close\n\n");

    while (client.available()) // While there's data available
      Serial.write(client.read()); // Read it and print to serial

    client.stop();
  }
  delay(1000);
}
