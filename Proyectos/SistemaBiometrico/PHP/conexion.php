<?php

$conn= mysqli_connect('localhost', 'root', 'fullpower7','Registro_tmp');

// Check connection
if ($conn->connect_error) {
    die("Error con la MySQLi: " . $conn->connect_error);
}
