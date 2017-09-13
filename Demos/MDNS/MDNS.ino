//chepecarlos.local mDNS
//Programa para Windos - https://support.apple.com/kb/DL999?locale=en_US&viewlocale=es_ES
//Linux ya trae

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>

const char* ssid = "TURBONETT_ALSW";
const char* contrasena = "2526-4897";

WiFiServer MiServidor(80);

void setup() {
  //Inciando La comunicion con ESP32
  Serial.begin(115200);

  //Conectar al wifi
  WiFi.begin(ssid, contrasena);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Se conecto a ");
  Serial.print(ssid);
  Serial.print(" la ip es: ");
  Serial.println(WiFi.localIP());

  //Activar mDNS
  if (!MDNS.begin("alsw")) {
    Serial.println("Error con servidor mDNS");
    while (1) {}
  }
  Serial.println("Se activo mDNS");

  //Activar el servidor
  MiServidor.begin();
  Serial.print("Levantando el servir");

  //Activar el MDNS
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  //Crear un cliente
  WiFiClient Juan = MiServidor.available();
  if (!Juan) {
    return;
  }

  Serial.println();
  Serial.println("Encontra a juan");

  //Espera que termine de enviar los datos
  while (juan.connected() && !juan.available()) {
    delay(1);
  }

  //Sacar todo los datos de lo que envio
  String Respuesta = juan.readStringUntil('\r');

  //   GET /encender HTTP/1.0
  int DireccionInicio = Respuesta.indexOf(' ');
  int DireccionFin = Respuesta.indexOf(' ');

}
