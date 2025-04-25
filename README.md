# IoT_Unidad3_InstrumentoEvaluacion

# El Tachomorfinador 62 💊🔥

# Descripcion General
<br>
El Tachomorfinador 62 es un sistema automatizado de dispensación de medicamentos, diseñado para administrar tanto jarabes líquidos como pastillas sólidas. El sistema está controlado mediante una interfaz gráfica y autenticación por RFID, e integra diversos sensores y actuadores para un funcionamiento preciso y seguro.


# Objetivos del Proyecto
<br>
- Automatizar la administración de medicamentos.
<br>
- Garantizar que cada paciente reciba su dosis correcta.
<br>
- Integrar tecnologías IoT para facilitar el monitoreo y control del dispensador.
<br>
- Ofrecer una solución funcional, segura y escalable para el entorno médico.

# Tecnologias utilizadas
| Categoría     | Tecnologías                                                                 |
|---------------|------------------------------------------------------------------------------|
| **Hardware**  | ESP32, RFID RC522, servomotores, bombas peristálticas, sensores de humedad, LEDs, pantalla TFT táctil |
| **Software**  | Arduino IDE, Thonny (Python para MQTT), PostgreSQL, Android Studio (Kotlin), Node.js con Express |
| **Protocolos**| MQTT, HTTP REST                                                              |
| **Otros**     | Impresión 3D                                                                 |


# Arquitectura del Sistema
<br>

# Tabla de Actuadores
| Nombre               | Descripción                              | Uso en el proyecto        | Imagen |
|----------------------|-------------------------------------------|----------------------------|--------|
| Servomotores         | Motores que abren compartimientos        | Dispensación de pastillas | ![image](https://github.com/user-attachments/assets/1b21659d-53d7-4b9e-a329-76e5268bbcb0) |
| Bombas peristálticas | Bombas para líquidos                     | Dispensación de jarabes   | ![image](https://github.com/user-attachments/assets/4f745527-b5a1-47a3-87c6-4e5f725ab461) |
| LEDs                 | Indicadores visuales                     | Estado de operación       | ![image](https://github.com/user-attachments/assets/cb0b8a95-2ec1-4be8-9d9b-fddad0b55fd3) |


# Tabla de sensores
| Nombre | Descripcion | Uso en el proyecto | Imagen |
|--------------|-----------|-----------|-----------|
|RFID RC522| Identificación por radiofrecuencia | Autenticación de pacientes | ![image](https://github.com/user-attachments/assets/002e70f3-e436-4943-931a-97413318eb89) |
|Sensor de humedad | Mide niveles de humedad | Seguridad del sistema | ![image](https://github.com/user-attachments/assets/19629866-1eaa-4263-93e8-4a4abe74b120) |

# Funcionalidad del Sistema
<br>
El paciente se autentica con una tarjeta RFID.

El sistema consulta la dosis programada.

El servomotor o bomba correspondiente dispensa el medicamento.

Se registra la acción en el historial.

LEDs indican el estado del proceso.


# Interfaz Grafica 
<br>

# Maqueta 
<br>

# Diagramas de las placas
<br>

# Bases de Datos y Almacenamiento 
<br>

![image](https://github.com/user-attachments/assets/6204e1f7-021d-461f-88ef-e11a5873fad2)

<br>

![image](https://github.com/user-attachments/assets/43573524-4fc0-41ce-b71b-8d77559f6a5f)

<br>

![image](https://github.com/user-attachments/assets/642df161-a0fc-46c0-99b9-fe6101d85bd1)




# Ejercicios de Clase 
https://drive.google.com/drive/folders/1gkQf6arO-RZu3aNoIe4QQNL3Rfe0vFYb?usp=sharing

# Coevaluacion 

https://github.com/roygro/IoT_Unidad3_InstrumentoEvaluacion/edit/main/README.md 

# Autores 

Juana Jaqueline Camarrillo Olaez
<br>
Jose Andres Gutierrez Vargas
<br>
Princes Rocio Guerrero Sánchez 
<br>
