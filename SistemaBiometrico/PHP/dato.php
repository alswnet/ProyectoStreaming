<?php

include("conexion.php");

//Verificar que se enviara el ID via metodo GET
if (isset($_GET["ID"])){
	$ID = $_GET["ID"];
	$hoy = date("Y-n-j");//Dia actual
	$Hora = date("H:i:s");//Hora actual

	$Entrada = 0;
	//Consulta para buscar si el usuario ID llego mas temprano a marcar
	$Buscar_SQL = "SELECT  * from Trabajo where ID_Minion = '$ID' and Dia = '$hoy' and Total is null order by ID DESC";
	$Busqueda = mysqli_query($conn, $Buscar_SQL);

	if (mysqli_num_rows($Busqueda) > 0) {
	//Hay registro que llego mas temprano se procesa a actualizar la hora de salida y total
		$Entrada = 1;
		$Dato = mysqli_fetch_assoc($Busqueda);
		$ID_Entrada = $Dato["ID"];//Se saca el ID de este registro
		$Hora_Entrada = $Dato["Hora_Entrada"];//Hora de entrada para calcular cuanto tiempo trabajo

		//Se actualiza el registro con la hora de salida y el total de horas trabajadas
		$Buscar_SQL = "UPDATE Trabajo SET Hora_Salida = '$Hora', Total = TIMEDIFF('$Hora','$Hora_Entrada') where ID = $ID_Entrada";
	}
	else {
	//No encntro mas temprano, ingresa uno nuevo registro con la hora actual
		$Buscar_SQL = "INSERT INTO Trabajo (ID_Minion, Dia, Hora_Entrada) VALUES ('$ID', '$hoy', '$Hora')";
		$Entrada = 2;
	}

	if (mysqli_query($conn, $Buscar_SQL)){
		//echo "OK<br>";
		if($Entrada == 2){
			echo "<h1>Entrada</h1>";
		}
		else if($Entrada == 1){
			echo "<h1>Salida</h1>";
		}
		else{
			echo "<h1>Error</h1>";
		}
		echo "%";
	}
	else{
		echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}
}
else{
	echo "No envio ID";
}

//Cerrar conexcion con MySQL
 mysqli_close($conn);

?>
