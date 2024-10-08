// Programa para parpadear un LED conectado al pin 4 en Arduino

void setup() { // Esta función se ejecuta una vez al inicio
  pinMode(4, OUTPUT); // Configura el pin 4 como salida porque mi nombre es juan
}

void loop() { // Esta función se ejecuta en un bucle infinito
  digitalWrite(4, HIGH); // Enciende el LED conectado al pin 4
  delay(1000); // Espera 1000 milisegundos (1 segundo)
  
  digitalWrite(4, LOW); // Apaga el LED conectado al pin 4
  delay(1000); // Espera 1000 milisegundos (1 segundo)
}
