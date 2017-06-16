#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal Pantalla(19, 18, 17, 16, 15, 14);
const byte ROWS = 4; //4 fial
const byte COLS = 3; //3 columnas
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {5, 4, 10, 2}; //pines para filas   vivo aqui le movi del pin 3 al 10 porque esta jodido el 3 en este arduino pero va en el 3 OJO
byte colPins[COLS] = {8, 7, 6}; //pines para filas

//vectores para clave
char clave[] = {'0', '0', '0', '0', '0'};
char llave[] = {'7', '0', '1', '8', '4'};
//contadores
int Contador = 0;
float TiempoPasado = 0;
char key;
int Estado = 0;
boolean Chapa;
int Error = 0;

Keypad Teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Pantalla.begin(16, 2);
  Serial.begin(9600); //initialise the serial port (9600 baud)
  Chapa = false;
  CerrarCerradura();
}

void loop() {
  key = Teclado.getKey();
  switch (Estado)
  {
    case 0:
      ImgresarContrasena();
      break;
    case 1:
      IngresarNuevaContrase();
      break;
    case 2:
      Errores();
      break;
    default:
      Estado = 0;
      break;
  }
  teclaEspecial();
}

void IngresarNuevaContrase() {
  Pantalla.setCursor(0, 0);
  Pantalla.print("nueva clave:");
  if (key != NO_KEY)
  {
    if (key >= '0' && key <= '9') {
      llave[Contador] = key;
      Pantalla.setCursor(Contador, 1);
      Pantalla.print(key);
      Contador++;
      delay(300);
    }
    if (Contador >= 5 ) {
      Estado = 2;
      Error = 1;
    }
  }
}

void ImgresarContrasena() {
  Pantalla.setCursor(0, 0);
  Pantalla.print("clave:");
  if (key != NO_KEY)
  {
    if (key >= '0' && key <= '9') {
      clave[Contador] = key;
      Pantalla.setCursor(Contador, 1);
      Pantalla.print(key);
      Contador++;
      delay(300);
    }
    if (Contador >= 5 ) {
      Estado = 2;
      Error = 1;
    }
  }
}
void teclaEspecial()
{
  if (key == '#') {
    switch (Estado) {
      case 0:
        boolean Verificar;
        Verificar = true;
        for (int k = 0; k < 5; k++) {
          if (llave[k] != clave[k]) {
            Verificar = false;
            break;
          }
        }
        if (Verificar) {
          Pantalla.setCursor(0, 1);
          Pantalla.print("correcta");
          if (Chapa)
            AbirCerradura();
          else
            CerrarCerradura();
          Chapa = !Chapa;
          Contador = 0;
          delay(5000);
          Pantalla.clear();
        }
        else {
          Pantalla.setCursor(0, 1);
          Pantalla.print("incorrecta");
          Contador = 0;
          delay(5000);
          Pantalla.clear();
        }
        break;
      case 1:
        if (Contador < 5) {
          GuardarEEPROM();
        }
        //guardao eeprom
        Estado = 0;
        break;
    }
  }
  else if (key == '*') {
    if (Estado == 1) {
      CargarEEPROM();
    }
    else if ( TiempoPasado == 0 )
    {
      TiempoPasado = millis();
    }
    else if (millis() - TiempoPasado > 3000)
    {
      //secuencia numero
      Estado = 1;
      TiempoPasado = 0;
    }
    else
    {
      TiempoPasado  = 0;
    }
  }
}

void Errores() {
  switch (Error) {
    case 1:
      Pantalla.clear();
      Pantalla.setCursor(0, 1);
      Pantalla.print("Error Ingresando");
      break;
    case 2:
      break;
  }
  Error = 0;
  Estado = 0;
  delay(2000);
}

void CargarEEPROM() {
  for (int i = 0; i < 5; i++) {
    llave[i] = EEPROM.read(i);
    Serial.println(llave[i]);
  }
}

void GuardarEEPROM() {
  for (int i = 0; i < 5; i++) {
    EEPROM.write(i, llave[i]);
    Serial.println(llave[i]);
  }
  CargarEEPROM();
}

void AbirCerradura() {
  Serial.println("Abierta");
  //Codigo para abir cerradura
}

void CerrarCerradura() {
  Serial.println("Cerrar");
  //codigo para abir su cerradura
}
