//Para mas informacion por favor ir a alsw.net/blog
//Consulta Ejemplo
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            21
#define NUMPIXELS      16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//Inforacion de la RED
const char* ssid     = "ALSW2"; //Nombre de la red
const char* password = "7210-3607"; //Contraseña

//Inforacion de la consulta a facebook
//Para la contraseña entra a https://developers.facebook.com/tools/explorer/
const char*  server = "facebook.com";//Servidor
String AccessToken = "EAACEdEose0cBAFmelWp9GiOtNl7ai5HJQEXgKg1cLoLkN6eEoxKXgJ8ZCEl8NeXtT9omSBQGv2LeLbY1iAr8I03tip0lLDd4EPL0ErXZAQ9xBvFclE4lMN4wdZB2aKn6ggDamZCX643CWMxcHudgGqoz2YUpTTgzdASXCJZCREYtFMilQhLTPYz8OyBB1lD0ZD";
String IDStriming = "xxx";//ID del video o foto
String Fanpage = "alswnet";
WiFiClientSecure client;//Cliente para contartar a facebook

//Pines del LED RGB
int LedRed = 14;
int LedBlue = 13;
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

  //Busca el ultimo ID que fue striming
  IDStriming = BuscarUltivoContenido(Fanpage);

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
  delay(500);
}

//Consulta a Facebook y verifica cual color es el ultimo
//En base a la posicion del Text
void CheckFB() {
  String Text = ConsutaFacebook(Data);

  //Inicalizar las varialbes
  int ValueRed = -1;
  int ValueBlue = -1;
  int ValueGreen = -1;
  int ValueYellow = -1;
  int ValueError = -1;

  //Muestra Datas y el Text que recibimos
  Serial.println(Text);
  Serial.print("Cantidad de Text ");
  Serial.println(Text.length());

  //Obtiene las primera pocion que aparece los comandos
  //Si no lo encuentra devolvera -1
  ValueBlue = Text.indexOf("#AZUL");
  ValueRed = Text.indexOf("#ROJO");
  ValueGreen = Text.indexOf("#VERDE");
  ValueYellow = Text.indexOf("#AMARILLO");
  ValueError = Text.indexOf("error");

  if (ValueError > 0) {
    Serial.println("Exite un problema, por favor revisa el ID o el Token");
    Serial.print("Error Fatal ");
    Serial.println(ValueError);
    digitalWrite(LedRed,  1);
    digitalWrite(LedBlue, 0);
    digitalWrite(LedGreen, 0);
    delay(500);
    digitalWrite(LedRed,  0);
    delay(500);
    digitalWrite(LedRed, 1);
    delay(500);
    digitalWrite(LedRed, 0);
    delay(500);
    digitalWrite(LedRed, 1);
    delay(500);
    digitalWrite(LedRed, 0);
    delay(500);
    digitalWrite(LedRed, 1);
    delay(500);
    digitalWrite(LedRed, 0);
  }
  else {
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
      ColorNeo(100, 0, 100);
    }
    if (LowOf(ValueRed, ValueBlue) && LowOf(ValueRed, ValueGreen)) {
      ColorNeo(255, 0, 0);
    }
    else if (LowOf(ValueBlue, ValueGreen)) {
      ColorNeo(0, 255, 0);
    }
    else if (ValueGreen != -1) {
      ColorNeo(0, 0, 255);
    }
  }
}

String ConsutaFacebook(String URL) {
  String Text = "\"error\"";
  //Value Inicial
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

    //Esperando que nos envien todo los Datas el servidor
    Serial.print("Esperando Respuesta ");
    while (!client.available()) {
      delay(500); //
      Serial.print(".");
    }

    //Si nos mandaron Datas lo guandamos en Text
    while (client.available()) {
      Text = client.readString();
    }

    //Nos Desconectamos del servidor
    if (!client.connected()) {
      Serial.println();
      Serial.println("Desconectar del servidor");
      client.stop();
    }
  }
  return Text;
}

//Busca en la Fanpage en los ultimo post
//Que tenga el #Hastag
String BuscarUltivoContenido(String Fanpage) {
  String Busqueda = "#streaming";
  String URL  = "GET https://graph.facebook.com/v2.9/";
  String Busqueda2 = "\"id\":\"";
  URL.concat(Fanpage);
  URL.concat("/feed?limit=4&access_token=");
  URL.concat(AccessToken);
  URL.concat(" HTTP/1.0");

  String Text =  ConsutaFacebook(URL);
  Serial.print("Consulta ");
  Serial.println(Text);

  int ValueBusqueda =  Text.indexOf(Busqueda);
  ValueBusqueda = Text.indexOf(Busqueda2, ValueBusqueda);
  if (ValueBusqueda > 0) {
    int Inicio = Text.indexOf("_", ValueBusqueda);
    int Fin = Text.indexOf("\"", Inicio);
    if (Inicio > -1 || Fin > -1 ) {
      String ID = Text.substring(Inicio + 1, Fin);
      Serial.print("El ID fue: ");
      Serial.println(ID);
      return ID;
    }
  }
  return IDStriming;
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

void ColorNeo(int Rojo, int Azul, int Verde) {

  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(Rojo, Azul, Verde)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
}
