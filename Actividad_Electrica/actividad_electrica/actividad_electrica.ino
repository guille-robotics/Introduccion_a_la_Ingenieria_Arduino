/* =======================================================
   MEDIDOR DE CONSUMO ELÉCTRICO (SIMULACIÓN)

   - Potenciómetro simula la corriente consumida
   - Se muestra un dígito (0-9) en display de 7 segmentos
   - Tres LEDs indican nivel de consumo:
         Verde   : Bajo
         Amarillo: Medio
         Rojo    : Alto
   - Si el consumo es extremo, suena buzzer (sobrecarga)

   Hecho para Tinkercad / Arduino UNO
   ======================================================= */

/// ------- Pines -------
const int potPin = A0;

// Display 7 segmentos (cátodo común)
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

// LEDs
int ledVerde   = 9;
int ledAmarillo = 10;
int ledRojo    = 11;

// Buzzer activo
int buzzer = 12;

/// ------- Tabla de segmentos para dígitos 0–9 -------
/// Cada vector corresponde a {a,b,c,d,e,f,g}
byte digitos[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

/// ------- CONFIGURACIÓN -------
void setup() {

  // Pines display
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  // Pines LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Buzzer
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

/// ------- Función para mostrar un número --------
void mostrarDigito(int num) {
  for (int i = 0; i < 7; i++) {
    int pin = a + i;  // a,b,c,d,e,f,g están en orden 2–8
    digitalWrite(pin, digitos[num][i]);
  }
}

/// ------- LOOP PRINCIPAL -------
void loop() {

  // Leer potenciómetro (0–1023)
  int lectura = analogRead(potPin);

  // Convertir a dígito (0–9)
  int digito = map(lectura, 0, 1023, 0, 9);

  mostrarDigito(digito);

  // Mostrar en monitor serial
  Serial.print("Corriente simulada: ");
  Serial.print(lectura);
  Serial.print(" | Digito: ");
  Serial.println(digito);

  // ----------- LÓGICA DE NIVELES -----------

  // Nivel Bajo
  if (lectura < 350) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
    digitalWrite(buzzer, LOW);
  }

  // Nivel Medio
  else if (lectura < 700) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledRojo, LOW);
    digitalWrite(buzzer, LOW);
  }

  // Nivel Alto
  else if (lectura < 900) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);
    digitalWrite(buzzer, LOW);
  }

  // Sobrecarga
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);
    digitalWrite(buzzer, HIGH);  // ALERTA
  }

  delay(150);
}
