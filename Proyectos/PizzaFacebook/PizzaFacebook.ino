//Consulta a realiza
// ID/feed - para optener la ultima foto en donde buscaremos las ordenes


#include <WiFiClientSecure.h>

//Inforacion de la RED
const char* ssid     = "TURBONETT_ALSW"; //Nombre de la red
const char* password = "2526-4897"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAG15IJnAoJ8p7avspAidPqImzriI6aSqaGZAyUn8vKfCUNMb1sWTNFqcn7k7EJeZCVj3Fwa4CVLZBQRYXeBZBCZBnxPl6RSBit4ahPEcyuCpyn2xn2PkwQromuJ8n1J2lA7ZCRBBXw8NX2ZAZBsRXiAZAaLy0VZAufzjyjUmlLWPIDDF6Ay9gkZBkUZD";
String IDImagen = "xxx";//ID del video o foto
String Fanpage = "252051211953535";
String IndicadorFacebook = "#PizzaTime";
String IDPost;
String ordenes[3] = {"#pizzajamon", "#pizzapeperonni", "#pizzaqueso"};
WiFiClientSecure client;//Cliente para contartar a facebook

//Pin del LED
int PinLed = 5;

//Respuesta con Facebook
String Data;

void setup() {
  pinMode(PinLed, OUTPUT);

  Serial.begin(115200);

  Serial.print("Contectando a ");
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
  buscarOrden();
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

  int IDIndicadorFB =  BuscarTexto(Respuesta, IndicadorFacebook );
  int IDPostInicio = BuscarTexto(Respuesta, "_", IDIndicadorFB );
  int IDPostFinal = BuscarTexto(Respuesta, "\"", IDPostInicio);
  IDPost = Respuesta.substring(IDPostInicio + 1, IDPostFinal);
  Serial.print("IDIndicadorFB ");
  Serial.println(IDIndicadorFB);

  Serial.print("IDPostInicio ");
  Serial.println(IDPostInicio);

  Serial.print("IDPostFinal ");
  Serial.println(IDPostFinal);

  Serial.print("ID Post:");
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

void buscarOrden() {
  String Pregunta2;

  Pregunta2 = "GET https://graph.facebook.com/v2.10/";
  Pregunta2.concat(IDPost);
  Pregunta2.concat("?fields=comments.limit(4).order(reverse_chronological)&access_token=");
  Pregunta2.concat(AccessToken);
  Pregunta2.concat(" HTTP/1.0");

  Serial.print("Pregunta2 ");
  Serial.println(Pregunta2);

  String Respuesta2 = PreguntarFacebook(Pregunta2);
  Serial.print("Respuesta2 ");
  Serial.println(Respuesta2);

  int IDIndicadorFB =  BuscarTexto(Respuesta2, "name" );
  int IDPostInicio = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB );
  int IDPostFinal = BuscarTexto(Respuesta2, "\",", IDPostInicio);
  String nombredeusuario = Respuesta2.substring(IDPostInicio + 2, IDPostFinal);

  Serial.print("nombredeusuario ");
  Serial.println(nombredeusuario);
  Serial.print("IDIndicadorFB ");
  Serial.println(IDIndicadorFB);
  Serial.print("IDPostInicio ");
  Serial.println(IDPostInicio);
  Serial.print("IDPostFinal ");
  Serial.println(IDPostFinal);


  int IDIndicadorFB2 =  BuscarTexto(Respuesta2, "id", IDPostFinal );
  int IDPostInicio2 = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB2 );
  int IDPostFinal2 = BuscarTexto(Respuesta2, "\"}", IDPostInicio2);
  String iddeusuario = Respuesta2.substring(IDPostInicio2 + 2, IDPostFinal2);

  Serial.print("iddeusuario ");
  Serial.println(iddeusuario);
  Serial.print("IDIndicadorFB2 ");
  Serial.println(IDIndicadorFB2);
  Serial.print("IDPostInicio2 ");
  Serial.println(IDPostInicio2);
  Serial.print("IDPostFinal2 ");
  Serial.println(IDPostFinal2);

  int IDIndicadorFB3 =  BuscarTexto(Respuesta2, "message", IDPostFinal );
  int IDPostInicio3 = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB3 );
  int IDPostFinal3 = BuscarTexto(Respuesta2, "\",", IDPostInicio3);
  String messagedeusuario = Respuesta2.substring(IDPostInicio3 + 2, IDPostFinal3);

  Serial.print("messagedeusuario ");
  Serial.println(messagedeusuario);
  Serial.print("IDIndicadorFB3 ");
  Serial.println(IDIndicadorFB3);
  Serial.print("IDPostInicio3 ");
  Serial.println(IDPostInicio3);
  Serial.print("IDPostFinal3 ");
  Serial.println(IDPostFinal3);
 boolean peticion = false;
  for (int i = 0; i < 3; i++) {
    if (messagedeusuario.indexOf(ordenes[i])  != -1) {
      peticion = true;
    }
  }
  Serial.println("peticion " );
  Serial.print(peticion);
}
