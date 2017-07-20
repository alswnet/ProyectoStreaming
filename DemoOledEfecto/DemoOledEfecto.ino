#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include <ESP8266WiFi.h>

const char* ssid = "TURBONETT_ALSW";
const char* password = "2526-4897";
WiFiServer server(80);

#define DC_JUMPER 1 //valor al cual se soldo el jumper DC
#define PIN_RESET 12  // Conectar RST al GPIO 12

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaración

void setup() {
  Serial.begin(115200);
  Serial.print("Conectado a");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi Conectado a:");
  Serial.println(ssdi);
  server.begin();
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  oled.begin();
  oled.clear(ALL);
  oled.display();
  delay(1000);
  oled.clear(PAGE);
  oled.setFontType(0);
  oled.setCursor(0, 0);
  oled.print("Loading...");
  for (int i = 0; i < 45; i++) {
    oled.rectFill(10, 10, i, 10);
    oled.display();
    delay(100);
  }
  oled.clear(PAGE);
  oled.display();
}

void loop() {
  WiFiClient client = server.available();
  if(!client)
  return;

  
}
