#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

// Define os pinos para o trigger e echo
#define PINO_TRIGGER 4
#define PINO_ECHO 5

// Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);

// Inicializa a tela LCD com endereço I2C 0x27, 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(); // Inicializa o LCD
  lcd.backlight(); // Ativa a luz de fundo do LCD
  lcd.print("Lendo dados..."); // Mensagem inicial

  // Configura os pinos
  pinMode(PINO_TRIGGER, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}

void loop() {
  // Lê as informações do sensor, em cm e polegadas
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  // Exibe informações no Serial Monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);

  // Exibe informações no LCD
  lcd.clear(); // Limpa o LCD
  lcd.setCursor(0, 0); // Define o cursor na coluna 0, linha 0
  lcd.print("Distancia:");
  lcd.setCursor(0, 1); // Define o cursor na coluna 0, linha 1
  lcd.print(cmMsec);
  lcd.print(" cm");

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
