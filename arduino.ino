/*
 * MAPA RM POR ZONAS - 30 LEDs AGRUPADOS
 * 5 zonas geográficas × 6 LEDs cada una  
 * Control simplificado con Arduino UNO
 */

// PINES DE CONTROL POR ZONA (Control Grupal)
#define ZONA_NORTE 2      // 6 LEDs Rojos (Acceso Crítico)
#define ZONA_PONIENTE 3   // 6 LEDs Amarillos (Acceso Bajo)
#define ZONA_CENTRO 4     // 6 LEDs Verdes (Acceso Alto)  
#define ZONA_ORIENTE 5    // 6 LEDs Blancos (Acceso Medio-Alto)
#define ZONA_SUR 6        // 6 LEDs Azules (Acceso Medio)

// PINES ADICIONALES PARA CONTROL SUBDIVIDIDO (Opcional)
#define NORTE_GRUPO_A 7   // 3 LEDs Norte (Colina, Lampa, Tiltil)
#define NORTE_GRUPO_B 8   // 3 LEDs Norte (Melipilla, Quilicura, Curacaví)
#define SUR_GRUPO_A 9     // 3 LEDs Sur (La Florida, Puente Alto, San Bernardo)
#define SUR_GRUPO_B 10    // 3 LEDs Sur (El Bosque, La Pintana, Maipú Sur)

// ESTRUCTURA DE DATOS POR ZONA
struct ZonaGeografica {
  String nombre;
  String color;
  int pin_principal;
  int pin_grupo_a;    // Para control subdividido  
  int pin_grupo_b;    // Para control subdividido
  float tasa_promedio;
  int cantidad_leds;
  String nivel_acceso;
  String territorio;
};

// DEFINICIÓN DE LAS 5 ZONAS DE LA RM
ZonaGeografica zonas[5] = {
  {
    "NORTE", "ROJO", ZONA_NORTE, NORTE_GRUPO_A, NORTE_GRUPO_B,
    16.8, 6, "CRÍTICO",
    "Colina, Lampa, Tiltil, Melipilla, Quilicura, Curacaví"
  },
  {
    "PONIENTE", "AMARILLO", ZONA_PONIENTE, -1, -1,  
    32.4, 6, "BAJO",
    "Maipú, Pudahuel, E.Central, Cerrillos, Lo Prado, P.A.Cerda"
  },
  {
    "CENTRO", "VERDE", ZONA_CENTRO, -1, -1,
    78.6, 6, "ALTO", 
    "Santiago, Providencia, Recoleta, Independencia, Q.Normal, Renca"
  },
  {
    "ORIENTE", "BLANCO", ZONA_ORIENTE, -1, -1,
    67.2, 6, "MEDIO-ALTO",
    "Las Condes, Vitacura, Ñuñoa, La Reina, Peñalolén, Lo Barnechea"
  },
  {
    "SUR", "AZUL", ZONA_SUR, SUR_GRUPO_A, SUR_GRUPO_B,
    44.1, 6, "MEDIO",
    "La Florida, Puente Alto, San Bernardo, El Bosque, La Pintana, Maipú Sur"
  }
};

// VARIABLES DE CONTROL
int modo_actual = 0;
unsigned long ultimo_cambio = 0;
unsigned long ultimo_parpadeo = 0;
bool estado_parpadeo = false;
bool control_subdividido = false;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines principales de zona
  for(int i = 0; i < 5; i++) {
    pinMode(zonas[i].pin_principal, OUTPUT);
    digitalWrite(zonas[i].pin_principal, LOW);
    
    // Configurar pines de subgrupos si existen
    if(zonas[i].pin_grupo_a != -1) {
      pinMode(zonas[i].pin_grupo_a, OUTPUT);  
      digitalWrite(zonas[i].pin_grupo_a, LOW);
    }
    if(zonas[i].pin_grupo_b != -1) {
      pinMode(zonas[i].pin_grupo_b, OUTPUT);
      digitalWrite(zonas[i].pin_grupo_b, LOW);
    }
  }
  
  Serial.println("🗺️ === MAPA INTERACTIVO RM POR ZONAS ===");
  Serial.println("30 LEDs agrupados en 5 zonas geográficas");
  Serial.println("");
  Serial.println("COMANDOS PRINCIPALES:");
  Serial.println("1 - Mostrar todas las zonas");
  Serial.println("2 - Solo zonas críticas (parpadeo)");  
  Serial.println("3 - Animación geográfica secuencial");
  Serial.println("4 - Recorrido por criticidad");
  Serial.println("5 - Modo comparativo (mejor vs peor)");
  Serial.println("6 - Efecto 'ola' territorial");
  Serial.println("7 - Control subdividido (Norte/Sur)");
  Serial.println("8 - Estadísticas y resumen");
  Serial.println("9 - Modo automático (demo)");
  Serial.println("0 - Apagar todas las zonas");
  Serial.println("=====================================");
  
  mostrar_resumen_zonas();
}

