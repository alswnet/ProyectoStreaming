//Consulta Ejemplo
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            22
#define NUMPIXELS      40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Inforacion de la RED
const char* ssid     = "ALSW2"; //Nombre de la red
const char* password = "7210-3607"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAGLRwvtmFq89KPHkHBJwhcOtqe2L3Q3CbRqfvXhdUZCiaT7snQDdi5NZCiuZBL1N0aZAI8rKeZBcgBt5wrGIWKlnjcieKGSqaYHxRMSe8ZBsCPsFk2tah5aYKGUZBTRAeBa1HetCJBWq6pPZCgrZA8eaUZBa2JqZA40rNV7OPZAwCErDOLoGSMhZA90MZD";
char* IDStriming = "1401754659879679";//ID del video o foto

WiFiClientSecure client;//Cliente para contartar a facebook

//Pines del LED RGB
int LedRojo = 13;
int LedAzul = 14;
int LedVerde = 12;

//Respuesta con Facebook
String Dato;

void setup() {
  //Inicializa la comunicacion Serial
  Serial.begin(115200);
  delay(100);

  //Activa los pines de los y los apaga
  pinMode(LedRojo, OUTPUT);
  pinMode(LedAzul, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  digitalWrite(LedRojo, 0);
  digitalWrite(LedVerde, 0);
  digitalWrite(LedAzul, 0);

  Serial.print("Intentando Conectar a: ");
  Serial.println(ssid);
  // WiFi.begin(ssid);


  //Intenta conectar al router, multiples veses:
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print(".");
    //Espera 1 segundo para intenar de nuevo
    delay(500);
  }

  Serial.print("Conctado a ");
  Serial.println(ssid);

  pixels.begin();
  ColorNeo(100, 100, 100);

  //Preparar la consulta para facebook
  Dato = "GET https://graph.facebook.com/v2.9/";
  Dato.concat(IDStriming);
  Dato.concat("?fields=comments.limit(4).order(reverse_chronological)&access_token=");
  Dato.concat(AccessToken);
  Dato.concat(" HTTP/1.0");

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

  //Inicalizar las varialbes
  int ValorRojo = -1;
  int ValorAzul = -1;
  int ValorVerde = -1;
  int ValorAmarillo = -1;
  int ValorError = -1;


  //Muestra datos y el Texto que recibimos
  Serial.println(Texto);
  Serial.print("Cantidad de texto ");
  Serial.println(Texto.length());

  //Obtiene las primera pocion que aparece los comandos
  //Si no lo encuentra devolvera -1
  ValorAzul = Texto.indexOf("#AZUL");
  ValorRojo = Texto.indexOf("#ROJO");
  ValorVerde = Texto.indexOf("#VERDE");
  ValorAmarillo = Texto.indexOf("#AMARILLO");
  ValorError = Texto.indexOf("\"error\"");

  if (ValorError > 0 && ValorError < 700) {
    Serial.println("Exite un problema, por favor revisa el ID o el Token");
    Serial.print("Error Fatal ");
    Serial.println(ValorError);
    digitalWrite(LedRojo,  1);
    digitalWrite(LedAzul,  0);
    digitalWrite(LedVerde, 0);
    delay(500);
    digitalWrite(LedRojo,  0);
    delay(500);
    digitalWrite(LedRojo, 1);
    delay(500);
    digitalWrite(LedRojo, 0);
    delay(500);
    digitalWrite(LedRojo, 1);
    delay(500);
    digitalWrite(LedRojo, 0);
    Serial.println();
    Serial.println("Intentar de nuevo");
    Serial.println();
  }
  else {
    //Imprime em Serial en que dato esta
    Serial.print("Rojo: ");
    Serial.print(ValorRojo);
    Serial.print(" Azul: ");
    Serial.print(ValorAzul);
    Serial.print(" Verde: ");
    Serial.print(ValorVerde);
    Serial.print(" Amaillo: ");
    Serial.println(ValorAmarillo);
    //Busca cual es valor mas pequeño entre todos descartando uno por uno
    if (Menor(ValorAmarillo, ValorRojo) && Menor(ValorAmarillo, ValorAzul) && Menor(ValorAmarillo, ValorVerde)) {
      ColorNeo(100, 0, 100);
    }
    if (Menor(ValorRojo, ValorAzul) && Menor(ValorRojo, ValorVerde)) {
      ColorNeo(255, 0, 0);
    }
    else if (Menor(ValorAzul, ValorVerde)) {
      ColorNeo(0, 255, 0);
    }
    else if (ValorVerde != -1) {
      ColorNeo(0, 0, 255);
    }
  }
}

//Funcion que hace la consulta a facebook a traves de la API Greap
//Es necesario enviar la URL a consultar ella devuelve la respuesta
String ConsutaFacebook(String URL) {
  String Texto = "\"error\"";
  //Valor Inicial
  Serial.println("\nEmpezando coneccion con el servidor...");
  if (!client.connect(server, 443))
    Serial.println("Conexion Fallida");
  else {
    Serial.println("Conexion Exitosa");

    //Hace la consulta HTTPS a facebook
    client.println(URL);
    client.println("Host: www.graph.facebook.com");
    client.println("Connection: close");
    client.println();

    //Esperando que nos envien todo los datos el servidor
    Serial.print("Esperando Respuesta ");
    while (!client.available()) {
      delay(500); //
      Serial.print(".");
    }

    //Si nos mandaron datos lo guandamos en Texto
    while (client.available()) {
      Texto = client.readString();
    }

    //Nos Desconectamos del servidor
    if (!client.connected()) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }
  }
  return Texto;
}

//Busca si el Valor1 es menor que el Valor2 o
//no fue encontrado que el valor sera -1
bool Menor(int Valor1, int Valor2) {

  if ((Valor1 == -1 && Valor2 == -1) || Valor1 == -1) {
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
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}
