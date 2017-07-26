/*
    title: Juego de pixel bird
    Description: Consiste en Emular el famoso video juego con un ESP8266
                 y una pequeña LCD Micro Oled
    Author: Carlos Hernández
    Date: 25/07/2017
    Gmail: carlitos.hernandez203@gmail.com
    Git-Hub: Carl0sHdz
*/

#include <Wire.h>               // Incluye la libreria para comunicación I2C
#include <SPI.h>                // Incluye la libreria para comunicación I2C
#include <SFE_MicroOLED.h>      // Incluye la libreria para uso de la LCD Micro OLED

#define DC_JUMPER 1             // valor al cual se soldo el jumper DC
#define PIN_RESET 12            // Conectar RST al GPIO 12

int PixelAbajo = 0;

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaración
void setup() {
  Serial.begin(115200);
  oled.begin();    // Inicializa la OLED
  oled.clear(ALL); // Borra la memoria interna de la OLED
  oled.display();  //Mostrar lo que hay en el buffer
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Borra lo que hay en el buffer
  pinMode(4, INPUT);
}

void loop() {
  oled.pixel(10, PixelAbajo); //encendemos el pixel del centro
  oled.display();   //Mostrar lo que hay en el buffer
  oled.clear(PAGE); // Borra lo que hay en el buffer
  Serial.println(digitalRead(4));
  if (PixelAbajo > 48) {
    oled.setCursor(0, 8);     //ubicamos el cursor donde incia el texto
    oled.print("GAME OVER");       //escribimos texto
    oled.display();           //Mostrar lo que hay en el buffer
    delay(3000);
    oled.clear(PAGE);
    PixelAbajo = 0;
  }
  if (digitalRead(4) == 0) {
    if (PixelAbajo >= 0) {
      PixelAbajo = PixelAbajo - 2;;
    }
    else {
      PixelAbajo = 0;
    }
  }
  else {
    PixelAbajo++;
  }
}
