#include <WiFi.h>
#include <HTTPClient.h>

#define TRIG_PIN 5   // Pino Trig do HC-SR04
#define ECHO_PIN 18  // Pino Echo do HC-SR04

const char* ssid = "LAB-SI";            // Nome da rede WiFi
const char* password = "LAB@SI1010";    // Senha da rede WiFi
const char* serverName = "http://10.0.2.130:3000/data"; // URL da API

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034) / 2;  // Calcula a distância em cm
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
}

void loop() {
  float distance = getDistance();
  Serial.print("Distância: ");
  Serial.println(distance);

  // Enviar a distância para a API via HTTP POST
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    char jsonPayload[64];
    sprintf(jsonPayload, "{\"distancia\": %.2f}", distance);

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.println("Dados enviados com sucesso.");
    } else {
      Serial.println("Erro ao enviar dados para API.");
    }
    http.end();
  }

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}
