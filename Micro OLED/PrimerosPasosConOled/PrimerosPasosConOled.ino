#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library


#define DC_JUMPER 1 //valor al cual se soldo el jumper DC
#define PIN_RESET 12  // Conectar RST al GPIO 12

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaración
void setup() {
  oled.begin();    // Inicializa la OLED
  oled.clear(ALL); // Borra la memoria interna de la OLED
  oled.display();  //Mostrar lo que hay en el buffer
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Borra lo que hay en el buffer
}

void loop() {
  oled.pixel(LCDWIDTH/2, LCDHEIGHT/2);  //encendemos el pixel del centro
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.pixel(60, 40);  //encendemos el pixel de la coordenada (60,40)
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.line(LCDWIDTH/2, LCDHEIGHT/2, 64, 0);  //trazamos una linea diagonal 
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE);// Borra lo que hay en el buffer

  oled.rect(7, 10, 10, 20);  //trazamos un rectangulo (7, 10) es su vertice, ancho = 10 y alto = 20. V1(7,10) V2(7,30) V3(17,10) V4(17,30)
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.rectFill(7, 10, 10, 20);  //trazamos un rectangulo relleno (7, 10) es su vertice, ancho = 10 y alto = 20. V1(7,10) V2(7,30) V3(17,10) V4(17,30)
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.circle(LCDWIDTH/2, LCDHEIGHT/2, 20); //dibujamos un circulo con su centro en la coordenada (32,24) con un radio de 20 Px
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.circleFill(LCDWIDTH/2, LCDHEIGHT/2, 20); //dibujamos un circulo relleno con su centro en la coordenada (32,24) con un radio de 20 Px
  oled.display();   //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer

  oled.setFontType(0);      //tipo de fuente (0) significa el tamaño mas pequeño 5x7 pixel por caracter maximo 10 por columna 6 por fila
  oled.setCursor(0,0);      //ubicamos el cursor donde incia el texto
  oled.print("ALSW");       //escribimos texto
  oled.display();           //Mostrar lo que hay en el buffer
  delay(3000);  

  oled.setCursor(0,8);      //ubicamos el cursor donde incia el texto
  oled.print("Feliz");       //escribimos texto
  oled.display();           //Mostrar lo que hay en el buffer
  delay(3000);

  oled.setCursor(0,16);      //ubicamos el cursor donde incia el texto
  oled.print("Cumple");       //escribimos texto
  oled.display();           //Mostrar lo que hay en el buffer
  delay(3000);

  oled.setCursor(0,24);      //ubicamos el cursor donde incia el texto
  oled.print("Chepe");       //escribimos texto
  oled.display();           //Mostrar lo que hay en el buffer
  delay(3000);
  oled.clear(PAGE); // Borra lo que hay en el buffer
}
