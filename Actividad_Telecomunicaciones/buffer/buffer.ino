// ----- CONFIGURACIÓN -----
const int BTN_DATA = 3;      // Pin del botón para ingresar datos
const int MAX_BITS = 32;     // Límite de capacidad del buffer
char bufferBits[MAX_BITS];   // Arreglo (el buffer)
int bufferIndex = 0;         // Puntero de posición

// Variable para detectar una sola pulsación (flanco)
bool ultimoEstadoBtn = LOW; 

void setup() {
  // Nota: Se recomienda INPUT_PULLUP si el botón va a GND directamente
  pinMode(BTN_DATA, INPUT); 
  Serial.begin(9600);
  Serial.println("Sistema listo. Presione el boton para guardar un '1'.");
}

void loop() {
  // Leer el estado actual del botón
  bool estadoBtn = digitalRead(BTN_DATA);

  // LÓGICA DE DETECCIÓN: Solo entra si el botón se presiona (pasa de LOW a HIGH)
  if (estadoBtn == HIGH && ultimoEstadoBtn == LOW) {
    
    // 1. VERIFICAR ESPACIO (Seguridad de memoria)
    // Se eliminó 'bufferLleno' porque el índice ya nos indica el estado del buffer
    if (bufferIndex < MAX_BITS) {
      
      // 2. ASIGNACIÓN: Guardamos el bit en la posición actual
      bufferBits[bufferIndex] = '1'; 
      
      // 3. INCREMENTO: Movemos el puntero a la siguiente casilla
      bufferIndex++; 
      
      // FEEDBACK: Mostrar progreso por Serial
      Serial.print("Bit '1' almacenado en posicion: ");
      Serial.print(bufferIndex - 1); 
      Serial.print(" | Total bits: ");
      Serial.println(bufferIndex);
      
    } else {
      // ESTA ES LA SECCIÓN DE LIMPIEZA
      Serial.println("\n!! ERROR: Buffer lleno. No se puede guardar mas.");
      Serial.println("Se limpiara el Buffer automaticamente...");
      
      bufferIndex = 0; // Reiniciamos el contador a 0
      
      Serial.println("Buffer vacio. Listo para nuevos datos.\n");
    }
    
    delay(150); // Debounce para evitar falsos disparos
  }

  // Guardar el estado para la próxima vuelta del loop
  ultimoEstadoBtn = estadoBtn;
}