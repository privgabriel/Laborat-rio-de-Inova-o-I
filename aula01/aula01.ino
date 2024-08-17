// Definindo os pinos digitais que estão conectados aos LEDs
const int ledPin1 = 8;

void setup() {
  // Configura os pinos digitais como saída
  pinMode(ledPin1, OUTPUT);
}

void loop() {
  // Liga o primeiro LED
  digitalWrite(ledPin1, HIGH);
  delay(500); // Aguarda 0,5 segundo
  digitalWrite(ledPin1, LOW);
}