#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

#define LCD_CS A3 // Chip Select - Pin analogico 3
#define LCD_CD A2 // Command/Data - Pin Analogico 2
#define LCD_WR A1 // LCD Write - Pin Analogico 1
#define LCD_RD A0 // LCD Read - Pin Analogico 0
#define LCD_RESET A4  // LCD Reset - Pin Analogico 4

#define  BLACK   0x0000  // Definimos los colores para poder referirnos a ellos con su nombre                  
#define RED     0xF800  // en lugar de usar el código hexadecimal de cada uno. 
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define BLUE    0x001F
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define MAGENTA 0xF81F

short TS_MINX = 150; // Coordenadas del panel tactil para delimitar
short TS_MINY = 120; // el tamaño de la zona donde podemos presionar
short TS_MAXX = 850; // y que coincida con el tamaño del LCD
short TS_MAXY = 891;


// Pines necesarios para los 4 pines del panel tactil
#define YP A1 // Pin analogico A1 para ADC
#define XM A2 // Pin analogico A2 para ADC
#define YM 7
#define XP 6

TouchScreen Tactil = TouchScreen(XP, YP, XM, YM, 364);

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia del LCD


const int SDSelector = 10;
File Archivo;
int CantidadPreguntas = 0;

String Pregunta;
String Opciones[4];
String Opcion0;
String Opcion1;
String Opcion2;
String Opcion3;
int Respueta;
int IDPregunta;

float TiempoPasado;
static int AnchoP = tft.width();
static int AltoP = tft.height();


void setup() {
  Serial.begin(9600);
  if (!SD.begin(SDSelector)) {
    Serial.println("Error SD");
    return;
  }
  Serial.println("SD funciona");
  CantidadPreguntas = ContrarPreguntas();
  tft.begin(0x9325);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  Serial.println();
  Serial.println();
  TiempoPasado = millis();
}

void loop() {
  LecturaPanel();
  if (millis() - TiempoPasado > 5000) {
    TiempoPasado = millis();
    IDPregunta = random(CantidadPreguntas);
    BuscarPregunta(IDPregunta);
    MostarSerial();
    Dibujar();
  }
  //delay(5000);
}

void Dibujar() {
  tft.fillScreen(BLACK);
  MostarTexto(0, 0, AltoP, AnchoP / 3, Pregunta, 1);

  MostarTexto(0, AnchoP / 3, AltoP / 2, AnchoP / 3, Opcion0, 0);
  MostarTexto(0, AnchoP / 3 * 2, AltoP / 2, AnchoP / 3, Opcion1, 0);
  MostarTexto(AltoP / 2, AnchoP / 3, AltoP / 2, AnchoP / 3, Opcion2, 0);
  MostarTexto(AltoP / 2, AnchoP / 3 * 2, AltoP / 2, AnchoP / 3, Opcion3, 0);
}

void MostarTexto(int PX, int PY, int ancho, int Alto, String texto, int Op) {
  if (Op == 0) {
    tft.fillRect(PX + 10, PY + 10, ancho - 20, Alto - 20, BLUE);
  }
  else {
    tft.fillRect(PX + 10, PY + 10, ancho - 20, Alto - 20, YELLOW);
  }
  tft.drawRect(PX, PY, ancho, Alto, RED);
  tft.setCursor(PX + 30, PY + 30);
  if ( texto.length() > 10) {
    tft.setTextSize(2);
  }
  else {
    tft.setTextSize(3);
  }
  tft.setTextColor(BLACK);
  tft.println(texto);

}
void MostarSerial() {
  Serial.print("ID ");
  Serial.print(IDPregunta);
  Serial.print(" - ");
  Serial.println(Pregunta);
  Serial.print("Respuesta: ");
  Serial.println(Respueta);
  Serial.print("Op0: ");
  Serial.print(Opcion0);
  Serial.print(" Op1: ");
  Serial.print(Opcion1);
  Serial.print(" Op2: ");
  Serial.print(Opcion2);
  Serial.print(" Op3: ");
  Serial.print(Opcion3);
  Serial.println();
  Serial.println();
}
void BuscarPregunta(int ID) {
  Pregunta = "";
  Opcion0 = "";
  Opcion1 = "";
  Opcion2 = "";
  Opcion3 = "";
  int IDBusqueda = ID;
  int Encontrado = 0;
  Archivo = SD.open("Pregun.txt");
  int Encontrando = 0;
  if (Archivo) {
    while (Archivo.available()) {
      char Letra = Archivo.read();
      if (Letra == '\n') {
        if (IDBusqueda < 0) {
          return;
        }
        IDBusqueda--;
      }
      else if (IDBusqueda == 0) {
        if (Letra == '\t') {
          Encontrado++;
        }
        else {
          switch (Encontrado) {
            case 0:
              Pregunta = Pregunta + String(Letra);
              break;
            case 1:
              Respueta = int(Letra) - '0';
              break;
            case 2:
              Opcion0 = Opcion0 + String(Letra);
              break;
            case 3:
              Opcion1 = Opcion1 + String(Letra);
              break;
            case 4:
              Opcion2 = Opcion2 + String(Letra);
              break;
            case 5:
              Opcion3 = Opcion3 + String(Letra);
              break;
          }
        }
      }
    }
  }
  Archivo.close();
}

int ContrarPreguntas() {
  int Preguntas = 0;
  Archivo = SD.open("Pregun.txt");
  if (Archivo) {
    while (Archivo.available()) {
      char Letra = Archivo.read();
      if (Letra == '\n') {
        Preguntas++;
      }
    }
  }
  Serial.print("Preguntas: ");
  Serial.println(Preguntas);
  Archivo.close();
  return Preguntas;
}


void LecturaPanel() {
  TSPoint p = Tactil.getPoint(); // Realizamos lectura de las coordenadas

  pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
  pinMode(YP, OUTPUT); // por lo que es necesario declararlos como salida justo
  // despues de realizar una lectura de coordenadas.

  // Mapeamos los valores analogicos leidos del panel tactil (0-1023)
  // y los convertimos en valor correspondiente a la medida del LCD 320x240
  int   X = map(p.x, TS_MAXX, TS_MINX,  tft.width(), 0);
  int  Y = map(p.y, TS_MAXY, TS_MINY,  tft.height(), 0);
  int  Z = p.z;
  if (Z > 0 && Z < 1000) {
    Serial.print("X ");
    Serial.print(X);
    Serial.print( " Y ");
    Serial.print(Y);
    Serial.print(" Z ");
    Serial.println(Z);
  }

}
