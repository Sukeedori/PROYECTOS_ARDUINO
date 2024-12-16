#include <Servo.h>

// Servo1 0-50 sirve para manejar la garra 0 es abajo y 50 arriba
// Servo2 0-130 sirve para manejar la garra 0 abierto 130 cerrado
// Sirvo3 0-90-180  sirve para girar el sensor ultrasonico 0 es izquierda 90 frente y 190 a la derecha

// Pines para servomotores
#define SERVO1_PIN 12 // D12 en Arduino Nano
#define SERVO2_PIN A0 // A0 en Arduino Nano
#define SERVO3_PIN A1 // A1 en Arduino Nano

Servo servo1;
Servo servo2;
Servo servo3;

// Variables para las posiciones de los servos
int servo1Pos = 0;
int servo2Pos = 0;
int servo3Pos = 0;

void setup() {
  // Configuración de servomotores
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  // Posicionar los servos en la posición inicial
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);

  // Configuración de comunicación serial
  Serial.begin(9600);
  Serial.println("Sistema listo para calibración de servomotores.");
  Serial.println("Comandos disponibles:");
  Serial.println(" Servo 1: 'q' (izquierda), 'w' (derecha)");
  Serial.println(" Servo 2: 'a' (izquierda), 's' (derecha)");
  Serial.println(" Servo 3: 'z' (izquierda), 'x' (derecha)");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case 'q': // Mover Servo 1 a la izquierda
        servo1Pos = max(servo1Pos - 10, 0);
        servo1.write(servo1Pos);
        Serial.print("Servo 1 posición: ");
        Serial.println(servo1Pos);
        break;
      case 'w': // Mover Servo 1 a la derecha
        servo1Pos = min(servo1Pos + 10, 180);
        servo1.write(servo1Pos);
        Serial.print("Servo 1 posición: ");
        Serial.println(servo1Pos);
        break;
      case 'a': // Mover Servo 2 a la izquierda
        servo2Pos = max(servo2Pos - 10, 0);
        servo2.write(servo2Pos);
        Serial.print("Servo 2 posición: ");
        Serial.println(servo2Pos);
        break;
      case 's': // Mover Servo 2 a la derecha
        servo2Pos = min(servo2Pos + 10, 180);
        servo2.write(servo2Pos);
        Serial.print("Servo 2 posición: ");
        Serial.println(servo2Pos);
        break;
      case 'z': // Mover Servo 3 a la izquierda
        servo3Pos = max(servo3Pos - 10, 0);
        servo3.write(servo3Pos);
        Serial.print("Servo 3 posición: ");
        Serial.println(servo3Pos);
        break;
      case 'x': // Mover Servo 3 a la derecha
        servo3Pos = min(servo3Pos + 10, 180);
        servo3.write(servo3Pos);
        Serial.print("Servo 3 posición: ");
        Serial.println(servo3Pos);
        break;
      default:
        Serial.println("Comando no reconocido. Usa 'q', 'w', 'a', 's', 'z', 'x'.");
        break;
    }
  }
}
