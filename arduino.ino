// Control de múltiples LEDs en Arduino
// Configuración de pines y LEDs

// Definición de pines - Protoboard 1
const int PIN_ROJO_1 = 2;    // 7 LEDs rojos
const int PIN_ROJO_2 = 3;    // 11 LEDs rojos  
const int PIN_BLANCO_1 = 4;  // LEDs blancos
const int PIN_BLANCO_2 = 5;  // LEDs blancos
const int PIN_VERDE_1 = 6;   // LEDs verdes
const int PIN_VERDE_2 = 7;   // LEDs verdes
const int PIN_ROJO_3 = 8;    // LEDs rojos

// Definición de pines - Protoboard 2
const int PIN_AZUL_1 = 9;    // 19 LEDs azules
const int PIN_AZUL_2 = 10;   // 15 LEDs azules

void setup() {
  // Configurar todos los pines como salidas - Protoboard 1
  pinMode(PIN_ROJO_1, OUTPUT);
  pinMode(PIN_ROJO_2, OUTPUT);
  pinMode(PIN_BLANCO_1, OUTPUT);
  pinMode(PIN_BLANCO_2, OUTPUT);
  pinMode(PIN_VERDE_1, OUTPUT);
  pinMode(PIN_VERDE_2, OUTPUT);
  pinMode(PIN_ROJO_3, OUTPUT);
  
  // Configurar pines como salidas - Protoboard 2
  pinMode(PIN_AZUL_1, OUTPUT);
  pinMode(PIN_AZUL_2, OUTPUT);
  
  // Inicializar comunicación serie para debugging
  Serial.begin(9600);
  Serial.println("Sistema de LEDs iniciado");
  
  // Prueba inicial - encender todos los LEDs por 2 segundos
  encenderTodos();
  delay(2000);
  apagarTodos();
  delay(1000);
}

void loop() {
  // Secuencia de prueba automática por colores
  
  // Encender LEDs rojos
  Serial.println("Encendiendo LEDs rojos");
  encenderRojos();
  delay(2000);
  
  // Encender LEDs blancos
  Serial.println("Encendiendo LEDs blancos");
  apagarTodos();
  encenderBlancos();
  delay(2000);
  
  // Encender LEDs verdes
  Serial.println("Encendiendo LEDs verdes");
  apagarTodos();
  encenderVerdes();
  delay(2000);
  
  // Encender LEDs azules
  Serial.println("Encendiendo LEDs azules");
  apagarTodos();
  encenderAzules();
  delay(2000);
  
  // Secuencia completa por protoboard
  Serial.println("Secuencia por protoboards");
  secuenciaPorProtoboard();
  
  // Secuencia alternada de todos los colores
  Serial.println("Secuencia alternada completa");
  apagarTodos();
  secuenciaAlternadaCompleta();
  
  // Efecto arcoíris
  Serial.println("Efecto arcoíris");
  efectoArcoiris();
  
  apagarTodos();
  delay(3000);
}

// Función para encender todos los LEDs
void encenderTodos() {
  // Protoboard 1
  digitalWrite(PIN_ROJO_1, HIGH);
  digitalWrite(PIN_ROJO_2, HIGH);
  digitalWrite(PIN_BLANCO_1, HIGH);
  digitalWrite(PIN_BLANCO_2, HIGH);
  digitalWrite(PIN_VERDE_1, HIGH);
  digitalWrite(PIN_VERDE_2, HIGH);
  digitalWrite(PIN_ROJO_3, HIGH);
  // Protoboard 2
  digitalWrite(PIN_AZUL_1, HIGH);
  digitalWrite(PIN_AZUL_2, HIGH);
}

// Función para apagar todos los LEDs
void apagarTodos() {
  // Protoboard 1
  digitalWrite(PIN_ROJO_1, LOW);
  digitalWrite(PIN_ROJO_2, LOW);
  digitalWrite(PIN_BLANCO_1, LOW);
  digitalWrite(PIN_BLANCO_2, LOW);
  digitalWrite(PIN_VERDE_1, LOW);
  digitalWrite(PIN_VERDE_2, LOW);
  digitalWrite(PIN_ROJO_3, LOW);
  // Protoboard 2
  digitalWrite(PIN_AZUL_1, LOW);
  digitalWrite(PIN_AZUL_2, LOW);
}

