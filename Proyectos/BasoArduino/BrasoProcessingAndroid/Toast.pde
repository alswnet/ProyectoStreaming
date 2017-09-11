import android.widget.Toast;
import android.view.Gravity;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
 
void ToastMaster(String Texto) {
  Activity Actividad;
  Actividad = this.getActivity();
  Toast MiMensaje = Toast.makeText(Actividad.getApplicationContext(), Texto, Toast.LENGTH_LONG);
  MiMensaje.setGravity(Gravity.CENTER, 0, 0);
  MiMensaje.show();
}