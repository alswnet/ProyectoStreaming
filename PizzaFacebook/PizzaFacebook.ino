//Consulta a realiza
// ID/feed - para optener la ultima foto en donde buscaremos las ordenes


#include <WiFiClientSecure.h>

//Inforacion de la RED
const char* ssid     = "TURBONETT_ALSW"; //Nombre de la red
const char* password = "2526-4897"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAMnggRP8SfLHZAXO1UbKn7fH2Pnrh4MR7xJNM0roeXwZC4PlSUlyk8A8qho3NzcoBC6HCrmD7sS7GOim8COe3O7WLmCY08ZBGvmbcZCybx4jnpLexZC9LBinimuKL4znxPsUux065GWZAGlEesHk1XiPJgeiypnliZBOZBZAh12U6DmpfciBAwveOJKRkqPvk1QZDZD";
String IDImagen = "xxx";//ID del video o foto
String Fanpage = "252051211953535";
String IndicadorFacebook = "#PizzaTime";
WiFiClientSecure client;//Cliente para contartar a facebook

//Pin del LED
int PinLed = 5;

//Respuesta con Facebook
String Data;

void setup() {
  pinMode(PinLed, OUTPUT);

  Serial.begin(115200);

  Serial.print("Contacando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(PinLed, 0);
    delay(500);
    digitalWrite(PinLed, 1);
    delay(500);
  }

  Serial.println("Conectado");

  PreguntaInicial();

}

void loop() {

}

void PreguntaInicial() {

  String Pregunta;

  Pregunta = "GET https://graph.facebook.com/v2.10/";
  Pregunta.concat(Fanpage);
  Pregunta.concat("/feed?access_token=");
  Pregunta.concat(AccessToken);
  Pregunta.concat(" HTTP/1.0");

  Serial.print("Pregunta ");
  Serial.println(Pregunta);

  String Respuesta = PreguntarFacebook(Pregunta);

  Serial.print("Respuesta : ");
  Serial.println(Respuesta);

  int IDIndicadorFB =  BuscarTexto(Respuesta, IndicadorFacebook);
  int IDPostInicio = BuscarTexto(Respuesta, "\"id\":\"", IDIndicadorFB) + 6;
  int IDPostFinal = BuscarTexto(Respuesta, "_", IDPostInicio+1);
  String IDPost = Respuesta.substring(IDPostInicio, IDPostFinal);
Serial.print("IDIndicadorFB ");
Serial.println(IDIndicadorFB);

Serial.print("IDPostInicio ");
Serial.println(IDPostInicio);

Serial.print("IDPostFinal ");
Serial.println(IDPostFinal);

Serial.print("ID Post ");
Serial.println(IDPost);
}

String PreguntarFacebook(String Consulta) {
  String Texto = "Error";

  Serial.println("\nEmpezando coneccion con el servidor...");

  if (!client.connect(server, 443))
    Serial.println("Conexion Fallida");
  else {
    Serial.println("Conexion Exitosa");

    client.println(Consulta);
    client.println("Host: www.graph.facebook.com");
    client.println("Connection: close");
    client.println();

    Serial.print("Esperando Respuesta ");
    while (!client.available()) {
      delay(500);
      Serial.print(".");
    }

    while (client.available()) {
      Texto = client.readString();
    }

    if (!client.connected()) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }
  }
  return Texto;
}

int BuscarTexto(String Consulta, String Texto) {
  int Posicion = Consulta.indexOf(Texto);
  return Posicion;
}

int BuscarTexto(String Consulta, String Texto, int Inicio) {
  int Posicion = Consulta.indexOf(Texto, Inicio);
  return Posicion;
}
