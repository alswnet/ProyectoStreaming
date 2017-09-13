#!/user/bin/env python
# -*- coding: utf-8 -*-

#Librerias
import time
import serial
import smtplib
import mimetypes

#importar modulos
from email.MIMEText import MIMEText

#Declaro el correo y contraseña
Emisor = "Correo@emisor.com"
Receptor = "Correo@receptor.com"
Contrasena = "contraseña"
Puerto = serial.Serial('/dev/ttyUSB0',9600)


def EnviarCorreo():
	print "Iniciando envio"
	#Obteniendo la fecha y hora actual 
	Fecha = time.strftime("%d/%m/%y")
	Hora = time.strftime("%H:%M:%S")

	#Creando mensaje a mandar
	Mensaje = MIMEText("Hola alquien se metio el "+ Fecha+ "a la hora " + Hora + " Peligro")
	Mensaje['From'] = Emisor
	Mensaje['To'] = Receptor
	Mensaje['Subject'] = "Alarma " + Fecha + " " + Hora

	print Mensaje

	#Preparando comunicacion
	mailServer = smtplib.SMTP('smtp.gmail.com',587)
	mailServer.ehlo()
	mailServer.starttls()
	mailServer.ehlo()
	mailServer.login(Emisor, Contrasena)

	#enviar el correo 
	mailServer.sendmail(Emisor, Receptor, Mensaje.as_string())
	print("Mensaje Enviado")

	mailServer.close()

while True:
	Dato = Puerto.readline()
	print(Dato)
	if Dato[0] == '1':
		print("Encontrado")
		EnviarCorreo()
		time.sleep(1) 
	time.sleep(0.5)
