// Definindo os pinos digitais que estão conectados aos LEDs
const int ledPin1 = 8;
const int ledPin2 = 7;
const int ledPin3 = 2;

void setup()
{
  // Configura os pinos digitais como saída
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{
  // Liga o primeiro LED
  digitalWrite(ledPin1, HIGH);
  delay(10); // Aguarda 0,5 segundo
  digitalWrite(ledPin1, LOW);
  delay(10); // Aguarda 0,5 segundo
  digitalWrite(ledPin2, HIGH);
  delay(10); // Aguarda 0,5 segundo
  digitalWrite(ledPin2, LOW);
  delay(10); // Aguarda 0,5 segundo
  digitalWrite(ledPin3, HIGH);
  delay(500); // Aguarda 0,5 segundo
  digitalWrite(ledPin3, LOW);
}