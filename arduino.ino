void setup() {
  Serial.begin(9600);
  Serial.println("=== PRUEBA 4 COMUNAS ===");
  
  // Configurar los 4 pines como salida
  pinMode(2, OUTPUT);   // Vitacura (LED verde)
  pinMode(5, OUTPUT);   // Santiago (LED amarillo)
  pinMode(6, OUTPUT);   // Ñuñoa (LED amarillo)
  pinMode(11, OUTPUT);  // Cerro Navia (LED rojo)
}

void loop() {
  Serial.println("Iniciando secuencia...");
  
  // 1. Vitacura (LED verde) - Excelente acceso
  Serial.println("Vitacura: Excelente acceso (95/100k)");
  digitalWrite(2, HIGH);
  delay(1500);
  digitalWrite(2, LOW);
  delay(500);
  
  // 2. Santiago (LED amarillo) - Acceso regular
  Serial.println("Santiago: Acceso regular (45/100k)");
  digitalWrite(5, HIGH);
  delay(1500);
  digitalWrite(5, LOW);
  delay(500);
  
  // 3. Ñuñoa (LED amarillo) - Acceso regular
  Serial.println("Ñuñoa: Acceso regular (38/100k)");
  digitalWrite(6, HIGH);
  delay(1500);
  digitalWrite(6, LOW);
  delay(500);
  
  // 4. Cerro Navia (LED rojo) - Acceso crítico (parpadeo)
  Serial.println("Cerro Navia: Acceso CRÍTICO (12/100k)");
  for(int i = 0; i < 5; i++) {
    digitalWrite(11, HIGH);
    delay(200);
    digitalWrite(11, LOW);
    delay(200);
  }
  
  Serial.println("--- Pausa antes de repetir ---");
  delay(2000);
}