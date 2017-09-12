import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import java.util.ArrayList;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
 
private static final int REQUEST_ENABLE_BT = 3;
ArrayList dispositivos;
BluetoothAdapter adaptador;
BluetoothDevice dispositivo;
BluetoothSocket socket;
InputStream ins;
OutputStream ons;
boolean registrado = false;
PFont f1;
PFont f2;
int estado;
String error;
byte valor;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BroadcastReceiver receptor = new BroadcastReceiver()
{
    public void onReceive(Context context, Intent intent)
    {
        println("onReceive");
        String accion = intent.getAction();
 
        if (BluetoothDevice.ACTION_FOUND.equals(accion))
        {
            BluetoothDevice dispositivo = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            println(dispositivo.getName() + " " + dispositivo.getAddress());
            dispositivos.add(dispositivo);
        }
        else if (BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(accion))
        {
          estado = 0;
          println("Empieza búsqueda");
        }
        else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(accion))
        {
          estado = 1;
          println("Termina búsqueda");
        }
 
    }
};
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //size(320,480);
  frameRate(25);
  f1 = createFont("Arial",20,true);
  f2 = createFont("Arial",15,true);
  stroke(255);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw() {
  switch(estado)
  {
    case 0:
      listaDispositivos("BUSCANDO DISPOSITIVOS", color(255, 0, 0));
      break;
    case 1:
      listaDispositivos("ELIJA DISPOSITIVO", color(0, 255, 0));
      break;
    case 2:
      conectaDispositivo();
      break;
    case 3:
      muestraDatos();
      break;
    case 4:
      muestraError();
      break;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onStart()
{
  super.onStart();
  println("onStart");
  adaptador = BluetoothAdapter.getDefaultAdapter();
  if (adaptador != null)
  {
    if (!adaptador.isEnabled())
    {
        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
    }
    else
    {
      empieza();
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onStop()
{
  println("onStop");
  /*
  if(registrado)
  {
    unregisterReceiver(receptor);
  }
  */
 
  if(socket != null)
  {
    try
    {
      socket.close();
    }
    catch(IOException ex)
    {
      println(ex);
    }
  }
  super.onStop();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onActivityResult (int requestCode, int resultCode, Intent data)
{
  println("onActivityResult");
  if(resultCode == RESULT_OK)
  {
    println("RESULT_OK");
    empieza();
  }
  else
  {
    println("RESULT_CANCELED");
    estado = 4;
    error = "No se ha activado el bluetooth";
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mouseReleased()
{
  switch(estado)
  {
    case 0:
      /*
      if(registrado)
      {
        adaptador.cancelDiscovery();
      }
      */
      break;
    case 1:
      compruebaEleccion();
      break;
    case 3:
      compruebaBoton();
      break;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void empieza()
{
    dispositivos = new ArrayList();
    /*
    registerReceiver(receptor, new IntentFilter(BluetoothDevice.ACTION_FOUND));
    registerReceiver(receptor, new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_STARTED));
    registerReceiver(receptor, new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED));
    registrado = true;
    adaptador.startDiscovery();
    */
    for (BluetoothDevice dispositivo : adaptador.getBondedDevices())
    {
        dispositivos.add(dispositivo);
    }
    estado = 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listaDispositivos(String texto, color c)
{
  background(0);
  textFont(f1);
  fill(c);
  text(texto,0, 20);
  if(dispositivos != null)
  {
    for(int indice = 0; indice < dispositivos.size(); indice++)
    {
      BluetoothDevice dispositivo = (BluetoothDevice) dispositivos.get(indice);
      fill(255,255,0);
      int posicion = 50 + (indice * 55);
      if(dispositivo.getName() != null)
      {
        text(dispositivo.getName(),0, posicion);
      }
      fill(180,180,255);
      text(dispositivo.getAddress(),0, posicion + 20);
      fill(255);
      line(0, posicion + 30, 319, posicion + 30);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void compruebaEleccion()
{
  int elegido = (mouseY - 50) / 55;
  if(elegido < dispositivos.size())   
  {     
    dispositivo = (BluetoothDevice) dispositivos.get(elegido);     
    println(dispositivo.getName());     
    estado = 2;   
  } 
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void conectaDispositivo() 
{   
  try   
  {     
    socket = dispositivo.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
    /*     
      Method m = dispositivo.getClass().getMethod("createRfcommSocket", new Class[] { int.class });     
      socket = (BluetoothSocket) m.invoke(dispositivo, 1);             
    */     
    socket.connect();     
    ins = socket.getInputStream();     
    ons = socket.getOutputStream();     
    estado = 3;   
  }   
  catch(Exception ex)   
  {     
    estado = 4;     
    error = ex.toString();     
    println(error);   
  } 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void muestraDatos() 
{   
  try
  {     
    while(ins.available() > 0)
    {
      valor = (byte)ins.read();
    }
  }
  catch(Exception ex)
  {
    estado = 4;
    error = ex.toString();
    println(error);
  }
  background(0);
  fill(255);
  text(valor, width / 2, height / 2);
  stroke(255, 255, 0);
  fill(255, 0, 0);
  rect(120, 400, 80, 40);
  fill(255, 255, 0);
  text("Botón", 135, 425);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void compruebaBoton()
{
  if(mouseX > 120 && mouseX < 200 && mouseY > 400 && mouseY < 440)
  {
    try
    {
        ons.write(0);
    }
    catch(Exception ex)
    {
      estado = 4;
      error = ex.toString();
      println(error);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void muestraError()
{
  background(255, 0, 0);
  fill(255, 255, 0);
  textFont(f2);
  textAlign(CENTER);
  translate(width / 2, height / 2);
  rotate(3 * PI / 2);
  text(error, 0, 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////