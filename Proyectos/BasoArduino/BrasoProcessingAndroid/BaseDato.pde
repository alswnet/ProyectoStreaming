import ketai.data.*;

KetaiSQLite BaseDato;

String Create_Configuracion = 
  " CREATE TABLE Configuracion ( " +
  " _id INTEGER PRIMARY KEY AUTOINCREMENT," +
  " Titulo TEXT NOT NULL," +
  " Dato INTEGER NOT NULL DEFAULT '0'" +
  " );";

void InicializarDB() {
  BaseDato = new KetaiSQLite(this);
  if (BaseDato.connect()) {
    if (!BaseDato.tableExists("Configuracion")) {
     BaseDato.execute(Create_Configuracion);
     println("Creando DB");
    }
  }
}