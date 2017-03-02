#include <SPI.h>
#include <SD.h>
#include <string.h>

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

void setup() {
  Serial.begin(9600);
  if (!SD.begin(SDSelector)) {
    Serial.println("Error SD");
    return;
  }
  Serial.println("SD funciona");
  CantidadPreguntas = ContrarPreguntas();
  Serial.println();
  Serial.println();
}

void loop() {
  IDPregunta = random(CantidadPreguntas);
  BuscarPregunta(IDPregunta);
  MostarSerial();
  delay(1000);
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


