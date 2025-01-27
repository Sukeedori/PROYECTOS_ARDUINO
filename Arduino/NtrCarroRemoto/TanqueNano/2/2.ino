#include <SoftwareSerial.h>

// Configuración del módulo Bluetooth en los pines D2 (RX) y D3 (TX)
SoftwareSerial bluetooth(2, 3);

// Pines del motor 1
const int motor1Pins[4] = {4, 5, 6, 7};  // A, B, C, D

// Pines del motor 2
const int motor2Pins[4] = {8, 9, 10, 11}; // A, B, C, D

// Secuencia de medio paso
const int halfStepSequence[8][4] = {
    {1, 0, 0, 0},  // A
    {1, 1, 0, 0},  // AB
    {0, 1, 0, 0},  // B
    {0, 1, 1, 0},  // BC
    {0, 0, 1, 0},  // C
    {0, 0, 1, 1},  // CD
    {0, 0, 0, 1},  // D
    {1, 0, 0, 1}   // DA
};

void setup() {
  // Inicializar Bluetooth y Monitor Serial
  bluetooth.begin(9600);
  Serial.begin(9600);

  // Configurar los pines de los motores como salida
  for (int i = 0; i < 4; i++) {
    pinMode(motor1Pins[i], OUTPUT);
    pinMode(motor2Pins[i], OUTPUT);
  }

  // Mensajes iniciales
  Serial.println("Motores configurados. Envíe comandos desde Bluetooth.");
  bluetooth.println("Conexión establecida. Use 'A', 'B', 'L', 'R' para controlar los motores.");
}

void loop() {
  // Leer comando desde Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read(); // Leer comando recibido
    Serial.print("Comando recibido: ");
    Serial.println(command);

    // Activar motores según el comando
    if (command == 'A') {  // Adelante
      Serial.println("Moviendo ambos motores hacia adelante.");
      moveMotors(1, 1, 3000); // Ambos motores hacia adelante por 3 segundos
    } else if (command == 'B') { // Atrás
      Serial.println("Moviendo ambos motores hacia atrás.");
      moveMotors(-1, -1, 3000); // Ambos motores hacia atrás por 3 segundos
    } else if (command == 'L') { // Izquierda
      Serial.println("Girando a la izquierda.");
      moveMotors(-1, 1, 3000); // Motor 1 atrás, Motor 2 adelante por 3 segundos
    } else if (command == 'R') { // Derecha
      Serial.println("Girando a la derecha.");
      moveMotors(1, -1, 3000); // Motor 1 adelante, Motor 2 atrás por 3 segundos
    } else {
      Serial.println("Comando no reconocido.");
      bluetooth.println("Comando no reconocido.");
    }
  }
}

// Función para mover los motores con secuencia de medio paso
void moveMotors(int dir1, int dir2, int durationMs) {
  unsigned long startTime = millis();

  while (millis() - startTime < durationMs) {
    for (int step = 0; step < 8; step++) {
      // Movimiento del motor 1
      for (int i = 0; i < 4; i++) {
        digitalWrite(motor1Pins[i], dir1 > 0 ? halfStepSequence[step][i] : halfStepSequence[7 - step][i]);
      }

      // Movimiento del motor 2
      for (int i = 0; i < 4; i++) {
        digitalWrite(motor2Pins[i], dir2 > 0 ? halfStepSequence[step][i] : halfStepSequence[7 - step][i]);
      }

      // Pausa entre pasos para controlar la velocidad
      delayMicroseconds(1000); // Ajustar según el comportamiento deseado
    }
  }

  // Apagar las bobinas después de finalizar
  for (int i = 0; i < 4; i++) {
    digitalWrite(motor1Pins[i], LOW);
    digitalWrite(motor2Pins[i], LOW);
  }
}
