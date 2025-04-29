from machine import Pin
from time import sleep
import urequests
import network

# 📌 Configuración del buzzer
buzzer = Pin(2, Pin.OUT)  # Cambia el número de pin según tu hardware
buzzer.value(0)  # Inicialmente apagado

# 📌 Configurar WiFi
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
WEBAPP_URL = "https://script.google.com/macros/s/AKfycbwIMtoPyBPZWQDR4MhhxhAXGjzdx36c9QvFBC8nKSjYkyneTvifa63Fq_xV2y92uuuVCA/exec"

def send_to_sheets(estado_buzzer):
    data = {"estado_buzzer": estado_buzzer}
    headers = {'Content-Type': 'application/json'}
    try:
        response = urequests.post(WEBAPP_URL, json=data, headers=headers)
        print("Respuesta:", response.text)
        response.close()
    except Exception as e:
        print("Error enviando datos:", e)

while True:
    try:
        # 📌 Control del buzzer
        print("🔴 Encendiendo buzzer!")
        buzzer.value(1)  # Encender buzzer
        send_to_sheets("Encendido")  # Enviar estado a Google Sheets
        sleep(2)

        # 📌 Apagar el buzzer
        print("✅ Apagando buzzer")
        buzzer.value(0)  # Apagar buzzer
        send_to_sheets("Apagado")  # Enviar estado a Google Sheets
        sleep(2)
    
    except Exception as e:
        print("Error en el control del buzzer:", e)

    print("-" * 20)
