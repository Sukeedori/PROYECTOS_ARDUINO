#include <SoftwareSerial.h>
#include <Servo.h>

// Definición de pines del módulo Bluetooth
#define BT_RX 2 // D2 en Arduino Nano
#define BT_TX 3 // D3 en Arduino Nano

SoftwareSerial Bluetooth(BT_RX, BT_TX);

// Pines para motores paso a paso
#define STEP1_IN1 4 // D4 en Arduino Nano
#define STEP1_IN2 5 // D5 en Arduino Nano
#define STEP1_IN3 6 // D6 en Arduino Nano
#define STEP1_IN4 7 // D7 en Arduino Nano

#define STEP2_IN1 8  // D8 en Arduino Nano
#define STEP2_IN2 9  // D9 en Arduino Nano
#define STEP2_IN3 10 // D10 en Arduino Nano
#define STEP2_IN4 11 // D11 en Arduino Nano

// Pines para servomotores
#define SERVO1_PIN 12 // D12 en Arduino Nano
#define SERVO2_PIN A0 // A0 en Arduino Nano
#define SERVO3_PIN A1 // A1 en Arduino Nano

// Pines para el sensor ultrasónico
#define TRIG_PIN A2 // A2 en Arduino Nano
#define ECHO_PIN A3 // A3 en Arduino Nano

Servo servo1;
Servo servo2;
Servo servo3;

// Variables para las posiciones de los servos
int servo1Pos = 90;
int servo2Pos = 90;
int servo3Pos = 90;

// Modo de funcionamiento: 0 - Manual, 1 - Automático
int mode = 0;

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

  // Configuración de comunicación serial
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Sistema listo. Modo: Manual (presiona 'M' para cambiar a automático)");
}

void loop() {
  // Mostrar la distancia constantemente
  float distance = measureDistance();
  Serial.print("Distancia medida: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Cambiar modo de funcionamiento
  if (Bluetooth.available()) {
    char command = Bluetooth.read();

    if (command == 'M' || command == 'm') {
      mode = !mode;
      Serial.print("Modo cambiado a: ");
      Serial.println(mode == 0 ? "Manual" : "Automático");
    }

    if (mode == 0) {
      handleManualMode(command);
    }
  }

  if (mode == 1) {
    handleAutomaticMode(distance);
  }
}

void handleManualMode(char command) {
  switch (command) {
    case 'F': // Adelante
      moveForward();
      break;
    case 'B': // Atrás
      moveBackward();
      break;
    case 'L': // Izquierda
      turnLeft();
      break;
    case 'R': // Derecha
      turnRight();
      break;
    case 'S': // Detener
      stopMotors();
      break;
    case 'G': // Garra arriba
      servo1Pos = min(servo1Pos + 10, 50);
      servo1.write(servo1Pos);
      break;
    case 'g': // Garra abajo
      servo1Pos = max(servo1Pos - 10, 0);
      servo1.write(servo1Pos);
      break;
    case 'O': // Garra abrir
      servo2Pos = max(servo2Pos - 10, 0);
      servo2.write(servo2Pos);
      break;
    case 'C': // Garra cerrar
      servo2Pos = min(servo2Pos + 10, 130);
      servo2.write(servo2Pos);
      break;
    case 'Z': // Sensor izquierda
      servo3Pos = max(servo3Pos - 10, 0);
      servo3.write(servo3Pos);
      break;
    case 'X': // Sensor derecha
      servo3Pos = min(servo3Pos + 10, 180);
      servo3.write(servo3Pos);
      break;
    default:
      Serial.println("Comando no reconocido en modo manual.");
      break;
  }
}

void handleAutomaticMode(float distance) {
  // Mantener el servo del sensor ultrasónico al frente
  servo3.write(90);

  if (distance < 10) {
    stopMotors();
    delay(500);

    // Revisar a la izquierda
    servo3.write(0);
    delay(500);
    float leftDistance = measureDistance();

    // Revisar a la derecha
    servo3.write(180);
    delay(500);
    float rightDistance = measureDistance();

    // Volver al frente
    servo3.write(90);

    // Decidir la dirección
    if (leftDistance > rightDistance) {
      turnLeft();
      delay(500);
    } else if (rightDistance > leftDistance) {
      turnRight();
      delay(500);
    } else {
      // En caso de empate, girar de forma aleatoria
      if (random(0, 2) == 0) {
        turnLeft();
      } else {
        turnRight();
      }
      delay(500);
    }
  } else {
    moveForward();
  }
}

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void moveForward() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
}

void moveBackward() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
}

void turnLeft() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
}

void turnRight() {
  rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
  rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
}

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
