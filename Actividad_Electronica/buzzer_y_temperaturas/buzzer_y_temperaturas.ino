// =====================================
// CONTROL DE TEMPERATURA CON LEDs Y BUZZER
// =====================================

// Pines de los LEDs
const int ledAzul  = 2;
const int ledVerde = 3;
const int ledRojo  = 4;

// Pin del buzzer
const int buzzer = 5;

int temperatura;   // Temperatura simulada (°C)

void setup() {
  // Configuración de pines
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Comunicación serial
  Serial.begin(9600);
  Serial.println("Simulacion de temperatura con LEDs y buzzer");
}

void loop() {

  // Simulamos temperatura desde 18°C hasta 32°C
  for (temperatura = 18; temperatura <= 32; temperatura++) {

    if (temperatura < 22) {
      // ----- RANGO FRÍO -----
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, LOW);

      noTone(buzzer);  // Buzzer apagado

      Serial.print("Temp: ");
      Serial.print(temperatura);
      Serial.println(" °C -> FRIO | Buzzer OFF");
    } 
    else if (temperatura >= 22 && temperatura < 28) {
      // ----- RANGO IDEAL -----
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledRojo, LOW);

      // Beep lento
      tone(buzzer, 1000);   // 1 kHz
      delay(200);
      noTone(buzzer);

      Serial.print("Temp: ");
      Serial.print(temperatura);
      Serial.println(" °C -> IDEAL | Beep lento");
    }
    else {
      // ----- RANGO CALIENTE -----
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);

      // Beep rápido
      tone(buzzer, 2000);   // 2 kHz
      delay(80);
      noTone(buzzer);

      Serial.print("Temp: ");
      Serial.print(temperatura);
      Serial.println(" °C -> CALIENTE | Beep rapido");
    }

    delay(400);  // Pausa general entre temperaturas
  }

  Serial.println("-----------------------------");
}
