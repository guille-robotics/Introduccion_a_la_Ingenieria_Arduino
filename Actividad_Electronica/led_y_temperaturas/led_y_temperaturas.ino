// ===============================
// CONTROL DE TEMPERATURA CON LEDs
// Azul  -> Frío
// Verde -> Ideal
// Rojo  -> Caliente
// ===============================

// Pines de los LEDs
const int ledAzul  = 2;
const int ledVerde = 3;
const int ledRojo  = 4;

int temperatura;   // Temperatura simulada (°C)

void setup() {
  // Configuración de pines
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Comunicación serial
  Serial.begin(9600);
  Serial.println("Simulacion de temperatura con LEDs");
}

void loop() {

  // Simulamos temperatura desde 18°C hasta 32°C
  for (temperatura = 18; temperatura <= 32; temperatura++) {

    // ----- LOGICA DE TEMPERATURA -----
    if (temperatura < 22) {
      // Rango FRÍO
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, LOW);

      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C -> FRIO (LED AZUL)");
    } 
    else if (temperatura >= 22 && temperatura < 28) {
      // Rango IDEAL
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledRojo, LOW);

      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C -> IDEAL (LED VERDE)");
    }
    else {
      // Rango CALIENTE
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);

      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C -> CALIENTE (LED ROJO)");
    }

    delay(600);  // Pausa para ver el cambio
  }

  Serial.println("-----------------------------");
}
