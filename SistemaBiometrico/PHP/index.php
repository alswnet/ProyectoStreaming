<?php

include("conexion.php");

$Busca = "SELECT * from Minion";
$Consulta = mysqli_query($conn, $Busca);
if(mysqli_num_rows($Consulta) > 0){
?>
  <form name="Buscando Minion" method="GET" action="index.php">
    Nombre del Minion:
      <select name="Nombre_Minion">
<?PHP
  while($Dato = mysqli_fetch_assoc($Consulta)) {
    echo "<option value=\"".$Dato["ID_Minion"]."\">".$Dato["Nombre"]."</option><br>";
    }
    echo "   </select>";
}
else{
    echo "<h1>No encuentro minion</h1>";
  }
  ?>
  <input type="submit"  value="Buscar"/>
  </form>
<?php



if(isset($_GET["Nombre_Minion"])){
//Codifo con ID
  $ID =  $_GET["Nombre_Minion"];
  $Consulta2 = "SELECT * FROM Trabajo where ID_Minion = '$ID' order by ID DESC";
  echo $Consulta2."<br>";
  $Busqueda2 = mysqli_query($conn, $Consulta2);
  if (mysqli_num_rows($Busqueda2) > 0) {
    $SuperTotal =  date ( 'H:i:s',"0:0:0");
      while($Dato = mysqli_fetch_assoc($Busqueda2)) {
        $Dia  = $Dato["Dia"];
        $Entrada = $Dato["Hora_Entrada"];
        $Salida = $Dato["Hora_Salida"];
        $Total = $Dato["Total"];
        $SuperTotal = strtotime($SuperTotal,$Total);
        echo $Dia." - ".$Entrada." - ".$Salida." - ".$Total."<br>";
      }
      echo date( 'H:i:s' ,$SuperTotal);
    }
  }
else{
  echo "<h1>Buscan Minion</h1>";
}



//Cerrar conexcion con MySQL
 mysqli_close($conn);

 ?>
