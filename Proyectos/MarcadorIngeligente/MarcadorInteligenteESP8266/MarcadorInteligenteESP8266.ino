
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "ALSW";
const char* password = "2526-4897";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
char IDTemporal = ' ';

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'2', '1', '3'},
  {'5', '4', '6'},
  {'8', '7', '9'},
  {'0', '*', '#'}
};

byte rowPins[ROWS] = {5, 0, 4, 13}; //conectar a los pines de las filas del keypad
byte colPins[COLS] = {15, 12, 16}; //conectar a los pines de las columnas del keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //inicializar una nueva instancia de un keypad


void setup() {
  lcd.init();//iniciar la lcd
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando programa");
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando Wifi ||");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando Wifi --");
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conectando con mqtt");
    // Attempt to connect
    if (client.connect("ALSWMarcadorInteligente")) {
      Serial.println("connected");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ingrese su");
      lcd.setCursor(0, 1);
      lcd.print("ID: ");
      lcd.print(IDTemporal );
      lcd.print(" */IN #/OUT");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fallo el Mqtt --");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void loop() {

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando Wifi ||");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando Wifi --");
    Serial.print(".");
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  char TeclaPresionada = customKeypad.getKey();
  if (TeclaPresionada >= '0' && TeclaPresionada <= '9') {
    IDTemporal  = TeclaPresionada;
  }
  lcd.setCursor(0, 0);
  lcd.print("Ingrese su");
  lcd.setCursor(0, 1);
  lcd.print("ID: ");
  lcd.print(IDTemporal );
  lcd.print(" */IN #/OUT");
  //delay(1000);
  if (IDTemporal >= '0' && IDTemporal <= '9') {
    if (TeclaPresionada == '*') {
      msg[0] = IDTemporal;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enviando mensaje");
      lcd.setCursor(0, 1);
      lcd.print("Bienvenido");
      delay(3000);
      lcd.clear();
      client.publish("ALSWEntrada", msg);
      IDTemporal = ' ';
    }
    else if (TeclaPresionada == '#') {
      msg[0] = IDTemporal;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enviando mensaje");
      lcd.setCursor(0, 1);
      lcd.print("Adios");
      delay(3000);
      lcd.clear();
      client.publish("ALSWSalida", msg);
      IDTemporal = ' ';
    }
  }
}