// Función para encender solo LEDs rojos
void encenderRojos() {
  digitalWrite(PIN_ROJO_1, HIGH);
  digitalWrite(PIN_ROJO_2, HIGH);
  digitalWrite(PIN_ROJO_3, HIGH);
}

// Función para encender solo LEDs blancos
void encenderBlancos() {
  digitalWrite(PIN_BLANCO_1, HIGH);
  digitalWrite(PIN_BLANCO_2, HIGH);
}

// Función para encender solo LEDs verdes
void encenderVerdes() {
  digitalWrite(PIN_VERDE_1, HIGH);
  digitalWrite(PIN_VERDE_2, HIGH);
}

// Función para encender solo LEDs azules
void encenderAzules() {
  digitalWrite(PIN_AZUL_1, HIGH);
  digitalWrite(PIN_AZUL_2, HIGH);
}

// Secuencia alternada de colores
void secuenciaAlternada() {
  for(int i = 0; i < 3; i++) {
    encenderRojos();
    delay(500);
    apagarTodos();
    
    encenderBlancos();
    delay(500);
    apagarTodos();
    
    encenderVerdes();
    delay(500);
    apagarTodos();
  }
}

// Secuencia alternada completa con azules
void secuenciaAlternadaCompleta() {
  for(int i = 0; i < 2; i++) {
    encenderRojos();
    delay(400);
    apagarTodos();
    
    encenderBlancos();
    delay(400);
    apagarTodos();
    
    encenderVerdes();
    delay(400);
    apagarTodos();
    
    encenderAzules();
    delay(400);
    apagarTodos();
  }
}

// Secuencia por protoboard
void secuenciaPorProtoboard() {
  Serial.println("Activando Protoboard 1");
  digitalWrite(PIN_ROJO_1, HIGH);
  digitalWrite(PIN_ROJO_2, HIGH);
  digitalWrite(PIN_BLANCO_1, HIGH);
  digitalWrite(PIN_BLANCO_2, HIGH);
  digitalWrite(PIN_VERDE_1, HIGH);
  digitalWrite(PIN_VERDE_2, HIGH);
  digitalWrite(PIN_ROJO_3, HIGH);
  delay(2000);
  
  apagarTodos();
  delay(500);
  
  Serial.println("Activando Protoboard 2");
  digitalWrite(PIN_AZUL_1, HIGH);
  digitalWrite(PIN_AZUL_2, HIGH);
  delay(2000);
  
  apagarTodos();
  delay(500);
}

// Efecto arcoíris (todos los colores en secuencia)
void efectoArcoiris() {
  // Rojo
  encenderRojos();
  delay(800);
  
  // Agregar blanco
  encenderBlancos();
  delay(800);
  
  // Cambiar a verde
  apagarTodos();
  encenderVerdes();
  delay(800);
  
  // Agregar azul
  encenderAzules();
  delay(800);
  
  // Todos los colores
  encenderTodos();
  delay(1500);
  
  apagarTodos();
}

// Efecto de parpadeo
void efectoParpadeo() {
  for(int i = 0; i < 5; i++) {
    encenderTodos();
    delay(200);
    apagarTodos();
    delay(200);
  }
}

// Función para control manual de un pin específico
void controlarPin(int pin, bool estado) {
  digitalWrite(pin, estado ? HIGH : LOW);
  Serial.print("Pin ");
  Serial.print(pin);
  Serial.println(estado ? " encendido" : " apagado");
}

// Función para secuencia personalizada
void secuenciaPersonalizada() {
  // Pin 2 (7 LEDs rojos)
  digitalWrite(PIN_ROJO_1, HIGH);
  delay(1000);
  
  // Pin 3 (11 LEDs rojos)
  digitalWrite(PIN_ROJO_2, HIGH);
  delay(1000);
  
  // Pines 4 y 5 (LEDs blancos)
  digitalWrite(PIN_BLANCO_1, HIGH);
  digitalWrite(PIN_BLANCO_2, HIGH);
  delay(1000);
  
  // Pines 6 y 7 (LEDs verdes)
  digitalWrite(PIN_VERDE_1, HIGH);
  digitalWrite(PIN_VERDE_2, HIGH);
  delay(1000);
  
  // Pin 8 (LEDs rojos)
  digitalWrite(PIN_ROJO_3, HIGH);
  delay(1000);
  
  // Mantener todo encendido
  delay(2000);
  
  // Apagar todo
  apagarTodos();
}