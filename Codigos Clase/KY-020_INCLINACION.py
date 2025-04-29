from machine import Pin
from time import sleep
import urequests
import network

# Configurar sensor de inclinación KY-020
ky020 = Pin(15, Pin.IN)

# Configurar WiFi
def connect_wifi():
    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    sta_if.connect("UTNG_Alumnos", "")
    while not sta_if.isconnected():
        print(".", end="")
        sleep(0.5)
    print("WiFi OK IP:", sta_if.ifconfig()[0])

connect_wifi()

# URL del WebApp de Google
WEBAPP_URL = "https://script.google.com/macros/s/AKfycbwY0NLHQBHDJU0rFc5h4G6vqhjyzugvEb5gZcBbzfT6U-L1BWvxBQSn9lGebNOs-FR5XQ/exec"

def send_to_sheets(inclinacion):
    data = {
        "inclinacion": inclinacion
    }
    try:
        response = urequests.post(WEBAPP_URL, json=data)
        print("Respuesta:", response.text)
        response.close()
    except Exception as e:
        print("Error enviando datos:", e)

while True:
    try:
        inclinacion = ky020.value()  # 1 si está inclinado, 0 si está recto
        print(f"Inclinación: {'Sí' if inclinacion else 'No'}")
        
        send_to_sheets(inclinacion)
    
    except Exception as e:
        print("Error al leer sensor:", e)
    
    sleep(2)
