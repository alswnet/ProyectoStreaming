<?php

$conn= mysqli_connect('localhost', 'root', 'fullpower7','Registro_tmp');

// Check connection
if ($conn->connect_error) {
    die("Error con la MySQLi: " . $conn->connect_error);
}

//Verificar que se enviara el ID via metodo GET
if (isset($_GET["ID"])){ 
	$ID = $_GET["ID"];
	$hoy = date("Y-n-j");//Dia actual 
	$Hora = date("H:i:s");//Hora actual

	//Consulta para buscar si el usuario ID llego mas temprano a marcar
	$Buscar_SQL = "SELECT  * from Trabajo where ID_Minion = '$ID' and Dia = '$hoy' and Total is null order by ID DESC";
	echo $Buscar_SQL."<br>";

	$Busqueda = mysqli_query($conn, $Buscar_SQL);

	if (mysqli_num_rows($Busqueda) > 0) {
	//Hay registro que llego mas temprano se procesa a actualizar la hora de salida y total 
		$Dato = mysqli_fetch_assoc($Busqueda);
		$ID_Entrada = $Dato["ID"];//Se saca el ID de este registro 
		$Hora_Entrada = $Dato["Hora_Entrada"];//Hora de entrada para calcular cuanto tiempo trabajo
		
		//Se actualiza el registro con la hora de salida y el total de horas trabajadas
		$Actualizar_SQL = "UPDATE Trabajo SET Hora_Salida = '$Hora', Total = TIMEDIFF('$Hora','$Hora_Entrada') where ID = $ID_Entrada";
		echo $Actualizar_SQL."<br>";
		if (mysqli_query($conn,  $Actualizar_SQL)){
			echo "OK";
		}
		else{
			echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	} 
	else {
	//No encntro mas temprano, ingresa uno nuevo registro con la hora actual
		$Intertar_SQL = "INSERT INTO Trabajo (ID_Minion, Dia, Hora_Entrada) VALUES ('$ID', '$hoy', '$Hora')";
		echo $Intertar_SQL."<br>";

		if (mysqli_query($conn, $Intertar_SQL)){
			echo "OK";
		}
		else{
			echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
}
else{
	echo "Error no encontrado ID";
}

//Cerrar conexcion con MySQL
 mysqli_close($conn); 

?>
