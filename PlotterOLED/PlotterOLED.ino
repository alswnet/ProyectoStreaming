#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define DC_JUMPER 1 //valor al cual se soldo el jumper DC
#define PIN_RESET 12  // Conectar RST al GPIO 12

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaración

int x0 = 0;
int y = 0;
int x1 = 0;
int ye = 0;

void setup() {
  oled.begin();    // Inicializa la OLED
  oled.clear(ALL); // Borra la memoria interna de la OLED
  oled.display();  //Mostrar lo que hay en el buffer
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Borra lo que hay en el buffer
  oled.line(0, LCDHEIGHT / 2, LCDWIDTH, LCDHEIGHT / 2);
}

void loop() {
  for (int i = 0; i < LCDWIDTH; i++) {
    x1 = i;
    ye = int(map(analogRead(A0), 0, 1023, 0, LCDHEIGHT));
    if (x0 != LCDWIDTH && x1 != 0) {
      oled.line(x0, y, x1, ye);
      oled.display();
    }
    x0 = x1;
    y = ye;
    delay(100);
  }
  oled.clear(PAGE);
  oled.line(0, LCDHEIGHT / 2, LCDWIDTH, LCDHEIGHT / 2);
  oled.display();
  delay(100);
}
