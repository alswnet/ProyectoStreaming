//Consulta a realiza
// ID/feed - para optener la ultima foto en donde buscaremos las ordenes

#include <WiFiClientSecure.h>

//Entrada
int EntradaSalsa = 36;
int EntradaQueso = 37;
int EntradaJamon = 38;
int EntradaPeperoni = 39;

//Motores
int MotorBanda  = 32;

//Pistones
int SalidaSalsa = 33;
int SalidaQueso = 34;
int SalidaJamon = 35;
int SalidaPeperoni = 25;

//
int BotonHorno = 26;
int SensorPizza = 27;
//Dos motor dos paso a paso
int SuperResistencia = 14;

//Info de la orde
String nombredeusuario;
String iddeusuario;
String Orden;
int TipoOrden;
int Tiempo = 30;

//Inforacion de la RED
const char* ssid     = "TURBONETT_ALSW"; //Nombre de la red
const char* password = "2526-4897"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char* server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAJg7AVJ0kQEIjZAt4kxS6FNfUHZCZCM2gi2mSkMsHQxVMUXG9BV9FGmMVy5ofXJ8hHZBOHyC7W9ZAwNAjIs4ipCwrLCG7pBk6MCAsySPOOeMGvwA8C5wyV1hWUwxrhgDOaBuPOH9xIHcl5l1pslJHAQWxmHHI2V0pkJE1nGyaNHHjJLLHT8UZD";
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

int Estado = 0;

void setup() {
  pinMode(PinLed, OUTPUT);

  Serial.begin(115200);

  //Entradas
  pinMode(EntradaSalsa, INPUT);
  pinMode(EntradaQueso, INPUT);
  pinMode(EntradaJamon, INPUT);
  pinMode(EntradaPeperoni, INPUT);

  //Motores
  pinMode(MotorBanda, OUTPUT);
  digitalWrite(MotorBanda, 0);

  //Pistones
  pinMode(SalidaSalsa, OUTPUT);
  pinMode(SalidaQueso, OUTPUT);
  pinMode(SalidaJamon, OUTPUT);
  pinMode(SalidaPeperoni, OUTPUT);

  pinMode( BotonHorno, INPUT );
  pinMode( SensorPizza , INPUT );
  pinMode( SuperResistencia , OUTPUT );

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

  //E0-Preguntar FB si Activar Banda
  Serial.println("E-1-Preguntado la Ultima Foto con #");
  PreguntaInicial();
}

