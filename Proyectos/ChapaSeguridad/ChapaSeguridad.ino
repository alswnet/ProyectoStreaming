#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal Pantalla(19, 18, 17, 16, 15, 14);
const byte Filas = 4; //4 fial
const byte Columnas = 3; //3 columnas
char keys[Filas][Columnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte PinesFila[Filas] = {5, 4, 10, 2}; //pines para filas   vivo aqui le movi del pin 3 al 10 porque esta jodido el 3 en este arduino pero va en el 3 OJO
byte PinesColumna[Columnas] = {8, 7, 6}; //pines para filas

//vectores para clave
char clave[] = {'0', '0', '0', '0', '0'}; //se declara un vector de tipo caracter de 5 posiciones
char llave[] = {'2', '3', '5', '6', '8'}; //se declara un vector de tipo caracter de 5 posiciones
int Contador = 0; //contadores
float TiempoPasado = 0;
char key;
int Estado = 0;
boolean Chapa;  //banderas
int Error = 0;

Keypad Teclado = Keypad( makeKeymap(keys), PinesFila, PinesColumna, Filas, Columnas );

void setup() {
  Pantalla.begin(16, 2);  //iniciamos la pantalla LCD
  Serial.begin(9600); //initialise the serial port (9600 baud)
  Chapa = false;  //le asignamos el estado falso a chapa
  CerrarCerradura();  //nos dirigimos al proceso CerrarCerradura
}

void loop() {
  key = Teclado.getKey(); //le asignamos a key el numero que precionamos en el teclado
  switch (Estado)         
  {
    case 0:               //si estado es igual a 0 se va a IngresarContraseña
      ImgresarContrasena();
      break;
    case 1:               //si estado es igual a 1 se va a IngresarNuevaContraseña
      IngresarNuevaContrase();
      break;
    case 2:               //si estado es igual a 2 se va a Errores
      Errores();
      break;
    default:
      Estado = 0;         //si no es ninguna estado vuelve a valer 0
      break;
  }
  teclaEspecial();        //se dirigue al proceso TecladoEspecial
}

void IngresarNuevaContrase() {
  Pantalla.setCursor(0, 0);   //ubicamos el cursor en la coordenada 0,0 de la LCD
  Pantalla.print("nueva clave:"); //escribimos en la LCD
  if (key != NO_KEY)          //verificamos si se digita un numero
  {
    if (key >= '0' && key <= '9') {   //verificamos si el numero esta entre 0 y 9
      llave[Contador] = key;          //se guardan en las posiciones del vector la clave
      Pantalla.setCursor(Contador, 1);    //se va desplazando el cursor de la LCD
      Pantalla.print(key);            //se imprime la tecla presionada en le monitor 
      Contador++;                     //se incrementa contador en contador + 1
      delay(300);                     //se hace una espera de 300miliSegundos
    }
    if (Contador >= 5 ) {             //se verifica si contador es mayor o igual a 5
      Estado = 2;                     //se le asigna el valor de 2 a Estado
      Error = 1;                      //se le asigna el valor de 1 a Error
    }
  }
}

void ImgresarContrasena() {
  Pantalla.setCursor(0, 0);           //ubicamos el cursor en la coordenada 0,0 de la LCD
  Pantalla.print("clave:");           //Escribimos en la LCD la palabra clave:
  if (key != NO_KEY)                  //verificamos si se a presionado una tecla
  {                                   
    if (key >= '0' && key <= '9') {   //verificamos si el numero esta entre 0 y 9
      clave[Contador] = key;          //se guardan en las posiciones del vector la clave
      Pantalla.setCursor(Contador, 1);//se va desplazando el cursor de la LCD
      Pantalla.print(key);            //se imprime la tecla presionada en le monitor
      Contador++;                     //se incrementa contador en contador + 1
      delay(300);                     //se hace una espera de 300miliSegundos
    }
    if (Contador >= 5 ) {             //se verifica si contador es mayor o igual a 5
      Estado = 2;                     //se le asigna el valor de 2 a Estado
      Error = 1;                      //se le asigna el valor de 1 a Error
    }
  }
}
void teclaEspecial()
{
  if (key == '#') {                   //se verifica si se digita la teclaa "#"
    switch (Estado) {                 
      case 0:                         //si estado vale 0
        boolean Verificar;            //se declara una variable de tipo boolean
        Verificar = true;             //se le asigna el estado de verdadero a la variable
        for (int k = 0; k < 5; k++) { //ciclo for para comparar la clave del usuario con la real y si falla se sale autmaticamente si acierta mantiene la variable verificar en verdadero
          if (llave[k] != clave[k]) {
            Verificar = false;       
            break;
          }
        }
        if (Verificar) {              //si verificar es verdadero (es decir no se equivoco en la contraseña)
          Pantalla.setCursor(0, 1);   //se ubica el cursor en la coordenada 0,1 de la LCD
          Pantalla.print("correcta"); //Se imprime la palabra Correcta
          if (Chapa)                  //si chapa es verdadero
            AbirCerradura();          //entra al procesoo AbirCerradura
          else
            CerrarCerradura();        //entra al proceso CerrarCerradura
          Chapa = !Chapa;             //le asigna a chapa lo contrario que tenia chapa
          Contador = 0;               //se reinicia el contador
          delay(5000);                //espera de 5 segundos
          Pantalla.clear();           //se borra la LCD
        }
        else {
          Pantalla.setCursor(0, 1);   //se ubica el cursor en la coordenada 0,1 de la LCD
          Pantalla.print("incorrecta"); //se escribe en la LCD
          Contador = 0;               //se reinicia el contador
          delay(5000);                //espera de 5 segundos
          Pantalla.clear();           //se borra la LCD
        }
        break;
      case 1:
        if (Contador < 5) {           //si el contador es menor a 5 se dirige al proceso GuardarEEPROM() 
          GuardarEEPROM();
        }
        //guardao eeprom
        Estado = 0;                   //se le asigna 0 a la variable estado
        break;
    }
  }
  else if (key == '*') {              //se verifica si se preciona la tecla "*"
    if (Estado == 1) {                //se verifica si estado vale 1
      CargarEEPROM();                 //se dirige al proceso CargarEEPROM()
    }
    else if ( TiempoPasado == 0 )     //verifica si la variable TiempoPasado es igual a 0
    {
      TiempoPasado = millis();        //la variable TiempoPasado comienza a contar  
    }
    else if (millis() - TiempoPasado > 3000)  //si la variable TiempoPasado es mayor a 3 segundos
    {
      //secuencia numero
      Estado = 1;                             //se le asigna 1 a la variable estado
      TiempoPasado = 0;                       //se le asigna 0 a la variable TiempoPasado 
    }
    else
    {
      TiempoPasado  = 0;                      //se le asigna 0 a la variable TiempoPasado 
    }
  }
}

void Errores() {
  switch (Error) {                      
    case 1:                             //se verifica si la variable Error vale 1
      Pantalla.clear();                 // se reinicia la pantalla
      Pantalla.setCursor(0, 1);         //se ubica el cursor en la coordenada 0,1 de la LCD
      Pantalla.print("Error Ingresando"); //se imprime la palabra Error Ingresando en la pantalla
      break;
    case 2:
      break;
  }
  Error = 0;                            //se le asigna 0 a la variable Error
  Estado = 0;                           //se le asigna 0 a la variable Estado
  delay(2000);                          //se hace una espera de 2 segundos
}

void CargarEEPROM() {
  for (int i = 0; i < 5; i++) {         
    llave[i] = EEPROM.read(i);          //almacena en el vector llave los valores que estan guardados en la memoria EEPROM
    Serial.println(llave[i]);           //se imprimen en el monitor serial la nueva clave
  }
}

void GuardarEEPROM() {
  for (int i = 0; i < 5; i++) {
    EEPROM.write(i, llave[i]);          //se guarda en la memoria EEPROM lo que tiene el vector llave
    Serial.println(llave[i]);           //se imprime en el monitor serial lo que tiene el vector llave
  }
  CargarEEPROM();                       //se va al proceso CargarEEPROM
}

void AbirCerradura() {
  Serial.println("Abierta");            //Escribe en el monitor Serial la palabra "abierta"
  //Codigo para abir cerradura
}

void CerrarCerradura() {
  Serial.println("Cerrar");             //Escribe en el monitor Serial la palabra "cerrar"
  //codigo para abir su cerradura
}
