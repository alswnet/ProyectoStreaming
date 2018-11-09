/*
  || @file Keypad Password
  || @version 1.0
  || @author Andrew Mascolo
  || @date May 7, 2013
  ||
  || @description
  || Simple use of keypad, password and LCD
*/
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Password_Lenght 5 // Give enough room for six chars + NULL char
int Paso;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
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

byte rowPins[ROWS] = {5, 0, 4, 13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 12, 16}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()
{
  lcd.init();// initialize the lcd
  lcd.backlight();
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Presione * o #");
  lcd.setCursor(6, 1);
  lcd.print("4 veces");

  customKey = customKeypad.getKey();
  if (customKey == '*')
  {
    Paso = 1;
  }
  if (customKey == '#')
  {
    Paso = 2;
  }
  if (Paso == 1)
  {

    if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
    {
      Data[data_count] = customKey; // store char into data array
      lcd.setCursor(data_count, 1); // move cursor to show each new char
      lcd.print(Data[data_count]); // print char at said cursor
      data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
    }

    if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
    {
      delay(2000);
      if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
      { lcd.clear();
        lcd.print("Good");
        Paso = 0;
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
        lcd.setCursor(0, 1);
        lcd.print("su codigo");
      }


      delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
      lcd.clear();
      clearData();
    }
  }
  if (Paso == 2)
  {

    if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
    {
      Data[data_count] = customKey; // store char into data array
      lcd.setCursor(data_count, 1); // move cursor to show each new char
      lcd.print(Data[data_count]); // print char at said cursor
      data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
    }

    if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
    {
      delay(2000);
      if (!strcmp(Data, Salida)) // equal to (strcmp(Data, Master) == 0)
      { lcd.clear();
        lcd.print("Good");
        Paso = 0;
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
        lcd.setCursor(0, 1);
        lcd.print("su codigo");
      }


      delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
      lcd.clear();
      clearData();
    }
  }
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
