// =======================================
// SISTEMA BÁSICO DE COMUNICACIÓN DIGITAL
// 1 LED + 1 BUZZER + 3 BOTONES
//
// BTN_0    -> Agrega un bit '0' al buffer
// BTN_1    -> Agrega un bit '1' al buffer
// BTN_SEND -> Envía la secuencia almacenada
//
// El LED y el buzzer representan el bit:
//   '1' -> LED encendido + buzzer sonando
//   '0' -> LED apagado  + buzzer apagado
// =======================================


// ---------- BOTONES (ENTRADAS) ----------
// Se usan con INPUT_PULLUP:
// - Sin presionar: HIGH
// - Presionado:    LOW
const int BTN_0    = 2;   // Botón para escribir un 0
const int BTN_1    = 3;   // Botón para escribir un 1
const int BTN_SEND = 4;   // Botón para enviar la secuencia


// ---------- SALIDAS ----------
const int LED_DATA = 8;   // LED que representa el bit transmitido
const int BUZZER   = 9;   // Buzzer pasivo para acompañar el bit '1'


// ---------- PARÁMETROS DEL SISTEMA ----------
const int MAX_BITS  = 32;     // Tamaño máximo del mensaje
const int BIT_TIME  = 500;    // Duración de cada bit (ms)
const int BUZZ_FREQ = 1000;   // Frecuencia del buzzer (Hz)


// ---------- VARIABLES ----------
char bufferBits[MAX_BITS];    // Arreglo donde se guarda la secuencia
int bufferIndex = 0;          // Indica cuántos bits hay guardados

// Estados anteriores de los botones
// Se usan para detectar el "flanco" (cuando recién se presiona)
bool lastBtn0    = HIGH;
bool lastBtn1    = HIGH;
bool lastBtnSend = HIGH;


// =======================================
// SETUP
// =======================================
void setup() {

  // Configuración de botones con resistencia pull-up interna
  pinMode(BTN_0, INPUT_PULLUP);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_SEND, INPUT_PULLUP);

  // Configuración de salidas
  pinMode(LED_DATA, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Estado inicial seguro
  digitalWrite(LED_DATA, LOW);
  noTone(BUZZER);

  // Comunicación serial para depuración
  Serial.begin(9600);
  Serial.println("Sistema de comunicacion digital iniciado");
}


// =======================================
// LOOP PRINCIPAL
// =======================================
void loop() {
  // Se revisan continuamente los botones
  leerBotones();
}


// =======================================
// FUNCIONES
// =======================================

// Lee los botones y detecta cuando son presionados
void leerBotones() {

  // Lectura actual de cada botón
  bool btn0    = digitalRead(BTN_0);
  bool btn1    = digitalRead(BTN_1);
  bool btnSend = digitalRead(BTN_SEND);

  // Si BTN_0 fue presionado (flanco HIGH -> LOW)
  if (btn0 == LOW && lastBtn0 == HIGH) {
    agregarBit('0');     // Agrega un 0 al buffer
    delay(150);          // Anti-rebote simple
  }

  // Si BTN_1 fue presionado
  if (btn1 == LOW && lastBtn1 == HIGH) {
    agregarBit('1');     // Agrega un 1 al buffer
    delay(150);
  }

  // Si BTN_SEND fue presionado
  if (btnSend == LOW && lastBtnSend == HIGH) {
    transmitirBuffer(); // Envía la secuencia completa
    delay(200);
  }

  // Guardamos el estado actual para la próxima iteración
  lastBtn0    = btn0;
  lastBtn1    = btn1;
  lastBtnSend = btnSend;
}


// ---------------------------------------
// Agrega un bit ('0' o '1') al buffer
void agregarBit(char bit) {

  // Verifica que no se supere el tamaño máximo
  if (bufferIndex < MAX_BITS) {

    bufferBits[bufferIndex++] = bit;  // Guarda el bit y avanza el índice

    // Mensajes por Serial para seguimiento
    Serial.print("Bit agregado: ");
    Serial.println(bit);

    Serial.print("Buffer actual: ");
    for (int i = 0; i < bufferIndex; i++) {
      Serial.print(bufferBits[i]);
    }
    Serial.println();

  } else {
    // Buffer lleno
    Serial.println("Buffer lleno");
  }
}


// ---------------------------------------
// Transmite todos los bits almacenados
void transmitirBuffer() {

  // Si no hay bits, no se transmite nada
  if (bufferIndex == 0) {
    Serial.println("Buffer vacio, nada que transmitir");
    return;
  }

  // Muestra la secuencia completa
  Serial.print("Transmitiendo secuencia: ");
  for (int i = 0; i < bufferIndex; i++) {
    Serial.print(bufferBits[i]);
  }
  Serial.println();

  // Envío bit por bit
  for (int i = 0; i < bufferIndex; i++) {

    Serial.print("Bit enviado: ");
    Serial.println(bufferBits[i]);

    if (bufferBits[i] == '1') {
      // Bit 1 -> LED encendido y buzzer activo
      digitalWrite(LED_DATA, HIGH);
      tone(BUZZER, BUZZ_FREQ);
    } else {
      // Bit 0 -> LED apagado y buzzer apagado
      digitalWrite(LED_DATA, LOW);
      noTone(BUZZER);
    }

    delay(BIT_TIME);  // Tiempo de duración del bit
  }

  // Apaga todo al finalizar
  digitalWrite(LED_DATA, LOW);
  noTone(BUZZER);

  Serial.println("Fin de transmision\n");

  // Limpia el buffer para la próxima secuencia
  bufferIndex = 0;
}
