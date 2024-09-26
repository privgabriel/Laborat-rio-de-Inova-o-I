#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define TRIG_PIN 5   // Pino Trig do HC-SR04
#define ECHO_PIN 18  // Pino Echo do HC-SR04

const char* ssid = "LAB-SI";            // Coloque aqui o nome da sua rede WiFi
const char* password = "LAB@SI1010";       // Coloque aqui a senha da sua rede WiFi
const char* serverName = "http://TROCAR IP:3001/data"; // URL da API

BLECharacteristic *pCharacteristic;

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.034) / 2;  // Calcula a distância em cm
  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Inicializa BLE
  BLEDevice::init("ESP32_Distance_Sensor");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0xFFE0));

  pCharacteristic = pService->createCharacteristic(
                      BLEUUID((uint16_t)0xFFE1),
                      BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ 
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  pServer->getAdvertising()->start();
}

void loop() {
  float distance = getDistance();
  Serial.print("Distância: ");
  Serial.println(distance);

  // Enviar a distância via BLE
  char buffer[8];
  dtostrf(distance, 1, 2, buffer);
  pCharacteristic->setValue(buffer);
  pCharacteristic->notify();

  // Enviar a distância para a API via HTTP POST
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Cria o payload JSON com a distância
    String jsonPayload = "{\"distancia\": " + String(distance) + "}";

    // Envia o POSTWARNING: Category 'Sound' in library ESP_I2S is not valid. Setting to 'Uncategorized'
WARNING: Category 'Sensor' in library ESP_NOW is not valid. Setting to 'Uncategorized'
WARNING: Category 'Sound' in library ESP_SR is not valid. Setting to 'Uncategorized'
WARNING: Category '' in library ESP Insights is not valid. Setting to 'Uncategorized'
WARNING: Category '' in library ESP RainMaker is not valid. Setting to 'Uncategorized'
WARNING: Category '' in library TFLite Micro is not valid. Setting to 'Uncategorized'
WARNING: Category '' in library WiFiProv is not valid. Setting to 'Uncategorized'
Build options changed, rebuilding all
Sketch uses 1803289 bytes (137%) of program storage space. Maximum is 1310720 bytes.

Global variables use 60552 bytes (18%) of dynamic memory, leaving 267128 bytes for local variables. Maximum is 327680 bytes.
Sketch too big; see http://www.arduino.cc/en/Guide/Troubleshooting#size for tips on reducing it.
Error compiling for board ESP32 Dev Module.

    int httpResponseCode = http.POST(jsonPayload);

    // Verifica a resposta da API
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do servidor: " + response);
    } else {
      Serial.println("Erro ao enviar dados para API: " + String(httpResponseCode));
    }
    http.end();
  }

  delay(1000); // Atualiza a distância a cada 1 segundo
}
