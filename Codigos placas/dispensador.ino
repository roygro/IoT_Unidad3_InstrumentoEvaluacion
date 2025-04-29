#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Configuración WiFi
const char* ssid = "Roy";
const char* password = "19020300";

// Configuración MQTT
const char* mqtt_server = "10.31.6.8";
const int mqtt_port = 1883;
const char* topic_servo1 = "tacho/activacion/servo1";
const char* topic_servo2 = "tacho/activacion/servo2";
const char* topic_motor = "tacho/activacion/motorpaso";
const char* topic_status = "tacho/estado";

WiFiClient espClient;
PubSubClient client(espClient);

// Pines de servos
const int servo1Pin = 13;
const int servo2Pin = 12;

// Motor unipolar
const int motorPin1 = 14;
const int motorPin2 = 27;
const int motorPin3 = 26;
const int motorPin4 = 25;

// Servo
Servo servo1;
Servo servo2;

// Ángulos de servos
const int servo1_min = 0;    // Cerrado
const int servo1_max = 50;   // Abierto
const int servo2_min = 130;  // Abierto
const int servo2_max = 180;  // Cerrado

// Tiempos
const int calibration_delay = 2000;
const int movement_delay = 1000;
const int step_delay = 3;

// Secuencia motor paso a paso
const int step_sequence[4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

// Estado
bool automaticMode = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado");
      client.subscribe(topic_servo1);
      client.subscribe(topic_motor);
      client.subscribe("tacho/modo");
      client.publish(topic_status, "Sistema iniciado");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(". Intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }
  Serial.println(messageTemp);

  if (String(topic) == "tacho/modo") {
    if (messageTemp == "automatico") {
      automaticMode = true;
      client.publish(topic_status, "Modo automático activado");
    } else if (messageTemp == "manual") {
      automaticMode = false;
      client.publish(topic_status, "Modo manual activado");
    }
    return;
  }

  if (!automaticMode) {
    if (String(topic) == topic_servo1) {
      int command = messageTemp.toInt();
      
      if (command == 1) {
        // Abrir (dispensar)
        servo1.write(servo1_max);
        servo2.write(servo2_min);
        Serial.println("Servos abiertos (dispensar)");
        client.publish(topic_status, "Servos abiertos");
      } else if (command == 0) {
        // Cerrar (regresar)
        servo1.write(servo1_min);
        servo2.write(servo2_max);
        Serial.println("Servos cerrados (regresados)");
        client.publish(topic_status, "Servos cerrados");
      }
    } else if (String(topic) == topic_motor) {
      int steps = messageTemp.toInt();
      moverMotorPasos(steps);
      Serial.print("Motor movido: ");
      Serial.println(steps);
      client.publish("tacho/estado/motor", String(steps).c_str());
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando calibración de servos...");

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  servo1.attach(servo1Pin, 500, 2500);
  servo2.attach(servo2Pin, 500, 2500);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  servo1.write(servo1_min);
  servo2.write(servo2_max);
  delay(calibration_delay);

  Serial.println("Calibración completada. Sistema listo.");
  client.publish(topic_status, "Calibración completada");
}

void moverMotorPasos(int pasos) {
  Serial.print("Moviendo motor ");
  Serial.println(pasos);

  int direction = pasos > 0 ? 1 : -1;
  pasos = abs(pasos);

  for (int i = 0; i < pasos; i++) {
    for (int j = 0; j < 4; j++) {
      int idx = (direction > 0) ? j : (3 - j);
      
      digitalWrite(motorPin1, step_sequence[idx][0]);
      digitalWrite(motorPin2, step_sequence[idx][1]);
      digitalWrite(motorPin3, step_sequence[idx][2]);
      digitalWrite(motorPin4, step_sequence[idx][3]);
      
      delay(step_delay);
    }
  }

  digitalWrite(motorPin1, 0);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin3, 0);
  digitalWrite(motorPin4, 0);

  delay(movement_delay);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (automaticMode) {
    Serial.println("Modo automático: moviendo servos y motor...");

    servo1.write(servo1_min);
    servo2.write(servo2_max);
    client.publish(topic_status, "Posición inicial (automático)");
    delay(movement_delay);

    moverMotorPasos(50);
    client.publish(topic_status, "Motor adelante (automático)");

    servo1.write(servo1_max);
    servo2.write(servo2_min);
    client.publish(topic_status, "Posición entrega (automático)");
    delay(movement_delay);

    moverMotorPasos(-50);
    client.publish(topic_status, "Motor reversa (automático)");
  }

  delay(100);
}
