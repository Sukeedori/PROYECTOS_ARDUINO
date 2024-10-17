// No tocar esta funcionando
const int NUM_LEDS = 5; 
const int leds[NUM_LEDS] = {8, 9, 10, 11, 12};
const int buttons[NUM_LEDS] = {2, 3, 4, 5, 6};
const int buzzer = 13;
const int debounceDelay = 50; // Tiempo de debounce en milisegundos

unsigned long lastDebounceTime[NUM_LEDS] = {0}; // Tiempo de la última pulsación registrada
bool lastButtonState[NUM_LEDS] = {HIGH}; // Estado anterior del botón

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
    digitalWrite(leds[i], HIGH); // Apaga los LEDs en el setup
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    int currentButtonState = digitalRead(buttons[i]);
    
    // Compara con el último estado para evitar rebotes
    if (currentButtonState != lastButtonState[i]) {
      // Reinicia el temporizador de debounce
      lastDebounceTime[i] = millis();
    }

    // Si ha pasado el tiempo de debounce, consideramos la pulsación válida
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (currentButtonState == LOW) {
        digitalWrite(leds[i], LOW); // Enciende el LED
        tone(buzzer, 261, 300); // Toca un tono de 261 Hz por 500 ms
        delay(1000); // Espera 2 segundos con el LED encendido
        digitalWrite(leds[i], HIGH); // Apaga el LED
      }
    }

    // Actualiza el estado anterior del botón
    lastButtonState[i] = currentButtonState;
  }
}
