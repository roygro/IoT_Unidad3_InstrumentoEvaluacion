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
|Sensor de agua | Mide niveles de humedad | Seguridad del sistema | ![image](https://github.com/user-attachments/assets/19629866-1eaa-4263-93e8-4a4abe74b120) |

# Funcionalidad del Sistema
<br>
El paciente se autentica con una tarjeta RFID.

El sistema consulta la dosis programada.

El servomotor o bomba correspondiente dispensa el medicamento.

Se registra la acción en el historial.

LEDs indican el estado del proceso.


# Interfaz Grafica 
<br>

![image](https://github.com/user-attachments/assets/403a0ebe-7794-4438-ae09-7b3a5cb1803b)


<br>

![image](https://github.com/user-attachments/assets/2d2088b6-3742-44bc-b8e3-ce2b61c8ff41)

<br>

![Imagen de WhatsApp 2025-04-29 a las 15 02 57_28cd0301](https://github.com/user-attachments/assets/5fbd26ef-7d7b-47f0-b283-2d9da11609a4)

<br>

![image](https://github.com/user-attachments/assets/9c6fbfbc-a7ee-400d-93c5-c1d05e72116b)






# Maqueta 
<br>

![Imagen de WhatsApp 2025-04-29 a las 16 58 48_8f592815](https://github.com/user-attachments/assets/add7e173-c7d8-4648-b56c-434ca69e9203)
<br>

![Imagen de WhatsApp 2025-04-29 a las 16 58 48_dbba274f](https://github.com/user-attachments/assets/d60a1229-0a0b-4705-a0c4-0a09388f5a34)
<br>

![Imagen de WhatsApp 2025-04-29 a las 16 58 48_644d7912](https://github.com/user-attachments/assets/3721eb54-55b6-4dfe-ada0-96b10ecbca86)
<br>

![Imagen de WhatsApp 2025-04-29 a las 16 58 48_2d42216f](https://github.com/user-attachments/assets/13577637-0858-45e6-8c35-3e2cf5690305)
<br>

![Imagen de WhatsApp 2025-04-29 a las 16 58 48_fc50af7d](https://github.com/user-attachments/assets/deff1816-5d12-4065-81d7-33ecc708237a)
<br>






# Diagramas de las placas
<br>


![image](https://github.com/user-attachments/assets/699ab7cf-b1e8-4673-9894-e127f4ef06fe)
<br>
https://app.cirkitdesigner.com/project/524df28d-17a4-4d42-8ff8-f6278b7e2e07

<br>

![image](https://github.com/user-attachments/assets/09116c59-474b-4316-8d04-b5b888f65aee)
<br>
https://app.cirkitdesigner.com/project/798a1c33-8ef0-47ed-80ed-8f71a19886e8

<br>

![image](https://github.com/user-attachments/assets/2db9a351-dd7a-4a3a-8afd-36d4deb3719d)

<br>
https://app.cirkitdesigner.com/project/4fc5dc96-468e-4d9d-bed5-134bb7744395




# Bases de Datos y Almacenamiento 
<br>

![image](https://github.com/user-attachments/assets/6204e1f7-021d-461f-88ef-e11a5873fad2)

<br>

![image](https://github.com/user-attachments/assets/43573524-4fc0-41ce-b71b-8d77559f6a5f)

<br>

![image](https://github.com/user-attachments/assets/642df161-a0fc-46c0-99b9-fe6101d85bd1)

<br>

![image](https://github.com/user-attachments/assets/a082f7b4-6466-4af0-89b6-0e044c240bfa)

<br>

![image](https://github.com/user-attachments/assets/7dab9c24-e544-4491-8cf2-c3714f931879)

<br>

![image](https://github.com/user-attachments/assets/cfc9d988-fda4-490a-8ce1-3442eb5e3bc9)





# Ejercicios de Clase 
https://drive.google.com/drive/folders/1gkQf6arO-RZu3aNoIe4QQNL3Rfe0vFYb?usp=sharing

# Coevaluacion 

https://docs.google.com/document/d/1JNbdgmP8gc3tPysofamoscSPRqMPaIEy5yJ789uDi5Q/edit?usp=sharing



# Aprobacion del proyecto
https://drive.google.com/file/d/1kuXvXRzVs7hb-csxIrKh6klvwPFE23-V/view?usp=drivesdk


# Autores 

Juana Jaqueline Camarrillo Olaez
<br>
Jose Andres Gutierrez Vargas
<br>
Princes Rocio Guerrero Sánchez 
<br>
