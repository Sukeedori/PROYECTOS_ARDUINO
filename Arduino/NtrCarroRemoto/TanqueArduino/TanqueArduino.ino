#include <Servo.h>

// Pines para motores paso a paso
#define STEP1_IN1 4 // Motor paso a paso 1 - Bobina 1
#define STEP1_IN2 5 // Motor paso a paso 1 - Bobina 2
#define STEP1_IN3 6 // Motor paso a paso 1 - Bobina 3
#define STEP1_IN4 7 // Motor paso a paso 1 - Bobina 4

#define STEP2_IN1 8  // Motor paso a paso 2 - Bobina 1
#define STEP2_IN2 9  // Motor paso a paso 2 - Bobina 2
#define STEP2_IN3 10 // Motor paso a paso 2 - Bobina 3
#define STEP2_IN4 11 // Motor paso a paso 2 - Bobina 4

// Pines para servomotores
#define SERVO1_PIN 12 // Servo 1: Control de subir/bajar la garra
#define SERVO2_PIN A0 // Servo 2: Apertura/cierre de la garra
#define SERVO3_PIN A1 // Servo 3: Movimiento del sensor ultrasónico

// Pines para el sensor ultrasónico
#define TRIG_PIN A2 // Pin TRIG del sensor ultrasónico
#define ECHO_PIN A3 // Pin ECHO del sensor ultrasónico

Servo servo1;
Servo servo2;
Servo servo3;

// Variables para las posiciones de los servos
int servo1Pos = 110; // Posición inicial de subir/bajar la garra
int servo2Pos = 65; // Posición inicial de apertura/cierre de la garra
int servo3Pos = 90; // Posición inicial del sensor ultrasónico

void setup() {
  // Configuración de pines para motores paso a paso
  pinMode(STEP1_IN1, OUTPUT);
  pinMode(STEP1_IN2, OUTPUT);
  pinMode(STEP1_IN3, OUTPUT);
  pinMode(STEP1_IN4, OUTPUT);

  pinMode(STEP2_IN1, OUTPUT);
  pinMode(STEP2_IN2, OUTPUT);
  pinMode(STEP2_IN3, OUTPUT);
  pinMode(STEP2_IN4, OUTPUT);

  // Configuración de servomotores
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  // Posicionar los servos en la posición inicial
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);

  // Configuración de pines del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuración de comunicación serial (para Bluetooth)
  Serial.begin(9600);
  Serial.println("Sistema listo en modo manual. Usa comandos Bluetooth para controlar.");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read(); // Leer comando desde Bluetooth
    handleManualMode(command);    // Manejar el comando
  }
}

void handleManualMode(char command) {
  switch (command) {
    case 'F': // Avanzar
      moveForward();
      break;
    case 'B': // Retroceder
      moveBackward();
      break;
    case 'L': // Girar a la izquierda
      turnLeft();
      break;
    case 'R': // Girar a la derecha
      turnRight();
      break;
    case 'S': // Detener motores
      stopMotors();
      break;
    case 'G': // Subir la garra
      servo1Pos = constrain(servo1Pos + 10, 0, 180);
      servo1.write(servo1Pos);
      break;
    case 'g': // Bajar la garra
      servo1Pos = constrain(servo1Pos - 10, 0, 180);
      servo1.write(servo1Pos);
      break;
    case 'O': // Abrir la garra
      servo2Pos = constrain(servo2Pos - 10, 0, 180);
      servo2.write(servo2Pos);
      break;
    case 'C': // Cerrar la garra
      servo2Pos = constrain(servo2Pos + 10, 0, 180);
      servo2.write(servo2Pos);
      break;
    case 'Z': // Mover sensor ultrasónico hacia la izquierda
      servo3Pos = constrain(servo3Pos - 10, 0, 180);
      servo3.write(servo3Pos);
      break;
    case 'X': // Mover sensor ultrasónico hacia la derecha
      servo3Pos = constrain(servo3Pos + 10, 0, 180);
      servo3.write(servo3Pos);
      break;
    default:
      Serial.println("Comando no reconocido.");
      break;
  }
}

// Función para mover hacia adelante
void moveForward() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
}

// Función para mover hacia atrás
void moveBackward() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
}

// Función para girar a la izquierda
void turnLeft() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
}

// Función para girar a la derecha
void turnRight() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
}

// Función para detener motores
void stopMotors() {
  digitalWrite(STEP1_IN1, LOW);
  digitalWrite(STEP1_IN2, LOW);
  digitalWrite(STEP1_IN3, LOW);
  digitalWrite(STEP1_IN4, LOW);

  digitalWrite(STEP2_IN1, LOW);
  digitalWrite(STEP2_IN2, LOW);
  digitalWrite(STEP2_IN3, LOW);
  digitalWrite(STEP2_IN4, LOW);
}

// Función para manejar los motores paso a paso
void rotateStepper(int in1, int in2, int in3, int in4, int direction) {
  int steps[4][4] = {
    {1, 0, 0, 1},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0}
  };

  for (int step = 0; step < 4; step++) {
    digitalWrite(in1, steps[step][0]);
    digitalWrite(in2, steps[step][1]);
    digitalWrite(in3, steps[step][2]);
    digitalWrite(in4, steps[step][3]);
    delay(5); // Reducir delay para aumentar velocidad
  }
}
