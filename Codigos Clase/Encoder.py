from machine import Pin, PWM
import time

# Configuración de pines para el motor A
ena = PWM(Pin(12))
in1 = Pin(13, Pin.OUT)
in2 = Pin(14, Pin.OUT)

# Configuración de pines para el motor B
enb = PWM(Pin(27))
in3 = Pin(26, Pin.OUT)
in4 = Pin(25, Pin.OUT)

# Frecuencia PWM (1kHz es común para motores)
ena.freq(1000)
enb.freq(1000)

def motor_a(velocidad, adelante):
    velocidad = max(0, min(100, velocidad))  # Limitar entre 0-100
    ena.duty(int(velocidad * 10.23))  # Convertir 0-100% a 0-1023
    
    if adelante:
        in1.on()
        in2.off()
    else:
        in1.off()
        in2.on()

def motor_b(velocidad, adelante):
    velocidad = max(0, min(100, velocidad))  # Limitar entre 0-100
    enb.duty(int(velocidad * 10.23))  # Convertir 0-100% a 0-1023
    
    if adelante:
        in3.on()
        in4.off()
    else:
        in3.off()
        in4.on()

def detener_motores():
    motor_a(0, True)
    motor_b(0, True)

# Ejemplo de uso
try:
    while True:
        print("Motores adelante al 50%")
        motor_a(10, True)
        motor_b(10, True)
        time.sleep(2)
        
        print("Motores atrás al 30%")
        motor_a(10, False)
        motor_b(10, False)
        time.sleep(2)
        
        print("Motor A adelante 80%, Motor B atrás 60%")
        motor_a(10, True)
        motor_b(10, False)
        time.sleep(2)
        
        print("Deteniendo motores")
        detener_motores()
        time.sleep(1)
        
except KeyboardInterrupt:
    detener_motores()
    print("Programa detenido")