void loop() {
  // Procesar comandos del usuario
  if (Serial.available() > 0) {
    char comando = Serial.read();
    ejecutar_comando(comando);
  }
  
  // Efectos continuos según modo activo
  switch(modo_actual) {
    case 2: efecto_parpadeo_criticas(); break;
    case 5: efecto_comparativo(); break; 
    case 9: modo_automatico(); break;
  }
  
  delay(100);
}

void ejecutar_comando(char cmd) {
  switch(cmd) {
    case '1':
      modo_actual = 1;
      encender_todas_zonas();
      Serial.println("→ Todas las zonas iluminadas");
      break;
      
    case '2':
      modo_actual = 2;
      Serial.println("→ Modo crítico: zonas con acceso < 30 parpadeando");
      break;
      
    case '3':
      modo_actual = 3;
      animacion_geografica_secuencial();
      break;
      
    case '4':
      modo_actual = 4;
      recorrido_por_criticidad();
      break;
      
    case '5':
      modo_actual = 5;
      Serial.println("→ Modo comparativo: alternando mejores vs peores");
      break;
      
    case '6':
      modo_actual = 6;
      efecto_ola_territorial();
      break;
      
    case '7':
      modo_actual = 7;
      activar_control_subdividido();
      break;
      
    case '8':
      mostrar_estadisticas_completas();
      break;
      
    case '9':
      modo_actual = 9;
      Serial.println("→ Modo automático iniciado (demo continuo)");
      ultimo_cambio = millis();
      break;
      
    case '0':
      modo_actual = 0;
      apagar_todas_zonas();
      Serial.println("→ Todas las zonas apagadas");
      break;
      
    default:
      Serial.println("❌ Comando no válido. Use números 0-9.");
  }
}

void encender_todas_zonas() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(zonas[i].pin_principal, HIGH);
  }
}

void apagar_todas_zonas() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(zonas[i].pin_principal, LOW);
    
    // Apagar también subgrupos si están activos
    if(zonas[i].pin_grupo_a != -1) {
      digitalWrite(zonas[i].pin_grupo_a, LOW);
    }
    if(zonas[i].pin_grupo_b != -1) {
      digitalWrite(zonas[i].pin_grupo_b, LOW);
    }
  }
  control_subdividido = false;
}

void encender_zona(int zona_id) {
  if(zona_id >= 0 && zona_id < 5) {
    digitalWrite(zonas[zona_id].pin_principal, HIGH);
  }
}

void apagar_zona(int zona_id) {
  if(zona_id >= 0 && zona_id < 5) {
    digitalWrite(zonas[zona_id].pin_principal, LOW);
  }
}

void efecto_parpadeo_criticas() {
  if(millis() - ultimo_parpadeo > 400) {
    estado_parpadeo = !estado_parpadeo;
    ultimo_parpadeo = millis();
    
    for(int i = 0; i < 5; i++) {
      if(zonas[i].tasa_promedio < 30) {
        // Zonas críticas parpadean
        digitalWrite(zonas[i].pin_principal, estado_parpadeo ? HIGH : LOW);
      } else {
        // Zonas normales permanecen encendidas
        digitalWrite(zonas[i].pin_principal, HIGH);
      }
    }
  }
}

