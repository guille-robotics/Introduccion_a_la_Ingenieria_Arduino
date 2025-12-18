// ----- CONFIGURACIÓN -----
const int BTN_SEND = 3;      // Botón para iniciar la "graficación"
const int MAX_BITS = 32;     

// Inicialización correcta del buffer como un arreglo de caracteres
char bufferBits[MAX_BITS] = {'1','1','1','1','0','0','0','0','1','1','1','0','1','0','1','0'}; 

// IMPORTANTE: El índice debe ser igual a la cantidad de bits escritos arriba
int bufferIndex = 16;        

const int BIT_TIME = 500;    
bool ultimoBtnSend = LOW;

void setup() {
  pinMode(BTN_SEND, INPUT); // Resistencia Pull-Down externa
  Serial.begin(9600);
  
  Serial.println("--- MODO TEST: Mensaje predeterminado cargado ---");
  Serial.println("Abra el Serial Plotter y presione el boton de envio.");
}

void loop() {
  bool estadoSend = digitalRead(BTN_SEND);

  if (estadoSend == HIGH && ultimoBtnSend == LOW) {
    
    // Si el buffer tiene datos (index > 0)
    if (bufferIndex > 0) {
      
      Serial.println("\n>>> GRAFICANDO BUFFER...");
      
      for (int i = 0; i < bufferIndex; i++) {
        // El Plotter necesita que enviemos el número directamente
        if (bufferBits[i] == '1') {
          Serial.println(1); 
        } else {
          Serial.println(0); 
        }
        
        delay(BIT_TIME); 
      }
      
      // Línea de cierre en 0
      Serial.println(0);
      Serial.println(">>> FIN");
      
    }
  }

  ultimoBtnSend = estadoSend;
}