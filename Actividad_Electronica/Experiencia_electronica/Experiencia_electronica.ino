/* ==============================================================
   ESTACIÓN METEOROLÓGICA INTERACTIVA 
   - Sensor DHT11: Temperatura y Humedad
   - Sensor ultrasónico HC-SR04: Distancia
   - Indicadores: Servo + LEDs + Buzzer pasivo

   
   ============================================================== */

#include <DHT.h>
#include <Servo.h>

/// ------------------------------------------------
/// CONFIGURACIÓN DE SENSORES
/// ------------------------------------------------
#define DHTPIN 2              // Pin de datos del DHT11
#define DHTTYPE DHT11         // Tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

#define TRIG 3                // Trigger HC-SR04
#define ECHO 4                // Echo HC-SR04

/// ------------------------------------------------
/// ACTUADORES
/// ------------------------------------------------
Servo servoTemp;              // Servo indicador de temperatura

int ledAzul     = 5;          // Frío
int ledVerde    = 6;          // Normal
int ledAmarillo = 7;          // Cálido
int ledRojo     = 8;          // Caliente

int buzzer   = 9;             // Buzzer pasivo
int pinServo = 10;            // Pin del servo

/// ------------------------------------------------
/// FUNCIÓN: MEDIR DISTANCIA HC-SR04
/// ------------------------------------------------
long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Timeout de 30 ms para evitar bloqueos
  long duracion = pulseIn(ECHO, HIGH, 30000);

  // Conversión a centímetros
  long distancia = duracion * 0.034 / 2;

  return distancia;
}

/// ------------------------------------------------
/// SETUP
/// ------------------------------------------------
void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  pinMode(buzzer, OUTPUT);

  servoTemp.attach(pinServo);
  servoTemp.write(0);

  Serial.println("Estación Meteorológica Interactiva (sin promedio móvil)");
}

/// ------------------------------------------------
/// LOOP PRINCIPAL
/// ------------------------------------------------
void loop() {

  /// ---- LECTURA DE SENSORES ----
  float temp = dht.readTemperature();   // Temperatura en °C
  float hum  = dht.readHumidity();      // Humedad %
  long distancia = medirDistancia();    // Distancia en cm

  // Verificación de error del DHT
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error leyendo DHT11");
    delay(1000);
    return;
  }

  /// ---- MONITOR SERIAL ----
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Humedad: ");
  Serial.print(hum);
  Serial.print(" % | Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  /// ---- RESET DE ACTUADORES ----
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);
  noTone(buzzer);

  int anguloServo = 0;

  /// ------------------- FRÍO -------------------
  if (temp < 15) {
    digitalWrite(ledAzul, HIGH);
    tone(buzzer, 300);        // Tono grave
    anguloServo = 20;
  }

  /// ------------------ NORMAL ------------------
  else if (temp < 24) {
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 600);        // Tono medio
    anguloServo = 60;
  }

  /// ------------------ CÁLIDO ------------------
  else if (temp < 30) {
    digitalWrite(ledAmarillo, HIGH);
    tone(buzzer, 900);        // Tono agudo suave
    anguloServo = 110;
  }

  /// ------------------ CALIENTE ----------------
  else {
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 1200);       // Alarma
    anguloServo = 160;
  }

  // Mover servo según temperatura
  servoTemp.write(anguloServo);

  delay(500);   // Tiempo de actualización
}
