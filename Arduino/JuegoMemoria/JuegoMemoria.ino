/* 
Desarrollado por: Juan Jose Benites Coronel

positivo - boton - resitencia - negativo
*/
// Definición de pines y constantes
const int NUM_LEDS = 5;                // Número de LEDs y botones
const int MAX_SEQUENCE = 5;            // Secuencia máxima de LEDs
const int MIN_SEQUENCE = 2;            // Secuencia inicial de LEDs

// Pines para los LEDs
const int leds[NUM_LEDS] = {8, 9, 10, 11, 12};

// Pines para los botones
const int botones[NUM_LEDS] = {2, 3, 4, 5, 6};

// Pin para el buzzer
const int bocina = 13;

// Arreglo para almacenar la secuencia de botones
int seq[100];

// Variables de control del juego
int nivel = MIN_SEQUENCE;      // Nivel actual del juego (número de LEDs en la secuencia)
bool perder = false;           // Indicador de pérdida

void setup() {
  // Configurar pines de salida para LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW); // Asegura que todos los LEDs estén apagados al inicio
  }

  // Configurar pin de salida para el buzzer
  pinMode(bocina, OUTPUT);
  digitalWrite(bocina, LOW);     // Asegura que el buzzer esté apagado al inicio

  // Configurar pines de entrada para botones con resistencias internas de pull-up
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(botones[i], INPUT_PULLUP);
  }

  // Inicializar la semilla para números aleatorios
  randomSeed(analogRead(A0));

  // Generar la secuencia aleatoria completa al inicio
  generarSecuencia();

  // Esperar un momento antes de comenzar el juego
  delay(1000);
}

void loop() {
  // Mostrar la secuencia actual al jugador
  mostrarSecuencia();

  // Si el jugador no ha perdido, esperar su respuesta
  if (!perder) {
    obtenerRespuesta();
  }

  // Verificar si el jugador ha perdido
  if (perder) {
    perderJuego();
  } else {
    // Pausa breve entre rondas
    delay(500);
    nivel++; // Aumenta el nivel si el usuario acierta

    // Limitar el nivel al número máximo de LEDs disponibles
    if (nivel > MAX_SEQUENCE) {
      nivel = MAX_SEQUENCE;
    }

    // Si se alcanza el nivel máximo, opcionalmente puedes reiniciar o celebrar
    if (nivel == MAX_SEQUENCE) {
      celebrarVictoria();
      nivel = MIN_SEQUENCE; // Reiniciar el juego después de celebrar
    }
  }
}

// Función para generar una secuencia aleatoria
void generarSecuencia() {
  for (int i = 0; i < 100; i++) {
    seq[i] = random(0, NUM_LEDS); // Genera números aleatorios entre 0 y NUM_LEDS-1
  }
}

// Función para mostrar la secuencia de LEDs
void mostrarSecuencia() {
  for (int i = 0; i < nivel; i++) {
    int led = seq[i];                   // Obtiene el LED correspondiente
    digitalWrite(leds[led], HIGH);      // Enciende el LED
    delay(500);                          // Espera 500 ms
    digitalWrite(leds[led], LOW);        // Apaga el LED
    delay(300);                          // Pausa entre LEDs
  }
}

// Función para obtener y verificar la respuesta del jugador
void obtenerRespuesta() {
  for (int i = 0; i < nivel; i++) {
    bool botonCorrecto = false;
    while (!botonCorrecto) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (digitalRead(botones[j]) == LOW) { // Detecta si el botón está presionado
          // Debounce simple: espera hasta que el botón se suelte
          while (digitalRead(botones[j]) == LOW);
          delay(50); // Pequeña pausa para evitar rebotes

          // Enciende el LED correspondiente brevemente para dar feedback visual
          digitalWrite(leds[j], HIGH);
          delay(200);
          digitalWrite(leds[j], LOW);

          // Confirmación con sonido al presionar el botón
          tone(bocina, 500, 200);  // Sonido a 500 Hz durante 200 ms

          // Verifica si el botón presionado es el correcto
          if (j == seq[i]) {
            // Correcto: continúa con la siguiente parte de la secuencia
            botonCorrecto = true;
          } else {
            // Incorrecto: el jugador pierde
            perder = true;
            return;
          }
        }
      }
    }
  }
}

// Función para manejar la pérdida del jugador
void perderJuego() {
  // Activa el buzzer para indicar la pérdida
  tone(bocina, 1000, 2000); // Sonido de 2 segundos a 1000 Hz
  delay(2000);
  noTone(bocina);

  // Opcional: parpadea todos los LEDs para indicar pérdida
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(leds[j], HIGH);
    }
    delay(200);
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(leds[j], LOW);
    }
    delay(200);
  }

  // Reiniciar el juego
  generarSecuencia();        // Genera una nueva secuencia aleatoria
  nivel = MIN_SEQUENCE;      // Reinicia al nivel mínimo (2 LEDs)
  perder = false;            // Reinicia el indicador de pérdida
  delay(1000);               // Pausa antes de comenzar de nuevo
}

// Función opcional para celebrar la victoria al alcanzar el nivel máximo
void celebrarVictoria() {
  // Activa el buzzer con un tono de celebración
  tone(bocina, 1500, 1000); // Sonido de 1 segundo a 1500 Hz
  delay(1000);
  noTone(bocina);

  // Parpadea todos los LEDs varias veces para celebrar
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(leds[j], HIGH);
    }
    delay(200);
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(leds[j], LOW);
    }
    delay(200);
  }

  // Reiniciar el juego
  generarSecuencia();        // Genera una nueva secuencia aleatoria
  nivel = MIN_SEQUENCE;      // Reinicia al nivel mínimo (2 LEDs)
  delay(1000);               // Pausa antes de comenzar de nuevo
}
