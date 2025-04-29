from machine import Pin
from time import sleep
import urequests
import network

# Configurar motor de vibración
vibration_motor = Pin(2, Pin.OUT)  # Cambia el número de pin según tu hardware
vibration_motor.value(0)  # Inicialmente apagado

# Configurar WiFi
def connect_wifi():
    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    sta_if.connect("UTNG_Alumnos", "")
    while not sta_if.isconnected():
        print(".", end="")
        sleep(0.5)
    print("\nWiFi OK IP:", sta_if.ifconfig()[0])

connect_wifi()

# 📌 URL corregida de Google Apps Script
WEBAPP_URL = "https://script.google.com/macros/s/AKfycbylWerXSlkPdWtlSKMbRu_F0jLguzyl_0zQMtJdkcjbkRZpI1xHNtQX9qktZAYZPL6d3w/exec"

def send_to_sheets(estado_motor):
    data = {"estado_motor": estado_motor}
    headers = {'Content-Type': 'application/json'}
    try:
        response = urequests.post(WEBAPP_URL, json=data, headers=headers)
        print("Respuesta:", response.text)
        response.close()
    except Exception as e:
        print("Error enviando datos:", e)

while True:
    try:
        # Encender motor de vibración
        print("🔴 Activando vibración!")
        vibration_motor.value(1)
        send_to_sheets("Encendido")  # Enviar estado a Google Sheets
        sleep(2)

        # Apagar motor de vibración
        print("✅ Apagando vibración!")
        vibration_motor.value(0)
        send_to_sheets("Apagado")  # Enviar estado a Google Sheets
        sleep(2)
    
    except Exception as e:
        print("Error en el control del motor:", e)

    print("-" * 20)
