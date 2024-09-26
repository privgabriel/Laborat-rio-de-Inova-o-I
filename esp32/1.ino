#include <WiFi.h>

// Defina o nome e senha da sua rede Wi-Fi
const char* ssid = "Seu_SSID";
const char* password = "Sua_Senha";

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Inicia a conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi...");

  // Espera até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Tentando conectar...");
  }

  // Exibe o endereço IP atribuído ao ESP32
  Serial.println("Conectado com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // O loop pode ser usado para outras funcionalidades
}