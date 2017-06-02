//Consulta Ejemplo
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>

//Inforacion de la RED
const char* ssid     = "TURBONETT_ALSW"; //Nombre de la red
const char* password = "2526-4897"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAECXxz5YWAnNmWkTkcuNa0KCLfr5ZCcLZBTxSz4t1hxNDHbucBXn7Y1MPml2FBkDZBEfebZCjROumgYNkeTUqrs9dqt8yehlvY4Tow1zIlQ758VLLIrw6ZBD3ngpZAljGZAWEmnzJ3XBRlbw9yzSbAS5MXhItcSeWSkiOOOCrSK";//Contraseña del greap API de facebook, cuidado caduze
char* IDStriming = "1346814398707039";//ID del video o foto
WiFiClientSecure client;//Cliente para contartar a facebook

//Pines del LED RGB
int LedRed = 13;
int LedBlue = 14;
int LedGreen = 12;

//Respuesta con Facebook
String Data;

void setup() {
  //Inicializa la comunicacion Serial
  Serial.begin(115200);
  delay(100);

  //Activa los pines de los y los apaga
  pinMode(LedRed, OUTPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  digitalWrite(LedRed, 0);
  digitalWrite(LedGreen, 0);
  digitalWrite(LedBlue, 0);

  Serial.print("connecting: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  //Intenta conectar al router, multiples veses:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //Espera 1 segundo para intenar de nuevo
    delay(1000);
  }

  Serial.print("conected to ");
  Serial.println(ssid);

  //Preparar la consulta para facebook
  Data = "GET https://graph.facebook.com/v2.9/";
  Data.concat(IDStriming);
  Data.concat("?fields=comments.limit(4).order(reverse_chronological)&access_token=");
  Data.concat(AccessToken);
  Data.concat(" HTTP/1.0");
}

void loop() {
  //Consulta cada 3 segundos
  //Comandos validos
  //#RED #BLUE #GREEN
  CheckFB();
  delay(1000);
}

//Consulta a Facebook y verifica cual color es el ultimo
//En base a la posicion del Text
void CheckFB() {

  //Inicalizar las varialbes
  int ValueRed = -1;
  int ValueBlue = -1;
  int ValueGreen = -1;
  int ValueYellow = -1;

  //Value Inicial
  Serial.println("\nEmpezando coneccion con el servidor...");
  if (!client.connect(server, 443))
    Serial.println("Conexion Fallida");
  else {
    Serial.println("Conexion Exitosa");

    //Hace la consulta HTTPS a facebook
    client.println(Data);
    client.println("Host: www.graph.facebook.com");
    client.println("Connection: close");
    client.println();

    //Esperando que nos envien todo los Datas el servidor
    Serial.print("Esperando Respuesta ");
    while (!client.available()) {
      delay(500); //
      Serial.print(".");
    }

    //Si nos mandaron Datas lo guandamos en Text
    String Text = "*";
    while (client.available()) {
      Text = client.readString();
    }

    //Nos Desconectamos del servidor
    if (!client.connected()) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }

    //Muestra Datas y el Text que recibimos
    Serial.println(Text);
    Serial.print("Cantidad de Text ");
    Serial.println(Text.length());

    //Obtiene las primera pocion que aparece los comandos
    //Si no lo encuentra devolvera -1
    ValueBlue = Text.indexOf("#BLUE");
    ValueRed = Text.indexOf("#RED");
    ValueGreen = Text.indexOf("#GREEN");
    ValueYellow = Text.indexOf("#YELLOW");

    //Imprime em Serial en que Data esta
    Serial.print("Rojo: ");
    Serial.print(ValueRed);
    Serial.print(" Azul: ");
    Serial.print(ValueBlue);
    Serial.print(" Verde: ");
    Serial.print(ValueGreen);
    Serial.print(" Amaillo: ");
    Serial.println(ValueYellow);
    //Busca cual es Value mas pequeño entre todos descartando uno por uno
    if (LowOf(ValueYellow, ValueRed) && LowOf(ValueYellow, ValueBlue) && LowOf(ValueYellow, ValueGreen)) {
      digitalWrite(LedRed,  1);
      digitalWrite(LedBlue, 0);
      digitalWrite(LedGreen, 1);
    }
    if (LowOf(ValueRed, ValueBlue) && LowOf(ValueRed, ValueGreen)) {
      digitalWrite(LedRed,  1);
      digitalWrite(LedBlue, 0);
      digitalWrite(LedGreen, 0);
    }
    else if (LowOf(ValueBlue, ValueGreen)) {
      digitalWrite(LedRed,  0);
      digitalWrite(LedBlue, 1);
      digitalWrite(LedGreen, 0);
    }
    else if (ValueGreen != -1) {
      digitalWrite(LedRed,  0);
      digitalWrite(LedBlue, 0);
      digitalWrite(LedGreen, 1);
    }
  }
}

//Busca si el Value1 es LowOf que el Value2 o
//no fue encontrado que el Value sera -1
bool LowOf(int Value1, int Value2) {

  if ((Value1 == -1 && Value2 == -1) || Value1 == -1) {
    return false;
  }
  else if (Value2 == -1 || Value1 < Value2) {
    return true;
  }
  return false;
}