void animacion_geografica_secuencial() {
  apagar_todas_zonas();
  delay(1000);
  
  // Secuencia geográfica: Norte → Oriente → Centro → Sur → Poniente
  int secuencia[] = {0, 3, 2, 4, 1}; // Índices de zonas
  String direccion[] = {"Norte", "Oriente", "Centro", "Sur", "Poniente"};
  
  Serial.println("🗺️ Recorrido geográfico de la Región Metropolitana:");
  
  for(int i = 0; i < 5; i++) {
    int zona_idx = secuencia[i];
    
    Serial.print("📍 Iluminando zona ");
    Serial.print(direccion[i]);
    Serial.print(" (");
    Serial.print(zonas[zona_idx].color);
    Serial.print(") - Acceso: ");
    Serial.println(zonas[zona_idx].nivel_acceso);
    
    encender_zona(zona_idx);
    delay(1800);
  }
  
  Serial.println("✅ Recorrido completado - Todas las zonas activas");
}

void recorrido_por_criticidad() {
  apagar_todas_zonas();
  delay(800);
  
  // Ordenar zonas por tasa de acceso (peor a mejor)
  int orden_criticidad[] = {0, 1, 4, 3, 2}; // Norte, Poniente, Sur, Oriente, Centro
  
  Serial.println("🚨 Activación por nivel de criticidad (peor → mejor):");
  
  for(int i = 0; i < 5; i++) {
    int zona_idx = orden_criticidad[i];
    
    Serial.print("⚡ Zona ");
    Serial.print(zonas[zona_idx].nombre);
    Serial.print(" - ");
    Serial.print(zonas[zona_idx].tasa_promedio);
    Serial.print(" centros/100k - ");
    Serial.println(zonas[zona_idx].nivel_acceso);
    
    encender_zona(zona_idx);
    delay(1200);
  }
  
  Serial.println("🎯 Visualización completa del gradiente de acceso");
}

void efecto_comparativo() {
  static unsigned long ultimo_efecto = 0;
  static int fase_comparativa = 0;
  
  if(millis() - ultimo_efecto > 2500) {
    apagar_todas_zonas();
    
    if(fase_comparativa == 0) {
      // Mostrar solo zonas críticas/bajas
      Serial.println("🔴 ZONAS CON ACCESO DEFICIENTE:");
      encender_zona(0); // Norte  
      encender_zona(1); // Poniente
      Serial.println("  Norte (16.8) + Poniente (32.4)");
      
    } else {
      // Mostrar solo zonas buenas/altas
      Serial.println("🟢 ZONAS CON BUEN ACCESO:");
      encender_zona(2); // Centro
      encender_zona(3); // Oriente  
      Serial.println("  Centro (78.6) + Oriente (67.2)");
    }
    
    fase_comparativa = (fase_comparativa + 1) % 2;
    ultimo_efecto = millis();
  }
}

void efecto_ola_territorial() {
  apagar_todas_zonas();
  delay(500);
  
  Serial.println("🌊 Efecto ola territorial:");
  
  // Ola que se expande desde el centro hacia afuera
  encender_zona(2); // Centro
  Serial.println("  Centro");
  delay(600);
  
  encender_zona(3); // Oriente  
  encender_zona(1); // Poniente
  Serial.println("  + Oriente + Poniente");
  delay(600);
  
  encender_zona(0); // Norte
  encender_zona(4); // Sur
  Serial.println("  + Norte + Sur");
  delay(800);
  
  // Efecto pulsante
  for(int pulso = 0; pulso < 3; pulso++) {
    apagar_todas_zonas();
    delay(300);
    encender_todas_zonas();
    delay(300);
  }
  
  Serial.println("🎆 Efecto ola completado");
}

