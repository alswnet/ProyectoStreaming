#include <LiquidCrystal.h>
#include <Keypad.h>

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(19, 18, 17, 16, 15, 14);
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
int i = 0;
int j = 0;
float TiempoPasado = 0;
char key;
int Estado = 0;
int Error = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); //initialise the serial port (9600 baud)
}

void loop() {
  key = keypad.getKey();
  switch (Estado)
  {
    case 0:
      ImgresarContrasena();
      break;
    case 1:
      IngresarNuevaContrase();
      break;
    case 2:
      error();
      break;
    default:
      Estado = 0;
      break;
  }
  teclaEspecial();

}

void IngresarNuevaContrase()[
  lcd.setCursor(0, 0);
  lcd.print("nueva clave:");
  //dddddd

]

void ImgresarContrasena() {
  lcd.setCursor(0, 0);
  lcd.print("clave:");
  if (key != NO_KEY)
  {
    if (key >= '0' && key <= '9') {
      clave[i] = key;
      lcd.setCursor(i, 1);
      lcd.print(key);
      i++;
      delay(300);
    }
    if (i > 4 ) {
     Estado = 2;
     Error =1;
    }
  }

}
void teclaEspecial()
{
  if (key == '#') {
    if (Estado == 0) {
      boolean pollo = true;
      for (int k = 0; k < 5; k++) {
        if (llave[k] != clave[k]) {
          pollo = false;
          break;
        }
      }
      if (pollo)
      {
        lcd.setCursor(0, 1);
        lcd.print("correcta");
        i = 0;
        delay(5000);
        lcd.clear();
      }
      else
      {
        lcd.setCursor(0, 1);
        lcd.print("incorrecta");
        i = 0;
        delay(5000);
        lcd.clear();
      }
    }
    else if (Estado == 1) {
      if (i < 5)[
          cargarEprom();
        ]
        //guardao eeprom
        Estado = 0;
    }
  }
  else if (key == '*') {
    if (Estado == 1)[
        cargarEprom();
      ]
      else if ( TiempoPasada == 0 )
      {
        TiempoPasado = millis();
      }
      else if (millis() - TiempoPasado > 3000)
      {
        //secuencia numero
        Estado = 1;
        Tiempo = 0;
      }
      else
      {
        Tiempo = 0;
      }
  }
}

void Errrors()[
swue(error){
  case 1
  lc... sss
  case 2
  lcd ..sssss
  
  }

]

void CargarEprom() {
}

vooid guardadEpprm() {

}
