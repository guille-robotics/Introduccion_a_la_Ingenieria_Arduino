int potPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lectura = analogRead(potPin); // 0–1023

  //Serial.print("Valor del potenciómetro: ");
  Serial.println(lectura);

  delay(1000);
}
