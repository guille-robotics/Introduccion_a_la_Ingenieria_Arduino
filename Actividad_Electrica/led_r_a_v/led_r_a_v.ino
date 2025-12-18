int ledVerde = 9;
int ledAmarillo = 10;
int ledRojo = 11;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
}

void loop() {
  digitalWrite(ledVerde, HIGH);
  delay(700);
  digitalWrite(ledVerde, LOW);

  digitalWrite(ledAmarillo, HIGH);
  delay(700);
  digitalWrite(ledAmarillo, LOW);

  digitalWrite(ledRojo, HIGH);
  delay(700);
  digitalWrite(ledRojo, LOW);
}
