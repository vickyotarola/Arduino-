void setup() {
  Serial.begin(9600);
  Serial.println("=== ZONA VERDE COMPLETA - 6 COMUNAS ===");
  
  // Configurar los 6 pines verdes (acceso excelente)
  pinMode(2, OUTPUT);  // Vitacura
  pinMode(3, OUTPUT);  // Providencia
  pinMode(4, OUTPUT);  // Las Condes
  pinMode(5, OUTPUT);  // Lo Barnechea
  pinMode(6, OUTPUT);  // La Reina
  pinMode(7, OUTPUT);  // Peñalolén
}

void loop() {
  // Modo 1: Encender una por una (de mayor a menor acceso)
  modoIndividualOrdenado();
  delay(2000);
  
  // Modo 2: Efecto de "ola" verde
  modoOlaVerde();
  delay(2000);
  
  // Modo 3: Todas juntas (zona privilegiada)
  modoZonaPrivilegiada();
  delay(3000);
}

void modoIndividualOrdenado() {
  Serial.println("=== ZONA VERDE: De mayor a menor acceso ===");
  apagarTodosVerdes();
  
  // Orden de mayor a menor acceso
  Serial.println("1. Vitacura: 95/100k - MÁXIMO");
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(300);
  
  Serial.println("2. Las Condes: 87/100k");
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(300);
  
  Serial.println("3. Providencia: 76/100k");
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(300);
  
  Serial.println("4. Lo Barnechea: 72/100k");
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  delay(300);
  
  Serial.println("5. La Reina: 58/100k");
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(300);
  
  Serial.println("6. Peñalolén: 52/100k");
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  delay(300);
}

void modoOlaVerde() {
  Serial.println("=== EFECTO OLA VERDE ===");
  apagarTodosVerdes();
  
  // Ola hacia adelante
  for(int i = 2; i <= 7; i++) {
    digitalWrite(i, HIGH);
    delay(200);
  }
  
  // Ola hacia atrás
  for(int i = 7; i >= 2; i--) {
    digitalWrite(i, LOW);
    delay(200);
  }
  
  // Repetir 2 veces más
  for(int rep = 0; rep < 2; rep++) {
    for(int i = 2; i <= 7; i++) {
      digitalWrite(i, HIGH);
      delay(150);
    }
    for(int i = 7; i >= 2; i--) {
      digitalWrite(i, LOW);
      delay(150);
    }
  }
}

void modoZonaPrivilegiada() {
  Serial.println("=== ZONA PRIVILEGIADA COMPLETA ===");
  
  // Encender todas las verdes juntas
  for(int i = 2; i <= 7; i++) {
    digitalWrite(i, HIGH);
  }
  
  Serial.println("ZONA ORIENTE: Acceso excelente a salud");
  Serial.println("Promedio zona: 73 centros/100k habitantes");
  Serial.println("Representa el PRIVILEGIO en acceso sanitario");
  
  delay(3000);
  
  // Efecto de "respiración" del privilegio
  for(int ciclo = 0; ciclo < 3; ciclo++) {
    // Apagar y encender rítmicamente
    apagarTodosVerdes();
    delay(300);
    for(int i = 2; i <= 7; i++) {
      digitalWrite(i, HIGH);
    }
    delay(700);
  }
  
  apagarTodosVerdes();
}

void apagarTodosVerdes() {
  for(int i = 2; i <= 7; i++) {
    digitalWrite(i, LOW);
  }
}