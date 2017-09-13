//Librerias
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include <Keypad.h>

//Informacion de la red
const char MiRed[] = "TURBONETT_ALSW";
const char MiContra[] = "2526-4897";

//Nombre o IP del servidor
const String MiServidor = "alsw.net";

//Consultas al servidor
String http1 = "GET http://alsw.net/minion/dato.php?ID=";
String http2 = " HTTP/1.1\nHost: " + MiServidor + "\nConnection: close\n\n";

//Pines de la Pantalla
LiquidCrystal Pantalla(19, 18, 17, 16, 15, 14);

//Teclado Numerico
const byte Fila = 4; //four rows
const byte Columna = 3; //three columns
char Teclas[Fila][Columna] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte PinFila[Fila] = {5, 4, 10, 2}; //connect to the row pinouts of the keypad
byte PinColumna[Columna] = {11, 7, 6}; //connect to the column pinouts of the keypad
Keypad Teclado = Keypad( makeKeymap(Teclas), PinFila, PinColumna, Fila, Columna);

//Pin Buzzer o bocina
int PinBuzzer = 12;

int IDMinion = -1;

void setup() {
  Serial.begin(9600);
  Serial.println("Hola iniciando :)");
  pinMode(PinBuzzer, OUTPUT);
  Pantalla.begin(16, 2);
  tone(PinBuzzer, 1000);
  delay(250);
  noTone(PinBuzzer);

  while (esp8266.begin() != true) {
    MensajePantalla(2);
    Serial.println("Error connecting to ESP8266.");
    tone(PinBuzzer, 1000);
    delay(500);
    noTone(PinBuzzer);
    delay(700);
  }

  Pantalla.clear();
  Pantalla.setCursor(0, 0);
  Pantalla.println("Conectando");
  if (esp8266.status() <= 0) {
    while (esp8266.connect(MiRed, MiContra) < 0) {
      Pantalla.print(".");
      tone(PinBuzzer, 500);
      delay(200);
      noTone(PinBuzzer);
      delay(200);
    }
  }

  Serial.println("Activado Wifi");

  delay(100);
  Serial.print("Mi ip es ");
  Serial.println(esp8266.localIP());

  MensajePantalla(0);
}

void loop() {
  char Tecla = Teclado.getKey();

  if (Tecla >= '0' && Tecla <= '9') {
    if (IDMinion == -1) {
      IDMinion = int(Tecla - '0');
    }
    else {
      IDMinion = IDMinion * 10 + int(Tecla - '0');
    }
    Serial.println(IDMinion);
    Pantalla.setCursor(0, 1);
    Pantalla.print(IDMinion);
  }
  else if (Tecla == '#') {
    Serial.println("Informacion del Minion ");
    Serial.println(IDMinion);
    tone(PinBuzzer, 500);
    delay(200);
    noTone(PinBuzzer);
    delay(200);
    MandarDatos(IDMinion);
    IDMinion = -1;
    MensajePantalla(0);

  }
  else if (Tecla == '*') {
    IDMinion = -1;
    Serial.println("Borrar memoria");
    MensajePantalla(0);
  }
}


void MandarDatos(int ID) {
  ESP8266Client Cliente;
  String Consulta = http1;
  Consulta.concat(ID);
  Consulta.concat(http2);
  if (Cliente.connect(MiServidor, 80) <= 0) {
    Serial.println("No se encontro Servidor");
    MensajePantalla(1);
    delay(2000);
    return;
  }
  else {
    Serial.println("Servidor encontrado");
  }
  Serial.println(Consulta);
  Cliente.print(Consulta);
  delay(100);
  String Texto;
  while (Cliente.available()) {
    //Serial.write(Cliente.read());
    Texto = Cliente.readStringUntil('%');
  }
  /*int ValorEntrada = Texto.indexOf("Entrada");
    int ValorSalida = Texto.indexOf("Salida");
    if (ValorEntrada > 0) {
    Serial.println("Entrada :)");
    }
    else if (ValorSalida > 0) {
    Serial.println("Salida :(");
    }
    else {
    Serial.println("Nada");
    }

  */
  Serial.print("Respuesta: ");
  Serial.println(Texto);
  if (Cliente.connected())
    Cliente.stop();

}

void MensajePantalla(int Mensaje) {
  Pantalla.clear();
  Pantalla.setCursor(0, 0);
  switch (Mensaje) {
    case 0:
      Pantalla.println("Ingrese IDMinion");
      break;
    case 1:
      Pantalla.print("No se encontro Servidor");
      break;
    case 2:
      Pantalla.println("Error ESP8266");
      break;
  }
}

