//Consulta Ejemplo
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>

//Inforacion de la RED
const char* ssid     = "TURBONETT_ALSW"; //Nombre de la red
const char* password = "2526-4897"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "xxx";//Contraseña del greap API de facebook, cuidado caduze
char* IDStriming = "xxx";//ID del video o foto
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
  WiFi.begin(ssid, password);

  //Intenta conectar al router, multiples veses:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //Espera 1 segundo para intenar de nuevo
    delay(1000);
  }

  Serial.print("Conctado a ");
  Serial.println(ssid);

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
  delay(1000);
}

//Consulta a Facebook y verifica cual color es el ultimo
//En base a la posicion del texto
void ConsultaFB() {

  //Inicalizar las varialbes
  int ValorRojo = -1;
  int ValorAzul = -1;
  int ValorVerde = -1;
  int ValorAmarillo = -1;
  int ValorError = -1;

  //Valor Inicial
  Serial.println("\nEmpezando coneccion con el servidor...");
  if (!client.connect(server, 443))
    Serial.println("Conexion Fallida");
  else {
    Serial.println("Conexion Exitosa");

    //Hace la consulta HTTPS a facebook
    client.println(Dato);
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
    String Texto = "*";
    while (client.available()) {
      Texto = client.readString();
    }

    //Nos Desconectamos del servidor
    if (!client.connected()) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }

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
      digitalWrite(LedAzul, 0);
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
        digitalWrite(LedRojo,  1);
        digitalWrite(LedAzul, 0);
        digitalWrite(LedVerde, 1);
      }
      if (Menor(ValorRojo, ValorAzul) && Menor(ValorRojo, ValorVerde)) {
        digitalWrite(LedRojo,  1);
        digitalWrite(LedAzul, 0);
        digitalWrite(LedVerde, 0);
      }
      else if (Menor(ValorAzul, ValorVerde)) {
        digitalWrite(LedRojo,  0);
        digitalWrite(LedAzul, 1);
        digitalWrite(LedVerde, 0);
      }
      else if (ValorVerde != -1) {
        digitalWrite(LedRojo,  0);
        digitalWrite(LedAzul, 0);
        digitalWrite(LedVerde, 1);
      }
    }
  }
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
