int buzzer = 12;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(buzzer, HIGH); // Suena
  delay(500);

  digitalWrite(buzzer, LOW);  // Silencio
  delay(500);
}