void loop() {
  switch (Estado) {
    case 0:
      //E0-Preguntar FB si Activar Banda
      Serial.println("E0-Preguntado a FB ");
      if (buscarOrden()) {
        digitalWrite(MotorBanda, 1);
        Serial.println();
        Serial.print("Gracias por preferirornos ");
        Serial.print(nombredeusuario);
        Serial.print(" : ");
        Serial.println(iddeusuario);
        Serial.print("La orden que solisito es ");
        Serial.println(Orden);
        Serial.println("Encendiendo El hirno");
        digitalWrite(SuperResistencia, 1);
        Estado = 1;
      }
      break;
    case 1:
      //E1-Esperar Sesnsor Salsa y parar banda
      Serial.println("E1-Esperar Sesnsor Salva y para banda");
      if (digitalRead(EntradaSalsa) == 1) {
        digitalWrite(MotorBanda, 0);
        Estado = 2;
      }
      break;
    case 2:
      //E2-Depositar Salsa
      Serial.println("E2-Depositar Salsa");
      digitalWrite(SalidaSalsa, 1);
      delay(2000);//Tiempo para poner salde
      digitalWrite(SalidaSalsa, 0);
      digitalWrite(MotorBanda, 1);
      Estado = 3;
      break;
    case 3:
      //E3-Detectar Sensor de Quezo
      Serial.println("E3-Detectar Sensor de Quezo");
      if (digitalRead(EntradaQueso) == 1) {
        digitalWrite(MotorBanda, 0);
        Estado = 4;
      }
      break;
    case 4:
      //E4-Depositar Queso y Saltamos Segun TipoOrden
      Serial.println("E4-Depositar Queso");
      digitalWrite(SalidaQueso, 1);
      delay(2000);//Tiempo para poner Queso
      digitalWrite(SalidaQueso, 0);
      digitalWrite(MotorBanda, 1);
      if (TipoOrden == 2) {
        Estado = 9;
      }
      else if (TipoOrden == 1) {
        Estado = 7;
      }
      Estado = 5;
      break;
    case 5:
      //E5-Detectar Sensor Jamon
      Serial.println("E5-Detectar Sensor de Jamon");
      if (digitalRead(EntradaJamon) == 1) {
        digitalWrite(MotorBanda, 0);
        Estado = 6;
      }
      break;
    case 6:
      //E6-Depositar Jamon
      Serial.println("E6-Depositar Jamon");
      digitalWrite(SalidaJamon, 1);
      delay(2000);//Tiempo para poner Queso
      digitalWrite(SalidaJamon, 0);
      digitalWrite(MotorBanda, 1);
      Estado = 9;
      break;
    case 7:
      //E7-Detectar Sensor Peperoni
      Serial.println("E7-Detectar Sensor de Peperoni");
      if (digitalRead(EntradaPeperoni) == 1) {
        digitalWrite(MotorBanda, 0);
        Estado = 8;
      }
      break;
    case 8:
      //E8-Depositar Peperoni
      Serial.println("E8-Depositar Peperoni");
      digitalWrite(SalidaPeperoni, 1);
      delay(2000);//Tiempo para poner Queso
      digitalWrite(SalidaPeperoni, 0);
      digitalWrite(MotorBanda, 1);
      Estado = 9;
      break;
    case 9:
      if (digitalRead(BotonHorno) == 1) {
        ///
        //         ()          ()
        //
        //
        //      ()                 ()
        //       ()               ()
        //         ()            ()
        //           ()         ()
        //             ()()()()()
        //
        //Inserte su codigo para motor paso a paso
        //ACTIVAr
        //SUERTE, DIOS LO QUIERE, F ChepeCarlos
        Estado = 10;
      }
      break;
    case 10:
      ///
      //         ()          ()
      //
      //
      //      ()                 ()
      //       ()               ()
      //         ()            ()
      //           ()         ()
      //             ()()()()()
      //
      //Inserte su codigo para motor paso a paso
      //SEGIR
      //SUERTE, DIOS LO QUIERE, F ChepeCarlos
      if (digitalRead(SensorPizza) == 1) {
        ///
        //         ()          ()
        //
        //
        //      ()                 ()
        //       ()               ()
        //         ()            ()
        //           ()         ()
        //             ()()()()()
        //
        //Inserte su codigo para motor paso a paso
        //PARAR
        //SUERTE, DIOS LO QUIERE, F ChepeCarlos
        digitalWrite(MotorBanda, 0);
        Estado = 11;

      }
      break;
    case 11:
      delay(Tiempo * 6000);
      ///
      //         ()          ()
      //
      //
      //      ()                 ()
      //       ()               ()
      //         ()            ()
      //           ()         ()
      //             ()()()()()
      //
      //Inserte su codigo para motor paso a paso
      //Abir puerta
      //SUERTE, DIOS LO QUIERE, F ChepeCarlos
      digitalWrite(SuperResistencia, 0);
      Estado = 0;
      break;
    default:
      Estado = 0;
      break;
  }
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

boolean buscarOrden() {
  String Pregunta2;

  Pregunta2 = "GET https://graph.facebook.com/v2.10/";
  Pregunta2.concat(IDPost);
  Pregunta2.concat("?fields=comments.limit(4).order(reverse_chronological)&access_token=");
  Pregunta2.concat(AccessToken);
  Pregunta2.concat(" HTTP/1.0");

  Serial.print("Consulta a facebook: ");
  Serial.println(Pregunta2);
  Serial.println();

  String Respuesta2 = PreguntarFacebook(Pregunta2);
  Serial.print("Facebook Responde: ");
  Serial.println(Respuesta2);
  Serial.println();

  if (Respuesta2 != "Error") {

    //Busca Nombre de usuario
    int IDIndicadorFB =  BuscarTexto(Respuesta2, "name" );
    int IDPostInicio = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB );
    int IDPostFinal = BuscarTexto(Respuesta2, "\",", IDPostInicio);
    nombredeusuario = Respuesta2.substring(IDPostInicio + 2, IDPostFinal);

    //Busca ID
    int IDIndicadorFB2 =  BuscarTexto(Respuesta2, "id", IDPostFinal );
    int IDPostInicio2 = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB2 );
    int IDPostFinal2 = BuscarTexto(Respuesta2, "\"}", IDPostInicio2);
    iddeusuario = Respuesta2.substring(IDPostInicio2 + 2, IDPostFinal2);

    //Busca Order
    int IDIndicadorFB3 =  BuscarTexto(Respuesta2, "message", IDPostFinal );
    int IDPostInicio3 = BuscarTexto(Respuesta2, ":\"", IDIndicadorFB3 );
    int IDPostFinal3 = BuscarTexto(Respuesta2, "\",", IDPostInicio3);
    Orden = Respuesta2.substring(IDPostInicio3 + 2, IDPostFinal3);

    //Busca ID Orde
    int IDIndicadorFB4 =  BuscarTexto(Respuesta2, "_", IDPostFinal3 );
    int IDPostInicio4 = BuscarTexto(Respuesta2, "\"", IDIndicadorFB4 );
    int IDPostFinal4 = BuscarTexto(Respuesta2, "\"}", IDPostInicio4);
    String idorden = Respuesta2.substring(IDIndicadorFB4 + 1, IDPostInicio4);

    //Confirma Orde Tiene Sentido
    TipoOrden = 0;
    for (int t = 0; t < 3; t++) {
      if (Orden.indexOf(ordenes[t])  != -1) {
        TipoOrden = t;
        return true;
      }
    }
  }
  return false;
}
