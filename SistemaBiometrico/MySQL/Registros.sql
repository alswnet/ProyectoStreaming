CREATE DATABASE if NOT EXISTS Registro_tmp;
USE Registro_tmp;

DROP TABLE IF EXISTS Trabajo;
DROP TABLE IF EXISTS Minion;

CREATE TABLE Minion (
	ID_Minion int(6) not null ,
	Usuario varchar(25) not null,
	Nombre varchar(25),
	Contrasena varchar(25),
	Salario double,
	PRIMARY KEY  (ID_Minion)
);

INSERT INTO Minion (ID_Minion, Usuario, Salario) VALUES ('0', 'ChepeCarlos', '0'), ('1', 'Evorock', '0'); 

CREATE TABLE Trabajo(
	ID int(10) not null AUTO_INCREMENT,
	ID_Minion int(6) not null,
	Dia DATE,
	Hora_Entrada TIME,
	Hora_Salida TIME,
	Total TIME,
	PRIMARY KEY (ID),
    INDEX (ID_Minion),
    FOREIGN KEY (ID_Minion) REFERENCES Minion(ID_Minion)
);
