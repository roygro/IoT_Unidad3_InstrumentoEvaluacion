#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

// Pines para motores (L298N)
const int ENA = 13;
const int IN1 = 12;
const int IN2 = 14;
const int ENB = 27;
const int IN3 = 26;
const int IN4 = 25;

// Pines para RFID RC522
#define RST_PIN  17
#define SS_PIN   5

// Configuración WiFi y MQTT
const char* ssid = "Roy";
const char* password = "19020300";
const char* mqtt_server = "10.31.6.8";
const int mqtt_port = 1883;

const char* topic_motor_A = "tacho/motorA";
const char* topic_motor_B = "tacho/motorB";
const char* topic_rfid = "tacho/rfid";

WiFiClient espClient;
PubSubClient client(espClient);
MFRC522 mfrc522(SS_PIN, RST_PIN);

// UID autorizado
byte uidAutorizado[] = {0xEB, 0x79, 0x00, 0x04};

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("ESP32Client_RFID")) {
      Serial.println("Conectado al servidor MQTT");
      client.subscribe(topic_motor_A);
      client.subscribe(topic_motor_B);
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(". Reintentando en 5 segundos");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  for (unsigned int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }

  Serial.print("Mensaje recibido en [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(messageTemp);

  if (String(topic) == topic_motor_A) {
    if (messageTemp == "1") {
      forwardMotor('A');
      client.publish("tacho/estado", "Motor A encendido");
    } else {
      stopMotor('A');
      client.publish("tacho/estado", "Motor A apagado");
    }
  }

  if (String(topic) == topic_motor_B) {
    if (messageTemp == "1") {
      forwardMotor('B');
      client.publish("tacho/estado", "Motor B encendido");
    } else {
      stopMotor('B');
      client.publish("tacho/estado", "Motor B apagado");
    }
  }
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor('A');
  stopMotor('B');

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Serial.println("Sistema listo. Acerca una tarjeta RFID...");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID detectado: ");
    String rfid_uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfid_uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(rfid_uid);

    if (memcmp(mfrc522.uid.uidByte, uidAutorizado, 4) == 0) {
      Serial.println("Acceso concedido.");
      client.publish(topic_rfid, rfid_uid.c_str());
    } else {
      Serial.println("Acceso denegado.");
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    delay(500);
  }
}

void forwardMotor(char motor) {
  if (motor == 'A') {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 150);
  } else if (motor == 'B') {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 150);
  }
}

void stopMotor(char motor) {
  if (motor == 'A') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  } else if (motor == 'B') {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}
