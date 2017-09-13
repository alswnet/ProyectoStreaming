import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.app.Activity;

int BACKGND=0; //Set the background to BLUE
//Get the default Bluetooth adapter
  BluetoothAdapter bluetooth = BluetoothAdapter.getDefaultAdapter();

/*The startActivityForResult() launches an Activity which is
 used to request the user to turn Bluetooth on. 
 The following onActivityResult() method is called when the 
 Activity exits. */
@Override public void onActivityResult(int requestCode, int resultCode, Intent data) {
  if (requestCode==0) {
    if (resultCode == Activity.RESULT_OK) {
      BACKGND=2; //Set the background to GREEN
    } else {
      BACKGND=1; //Set the background to RED
    }
  }
}

void setup() {
  fullScreen();
  orientation(LANDSCAPE);

  /*IF Bluetooth is NOT enabled, 
   then ask user permission to enable it */
  if (!bluetooth.isEnabled()) {
    Intent requestBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
    startActivityForResult(requestBluetooth, 0);
  }
}
void draw() {
  if (BACKGND==0) {
    background(10, 10, 255); //Set background to BLUE
  } else if (BACKGND==1) {
    background(255, 10, 10); //Set background to RED
  } else {
    background(10, 255, 10); //Set background to GREEN
  }
}