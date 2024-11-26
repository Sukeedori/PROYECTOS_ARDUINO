#include "pitches.h"

// Pin del buzzer
const int buzzerPin = 13;

// Notas de la canción
int melody[] = {
  // Parte 1
  NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_A5, NOTE_D5, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_A5, NOTE_D5, 
  NOTE_C4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, 
  NOTE_A5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_D5, 
  NOTE_C5, NOTE_A5, NOTE_D6, NOTE_C6, NOTE_D5, NOTE_A5, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_G5, 
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_A4, NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, 
  NOTE_A5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_F5, 
  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_A4, NOTE_A5, NOTE_G4, NOTE_C5, 

  // Parte 2
  NOTE_C5, NOTE_C5, NOTE_F5, NOTE_D5, NOTE_A4, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_C5, 
  NOTE_D6, NOTE_C5, NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, 
  NOTE_C5, NOTE_D6, NOTE_A5, NOTE_G4, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_F5, 
  NOTE_A5, NOTE_F5, NOTE_D6, NOTE_C5, NOTE_A4, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_C5, NOTE_E5, 
  NOTE_G5, NOTE_F5, NOTE_E5, NOTE_A5, NOTE_G4, NOTE_A4, NOTE_C6, NOTE_G5, NOTE_A5, NOTE_F5, 
  NOTE_D5, NOTE_G4, NOTE_C5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_A4, NOTE_F5, 
  NOTE_D6, NOTE_C5, NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_G5, NOTE_F5, NOTE_C5, NOTE_D5, 
  NOTE_A4, NOTE_A5, NOTE_G4, NOTE_F5, NOTE_D5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_A4, NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, NOTE_E5, 

  // Parte 3
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G4, NOTE_C6, NOTE_F5, NOTE_D5, NOTE_G5, NOTE_E5, NOTE_F5, 
  NOTE_D5, NOTE_G5, NOTE_F5, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_D5, NOTE_G4, 
  NOTE_F5, NOTE_D5, NOTE_C6, NOTE_F5, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_D6, NOTE_C5, 
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_D5, NOTE_F5, NOTE_E5, 
  NOTE_A5, NOTE_F5, NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, 
  NOTE_E5, NOTE_D5, NOTE_F5, NOTE_A4, NOTE_C5, NOTE_F5, NOTE_D6, NOTE_E5, NOTE_C6, NOTE_F5, 
  NOTE_A4, NOTE_G5, NOTE_D5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_D6, 
  NOTE_F5, NOTE_E5, NOTE_G4, NOTE_F5, NOTE_D5, NOTE_A4, NOTE_F5, NOTE_E5, NOTE_A5, NOTE_F5, 
  NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, NOTE_C5, NOTE_D6, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5
};

// Duraciones de las notas (4 = negra, 8 = corchea, etc.)
float noteDurations[] = {
  // Parte 1
  4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
  8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 
  8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 
  8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 
  8, 4, 8, 4, 8, 8, 8, 8, 8, 8, 
  8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 
  8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 
  8, 4, 8, 8, 4, 8, 8, 8, 8, 4, 

  // Parte 2
  8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 
  8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 
  8, 8, 4, 8, 8, 8, 4, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 
  8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 
  8, 4, 8, 4, 8, 8, 4, 8, 8, 8, 
  8, 4, 8, 8, 8, 4, 8, 8, 4, 8, 
  8, 8, 4, 8, 8, 8, 4, 8, 8, 8, 

  // Parte 3
  8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 
  8, 8, 4, 8, 8, 8, 8, 8, 4, 8, 
  8, 8, 4, 8, 8, 4, 8, 8, 8, 4, 
  8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 
  8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 
  8, 4, 8, 8, 8, 8, 4, 8, 8, 8, 
  8, 
};

// Función para reproducir la melodía
void playMelody(int *melody, float *noteDurations, int size) {
  for (int thisNote = 0; thisNote < size; thisNote++) {
    // Calcula la duración de la nota
    float duration = 1000 / noteDurations[thisNote];

    // Reproduce la nota en el buzzer conectado al pin 13
    tone(buzzerPin, melody[thisNote], duration);

    // Pausa entre las notas para que sean distinguibles
    float pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    // Apaga el buzzer antes de la siguiente nota
    noTone(buzzerPin);
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Configura el pin del buzzer como salida
}

void loop() {
  int melodySize = sizeof(melody) / sizeof(melody[0]);  // Calcula el tamaño de la melodía
  playMelody(melody, noteDurations, melodySize);        // Llama a la función para reproducir la melodía
  delay(2000);  // Pausa de 2 segundos antes de repetir la melodía
}
