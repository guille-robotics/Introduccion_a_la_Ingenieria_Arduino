// ====== Pines del display (cátodo común) ======
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

// Tabla para formar los números (0–9)
// {a,b,c,d,e,f,g}  → 1 = encendido, 0 = apagado
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

void setup() {

Serial.begin(9600);
pinMode(a, OUTPUT);
pinMode(b, OUTPUT);
pinMode(c, OUTPUT);
pinMode(d, OUTPUT);
pinMode(e, OUTPUT);
pinMode(f, OUTPUT);
pinMode(g, OUTPUT);
}

void mostrarDigito(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(a + i, digitos[num][i]);
  }
}

void loop() {
  for (int n = 0; n < 10; n++) {
    mostrarDigito(n);
    Serial.print("Número: ");
    Serial.println(n);
    delay(1000);
  }
}
