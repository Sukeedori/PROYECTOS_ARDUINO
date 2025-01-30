#include <SoftwareSerial.h>
#include <Servo.h>

// Configuración del módulo Bluetooth en los pines D2 (RX) y D3 (TX)
SoftwareSerial bluetooth(2, 3);

// Pines del motor 1
const int motor1Pins[4] = {4, 5, 6, 7};  // A, B, C, D

// Pines del motor 2
const int motor2Pins[4] = {8, 9, 10, 11}; // A, B, C, D

// Pines para los servos
const int servoPin1 = 12; // Subir y bajar
const int servoPin2 = A1; // Abrir y cerrar
const int servoPin3 = A3; // Izquierda, centro, derecha

// Objetos servo
Servo servo1;
Servo servo2;
Servo servo3;

// Rango de movimiento para los servos
int servo1Position = 20; // Posición inicial (subir y bajar) rango: 10-25
int servo2Position = 100; // Posición inicial (abrir y cerrar) rango: 0-105
int servo3Position = 90; // Posición inicial (izquierda, centro, derecha) rango: 0-180

// Secuencia de medio paso para los motores
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

  // Configurar servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  // Establecer posiciones iniciales
  servo1.write(servo1Position);
  servo2.write(servo2Position);
  servo3.write(servo3Position);

  // Mensajes iniciales
  Serial.println("Sistema listo. Envíe comandos desde Bluetooth.");
  bluetooth.println("Conexión establecida. Use comandos para controlar motores y servos.");
}

void loop() {
  // Leer comando desde Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read(); // Leer comando recibido
    Serial.print("Comando recibido: ");
    Serial.println(command);

    // Activar motores según el comando
    if (command == 'A') {  // Adelante
      moveMotors(1, 1, 2000); // Ambos motores hacia adelante por 2 segundos
    } else if (command == 'B') { // Atrás
      moveMotors(-1, -1, 2000); // Ambos motores hacia atrás por 2 segundos
    } else if (command == 'L') { // Izquierda
      moveMotors(-1, 1, 2000); // Motor 1 atrás, Motor 2 adelante por 2 segundos
    } else if (command == 'R') { // Derecha
      moveMotors(1, -1, 2000); // Motor 1 adelante, Motor 2 atrás por 2 segundos
    } else if (command == 'U') { // Subir
      servo1Position = constrain(servo1Position + 5, 10, 25); // Restringir entre 10 y 25
      servo1.write(servo1Position);
      Serial.println("Subiendo.");
    } else if (command == 'D') { // Bajar
      servo1Position = constrain(servo1Position - 5, 10, 25); // Restringir entre 10 y 25
      servo1.write(servo1Position);
      Serial.println("Bajando.");
    } else if (command == 'O') { // Abrir
      gradualMove(servo2, servo2Position, servo2Position + 5, 0, 105); // Movimiento gradual para abrir
      servo2Position = constrain(servo2Position + 5, 0, 105);
      Serial.println("Abriendo.");
    } else if (command == 'C') { // Cerrar
      gradualMove(servo2, servo2Position, servo2Position - 5, 0, 105); // Movimiento gradual para cerrar
      servo2Position = constrain(servo2Position - 5, 0, 105);
      Serial.println("Cerrando.");
    } else if (command == 'I') { // Izquierda
      servo3Position = 178; // Posición izquierda
      servo3.write(servo3Position);
      Serial.println("Moviendo a la izquierda.");
    } else if (command == 'T') { // Centro
      servo3Position = 90; // Posición central
      servo3.write(servo3Position);
      Serial.println("Moviendo al centro.");
    } else if (command == 'E') { // Derecha
      servo3Position = 2; // Posición derecha
      servo3.write(servo3Position);
      Serial.println("Moviendo a la derecha.");
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

// Función para mover el servo gradualmente
void gradualMove(Servo &servo, int startPosition, int endPosition, int minLimit, int maxLimit) {
  if (endPosition > startPosition) {
    for (int pos = startPosition; pos <= constrain(endPosition, minLimit, maxLimit); pos++) {
      servo.write(pos);
      delay(15); // Ajustar la velocidad del movimiento
    }
  } else {
    for (int pos = startPosition; pos >= constrain(endPosition, minLimit, maxLimit); pos--) {
      servo.write(pos);
      delay(15); // Ajustar la velocidad del movimiento
    }
  }
}