void activar_control_subdividido() {
  control_subdividido = true;
  apagar_todas_zonas();
  
  Serial.println("🎛️ Control subdividido activado:");
  Serial.println("Zona Norte dividida en:");
  Serial.println("  Grupo A: Colina + Lampa + Tiltil");
  Serial.println("  Grupo B: Melipilla + Quilicura + Curacaví");
  
  // Demostrar control subdividido
  digitalWrite(NORTE_GRUPO_A, HIGH);
  delay(1000);
  digitalWrite(NORTE_GRUPO_B, HIGH);
  delay(1000);
  
  Serial.println("Zona Sur dividida en:");
  Serial.println("  Grupo A: La Florida + Puente Alto + San Bernardo");  
  Serial.println("  Grupo B: El Bosque + La Pintana + Maipú Sur");
  
  digitalWrite(SUR_GRUPO_A, HIGH);
  delay(1000);
  digitalWrite(SUR_GRUPO_B, HIGH);
  delay(1000);
  
  Serial.println("✅ Control granular demostrado");
}

void modo_automatico() {
  if(millis() - ultimo_cambio > 4500) {
    static int secuencia_auto = 1;
    
    Serial.print("🔄 Demo automático - Paso ");
    Serial.println(secuencia_auto);
    
    switch(secuencia_auto) {
      case 1: 
        encender_todas_zonas();
        Serial.println("   Panorama completo");
        break;
      case 2: 
        modo_actual = 2; // Críticas
        Serial.println("   Enfoque en zonas críticas");
        break;
      case 3: 
        animacion_geografica_secuencial();
        Serial.println("   Recorrido geográfico");
        break;
      case 4: 
        modo_actual = 5; // Comparativo
        Serial.println("   Comparación contrastante");
        break;
    }
    
    secuencia_auto = (secuencia_auto % 4) + 1;
    ultimo_cambio = millis();
  }
}

void mostrar_resumen_zonas() {
  Serial.println("\n📊 === RESUMEN POR ZONAS GEOGRÁFICAS ===");
  
  for(int i = 0; i < 5; i++) {
    Serial.print("🔸 ");
    Serial.print(zonas[i].nombre);
    Serial.print(" (");
    Serial.print(zonas[i].color);
    Serial.print("): ");
    Serial.print(zonas[i].tasa_promedio);
    Serial.print(" centros/100k - ");
    Serial.print(zonas[i].nivel_acceso);
    Serial.print(" - ");
    Serial.print(zonas[i].cantidad_leds);
    Serial.println(" LEDs");
  }
  
  Serial.println("\n🗺️ INTERPRETACIÓN:");
  Serial.println("🔴 Zona Norte: Acceso crítico, requiere intervención urgente");
  Serial.println("🟡 Zona Poniente: Acceso bajo, necesita mejoras"); 
  Serial.println("🔵 Zona Sur: Acceso medio, situación regular");
  Serial.println("⚪ Zona Oriente: Acceso medio-alto, situación favorable");
  Serial.println("🟢 Zona Centro: Acceso alto, buena cobertura");
  Serial.println("==========================================\n");
}

void mostrar_estadisticas_completas() {
  Serial.println("\n📈 === ESTADÍSTICAS DETALLADAS ===");
  Serial.println("Zona\t\tTasa/100k\tNivel\t\tTerritorios Incluidos");
  Serial.println("--------------------------------------------------------------------");
  
  for(int i = 0; i < 5; i++) {
    Serial.print(zonas[i].nombre);
    Serial.print("\t\t");
    Serial.print(zonas[i].tasa_promedio);
    Serial.print("\t\t");
    Serial.print(zonas[i].nivel_acceso);
    Serial.print("\t");
    Serial.println(zonas[i].territorio);
  }
  
  // Calcular estadísticas generales
  float promedio_rm = 0;
  for(int i = 0; i < 5; i++) {
    promedio_rm += zonas[i].tasa_promedio;
  }
  promedio_rm /= 5;
  
  Serial.println("--------------------------------------------------------------------");
  Serial.print("PROMEDIO RM: ");
  Serial.print(promedio_rm);
  Serial.println(" centros/100k habitantes");
  Serial.println("BRECHA MÁXIMA: ");
  Serial.print(zonas[2].tasa_promedio - zonas[0].tasa_promedio);
  Serial.println(" centros/100k (Centro vs Norte)");
  Serial.println("==========================================\n");
}