#include <Servo.h>

Servo indicador;   // Objeto servo

int temperatura;   // Temperatura simulada (°C)
int angulo;        // Ángulo del servo (°)

void setup() {
  indicador.attach(9);      // Servo conectado al pin 9
  Serial.begin(9600);       // Inicia comunicación serial
  Serial.println("Simulacion de temperatura iniciada");
}

void loop() {

  // Simulamos temperatura desde 20°C hasta 40°C
  for (temperatura = 20; temperatura <= 40; temperatura++) {

    // Mapeo de temperatura a ángulo
    // 20°C -> 0°
    // 40°C -> 180°
    angulo = map(temperatura, 20, 40, 0, 180);

    // Limitamos el ángulo por seguridad
    angulo = constrain(angulo, 0, 180);

    // Movemos el servo
    indicador.write(angulo);

    // ---- MONITOR SERIAL ----
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C  |  Angulo servo: ");
    Serial.print(angulo);
    Serial.println(" °");

    delay(500);  // Pausa para ver el movimiento y los datos
  }

  Serial.println("-----------------------------");
}
