#include <WiFi.h>
#include <PubSubClient.h>

// Configuración WiFi
const char* ssid = "Roy";
const char* password = "19020300";

// Configuración MQTT
const char* mqtt_server = "10.31.6.8";  // IP de tu broker local
const int mqtt_port = 1883;
const char* topic_valor = "tacho/sensor/agua";
const char* topic_estado = "tacho/sensor/estado";

WiFiClient espClient;
PubSubClient client(espClient);

// Pines
const int SENSOR_PIN = 34;
const int RED_PIN = 25;
const int GREEN_PIN = 26;
const int BLUE_PIN = 27;

unsigned long previousMillis = 0;
const long lecturaInterval = 5000;

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

  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect("SensorAguaClient")) {
      Serial.println("Conectado");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(". Intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Sistema de monitoreo de agua con MQTT iniciado");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= lecturaInterval) {
    previousMillis = currentMillis;

    int valorSensor = analogRead(SENSOR_PIN);
    Serial.print("Valor del sensor: ");
    Serial.println(valorSensor);

    client.publish(topic_valor, String(valorSensor).c_str());

    if (valorSensor > 2000) {
      setColor(false, true, false); // LED Verde
      Serial.println("Estado: Agua detectada");
      client.publish(topic_estado, "agua");
    } else {
      setColor(true, false, false); // LED Rojo
      Serial.println("Estado: ALERTA - No hay agua");
      client.publish(topic_estado, "alerta");
    }
  }
  delay(100);
}

void setColor(bool red, bool green, bool blue) {
  digitalWrite(RED_PIN, !red);
  digitalWrite(GREEN_PIN, !green);
  digitalWrite(BLUE_PIN, !blue);
}
