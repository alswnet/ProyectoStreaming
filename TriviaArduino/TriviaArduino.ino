#include <SPI.h>
#include <SD.h>
#include <string.h>

const int SDSelector = 10;
File Archivo;
int CantidadPreguntas = 0;

String Pregunta;
String Opcion0;
String Opcion1;
String Opcion2;
String Opcion3;
int Respueta;

void setup() {
  Serial.begin(9600);
  if (!SD.begin(SDSelector)) {
    Serial.println("Error SD");
    return;
  }
  Serial.println("SD funciona");
  CantidadPreguntas = ContrarPreguntas();
}

void loop() {
  int IDPregunta = random(CantidadPreguntas);
  BuscarPregunta(IDPregunta);
  Serial.print("La preguntas numero ");
  Serial.println(IDPregunta);
  Serial.print("Preguntas es: ");
  Serial.println(Pregunta);
  Serial.print("Respuesta es: ");
  Serial.println(Respueta);
  Serial.println();
  delay(1000);
}

void BuscarPregunta(int ID) {
  Pregunta = " ";
  int IDBusqueda = ID;
  int Encontrado = 0;
  Archivo = SD.open("Pregun.txt");
  int Encontrando = 0;
  if (Archivo) {
    while (Archivo.available()) {
      char Letra = Archivo.read();
      if (Letra == '\n') {
        if (IDBusqueda == 0) {
          if (Letra == '\t') {
            Encontrado++;
          }
          switch (Encontrado) {
            case 0:
              Pregunta = Pregunta + String(Letra);
              break;
            case 1:
              Respueta = int(Letra) - '0';
              break;

          }


          return;
        }
        IDBusqueda--;
      }

      //Serial.print(Letra);

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


