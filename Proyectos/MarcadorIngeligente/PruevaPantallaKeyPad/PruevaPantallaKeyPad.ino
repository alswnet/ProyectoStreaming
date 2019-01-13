// las librerias fueron descargadas del IDE de arduino pueden ser halladas como
//keypad by mark Stanley and Alexander Brevig
//LiquidCrystal_I2C by Frank de Brabander
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Password_Lenght 5 //El largo de la contrasenia, aunque diga 5, en realidad son 4 cifras, la 5ta es un limite
int Paso;
int Paso1;
int Mensaje;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
char Data[Password_Lenght]; // 4 es el numero que puede soportar, y 5 es el limite
char Master[Password_Lenght] = "1234";
char Salida[Password_Lenght] = "5678";
char Entrada[Password_Lenght] = "****";
char Chief[Password_Lenght] = "####";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'2', '1', '3'},
  {'5', '4', '6'},
  {'8', '7', '9'},
  {'0', '*', '#'}
};

byte rowPins[ROWS] = {5, 0, 4, 13}; //conectar a los pines de las filas del keypad
byte colPins[COLS] = {15, 12, 16}; //conectar a los pines de las columnas del keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //inicializar una nueva instancia de un keypad

void setup()
{
  lcd.init();//iniciar la lcd
  lcd.backlight();
}

void loop()
{
  if(Mensaje<12)
  {
  lcd.setCursor(0, 0);
  lcd.print("Presione * o #");
  lcd.setCursor(6, 1);
  lcd.print("4 veces");
  }

  if(Mensaje>=12)
  {

        lcd.setCursor(0, 0);
        lcd.print("Ingrese");
        lcd.setCursor(6, 1);
        lcd.print("su codigo");
  }

  customKey = customKeypad.getKey();
  if (customKey == '*')
  {
    Paso = 1;
    Mensaje=Mensaje+3;
  }
  if (customKey == '#')
  {

    
    Paso = 2;
    Mensaje=Mensaje+3;
  }
  if (Paso == 1)
  {
    
      if (customKey) // se aasegura que una tecla es presionada, es igual a (customKey != NO_KEY)
    {
      Data[data_count] = customKey; // convierte el char en array
      lcd.setCursor(data_count, 1); // mueve el cursor para mostrar el nuevo char
      lcd.print(Data[data_count]); // que imprima el char en el cursor dicho
      data_count++; // incrementa en uno la cantidad de chars agregados y a su vez lleva una cuenta de los mismos
    }


    if (data_count == Password_Lenght - 1) // si la cantidad de chars ingresados son iguales a los designados arriba, comparar con el codigo maestro
    {
      delay(2000);
      if (!strcmp(Data, Master)) // igual a (strcmp(Data, Master) == 0)
      { lcd.clear();
        lcd.print("Good");
        Paso = 0;
        Mensaje=0;
      }
      else
      { lcd.clear();
        lcd.print("Bad");
      }

      if (!strcmp(Data, Entrada))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese");
        lcd.setCursor(6, 1);
        lcd.print("su codigo");
      }


      delay(1000);// agregamos un segundo de espera para asegurarnos que la contrasenia es mostrada en pantalla
      lcd.clear();
      clearData();
    }
  }
  
  if (Paso == 2)
  {



      if (customKey) // se aasegura que una tecla es presionada, es igual a (customKey != NO_KEY)
    {
      Data[data_count] = customKey; // convierte el char en array
      lcd.setCursor(data_count, 1); // mueve el cursor para mostrar el nuevo char
      lcd.print(Data[data_count]); // que imprima el char en el cursor dicho
      data_count++; // incrementa en uno la cantidad de chars agregados y a su vez lleva una cuenta de los mismos
    }

    if (data_count == Password_Lenght - 1) 
    {
      delay(2000);
      if (!strcmp(Data, Salida)) // igual a (strcmp(Data, Master) == 0)
      { lcd.clear();
        lcd.print("Good");
        Paso = 0;
        Mensaje=0;
      }
      else
      { lcd.clear();
        lcd.print("Bad");
      }

      if (!strcmp(Data, Chief))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese");
        lcd.setCursor(6, 1);
        lcd.print("su codigo");
      }


      delay(1000);
      lcd.clear();
      clearData();
    }
  }
}


void clearData()
{
  while (data_count != 0)
  { // puede ser usado para cualquier tamanio de arrays
    Data[data_count--] = 0; //limpia el array para nueva data
  }
  return;
}
