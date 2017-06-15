#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal Pantalla(19, 18, 17, 16, 15, 14);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 4, 10, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 7, 6}; //connect to the column pinouts of the keypad

Keypad Teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char Llave[3] = {'7', '6', '5'};
char Clave[3] = {'0', '0', '0'};

int Contador = 0;

void setup() {

  Pantalla.begin(16, 2);
  Pantalla.clear();
  Pantalla.setCursor(0, 0);
  Pantalla.print("Iniciando");

  Serial.begin(9600);

}

void loop() {
  char Tecla = Teclado.getKey();

  if (Tecla && Tecla >= '0' && Tecla <= '9') {
    Serial.println(Tecla);
    Pantalla.setCursor(Contador, 1);
    Pantalla.print(Tecla);
    Clave[Contador] = Tecla;
    Contador++;
    if (Contador > 2) {
      boolean Activo = true;
      for (int i = 0; i < 3; i++) {
        if (Llave[i] != Clave[i]) {
          Activo = false;
        }
      }
      if (Activo) {
        Pantalla.clear();
        Pantalla.setCursor(0, 0);
        Pantalla.print("Correcto");
      }
      else {
        Pantalla.clear();
        Pantalla.setCursor(0, 0);
        Pantalla.print("Incorrecto");
      }
      Contador  = 0;
    }
  }
}
