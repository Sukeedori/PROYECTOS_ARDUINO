// Notas de la melodía extraídas de Miku.mxl
int melody[] = {
  NOTE_Db4, NOTE_F4, NOTE_Ab4, NOTE_Db3, NOTE_C3, // Primeras notas
  NOTE_B3, NOTE_B2, NOTE_F4, NOTE_F5, NOTE_A4, // Continuación de las notas
  NOTE_C4, NOTE_A3 // Puedes agregar más notas aquí según sea necesario
};

// Duraciones de las notas: 4 = negra, 8 = corchea, etc.
int noteDurations[] = {
  8, 8, 8, 8, 8,   // Corcheas
  4, 4, 4, 8, 4,   // Notas negras y corcheas
  8, 8              // Ajusta las duraciones según la partitura
};

void setup() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(13, melody[thisNote], noteDuration); // Reproduce la nota en el pin 13
    int pauseBetweenNotes = noteDuration * 1.30; // Pausa entre notas
    delay(pauseBetweenNotes);
    noTone(13); // Apaga el sonido antes de tocar la siguiente nota
  }
}

void loop() {
  // No se necesita hacer nada en el loop, la melodía se toca una vez en el setup
}
