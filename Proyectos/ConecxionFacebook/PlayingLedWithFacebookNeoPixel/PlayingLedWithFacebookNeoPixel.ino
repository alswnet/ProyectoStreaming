//Consulta Ejemplo
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            22
#define NUMPIXELS      300

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int Led = 5;
int CantidadConciones = 0;
int CantidadFallidas = 0;

//Inforacion de la RED
const char* ssid     = "ChepeCarlosWifi"; //Nombre de la red
const char* password = "7210-3607"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "900538806624473|34ceIHcz6e6GNlmT-rLBnvdO1Rw";
char* IDStriming = "1401754659879679";//ID del video o foto

WiFiClientSecure client;//Cliente para contartar a facebook

//Respuesta con Facebook
String Dato;

String Mensaje[9] = {
  "\"error\"",
  "#ROJO",
  "#AZUL",
  "#VERDE",
  "#AMARILLO",
  "#MORADO",
  "#CYAN",
  "#FIESTA",
  "#AURORA"
};

int CantidadMensajes = 9;

void setup() {
  //Inicializa la comunicacion Serial
  Serial.begin(115200);
  delay(100);

  pinMode(Led, OUTPUT);
  digitalWrite(Led, 1);

  Serial.print("Intentando Conectar a: ");
  Serial.println(ssid);
  // WiFi.begin(ssid);


  //Intenta conectar al router, multiples veses:
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print(".");
    digitalWrite(Led, !digitalRead(Led));
    //Espera 1 segundo para intenar de nuevo
    delay(500);
  }
  WiFi.printDiag(Serial);

  Serial.print("Conctado a ");
  Serial.println(ssid);

  pixels.begin();
  pixels.setBrightness(50);
  pixels.clear();
  ColorNeo(100, 100, 100);
  delay(1000);

  //Preparar la consulta para facebook
  Dato = "GET https://graph.facebook.com/v2.9/";
  Dato.concat(IDStriming);
  Dato.concat("?fields=comments.limit(4).order(reverse_chronological)&access_token=");
  Dato.concat(AccessToken);
  Dato.concat(" HTTP/1.0");

  Serial.print("Dato ");
  Serial.println(Dato);
}

void loop() {
  //Consulta cada 3 segundos
  //Comandos validos
  //#ROJO #AZUL #VERDE
  ConsultaFB();
  delay(500);
}

//Consulta a Facebook y verifica cual color es el ultimo
//En base a la posicion del texto
void ConsultaFB() {
  String Texto = ConsutaFacebook(Dato);

  int SelecionColor = -1;
  int SelecionValor = Texto.length();
  int SelecionActual = -1;

  Serial.println(Texto);
  Serial.print("Cantidad de texto ");
  Serial.println(Texto.length());

  for (int i = 0; i < CantidadMensajes; i++) {
    SelecionActual = Texto.indexOf(Mensaje[i]);
    if (SelecionActual != -1) {
      Serial.print("Encontrado ");
      Serial.print(Mensaje[i]);
      Serial.print(" Posicion ");
      Serial.println(SelecionActual);
      if (EsMenor(SelecionActual, SelecionValor)) {
        SelecionColor = i;
        SelecionValor = SelecionActual;
      }
    }
  }

  Serial.print("Selcionado ");
  Serial.print(SelecionColor);
  Serial.print(" - ");
  Serial.println(Mensaje[SelecionColor]);

  switch (SelecionColor) {
    case 1://Rojo
      ColorNeo(255, 0, 0);
      break;
    case 2://Azul
      ColorNeo(0, 0, 255);
      break;
    case 3://Verde
      ColorNeo(0, 255, 0);
      break;
    case 4://Amarillo
      ColorNeo(255, 255, 0);
      break;
    case 5://Morado
      ColorNeo(255, 0, 255);
      break;
    case 6://CIAN
      ColorNeo(0, 255, 255);
      break;
    case 7://Fiesta
      ColorNeo(255, 0, 0);
      break;
    case 8://AURORA
      ColorNeo(0, 0, 255);
      break;
    default:
      Serial.println("Error Fatal");
      break;
  }
}

//Funcion que hace la consulta a facebook a traves de la API Greap
//Es necesario enviar la URL a consultar ella devuelve la respuesta
String ConsutaFacebook(String URL) {
  String Texto = "\"error\"";
  //Valor Inicial
  Serial.print("\nEmpezando coneccion con el servidor...");
  Serial.print(CantidadConciones );
  Serial.print(" - ");
  Serial.println(CantidadFallidas);
  CantidadConciones ++;
  if (!client.connect(server, 443)) {
    Serial.println("Conexion Fallida");
    CantidadFallidas++;
  }
  else {
    Serial.println("Conexion Exitosa");

    //Hace la consulta HTTPS a facebook
    client.println(URL);
    client.println("Host: www.graph.facebook.com");
    client.println("Connection: close");
    client.println();

    //Esperando que nos envien todo los datos el servidor
    int t = 0;
    Serial.print("Esperando Respuesta ");
    while (!client.available() && t < 20) {
      delay(250); //
      Serial.print(".");
      digitalWrite(Led, !digitalRead(Led));
      t++;
    }

    //Si nos mandaron datos lo guandamos en Texto
    while (client.available()) {
      Texto = client.readString();
    }

    //Nos Desconectamos del servidor
    if (!client.connected() || t > 5) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }
  }
  return Texto;
}

//Busca si el Valor1 es menor que el Valor2 o
//no fue encontrado que el valor sera -1
bool EsMenor(int Valor1, int Valor2) {
  if (Valor1 == -1) {
    return false;
  }
  else if (Valor2 == -1 || Valor1 < Valor2) {
    return true;
  }
  return false;
}

void ColorNeo(int Rojo, int Azul, int Verde) {
  Serial.print("Rojo ");
  Serial.print(Rojo);
  Serial.print(" Azul ");
  Serial.print(Azul);
  Serial.print(" Verde ");
  Serial.println(Verde);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(Rojo, Azul, Verde)); // Moderately bright green color.
    delay(1);                     // one partial workaround
    portDISABLE_INTERRUPTS();     // the other workaround
    pixels.show();
    portENABLE_INTERRUPTS();
  }
}
