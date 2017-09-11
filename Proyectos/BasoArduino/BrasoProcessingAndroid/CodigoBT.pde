import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.app.Activity;

//Objeto BT
BluetoothAdapter bluetooth = BluetoothAdapter.getDefaultAdapter();

//Estado del BT
int EstadoBT=0;
//Estado = 2 BT Activado
//Estado = 1 BT Negado de Activarse
//Estado = 0 No tiene BT

@Override public void onActivityResult(int requestCode, int resultCode, Intent data) {
  println("Regresando");
  if (requestCode==0) {
    if (resultCode == Activity.RESULT_OK) {
      EstadoBT=2; //El BT esta activado
    } else {
      EstadoBT=1; //El BT esta desactivado
    }
  }
}

void EncenderBT() {
  if (!bluetooth.isEnabled()) {
    println("Activando BT");
    Intent requestBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
    startActivity(requestBluetooth);
  }
}