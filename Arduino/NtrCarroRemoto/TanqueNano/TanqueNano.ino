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

Servo servo1;
Servo servo2;
Servo servo3;

// Variables para las posiciones de los servos
int servo1Pos = 90;
int servo2Pos = 90;
int servo3Pos = 90;

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

  // Configuración de comunicación serial
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Sistema listo. Esperando comandos Bluetooth...");
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (Bluetooth.available()) {
    char command = Bluetooth.read();

    // Filtrar caracteres adicionales
    if (command == '\r' || command == '\n') {
      return; // Ignorar caracteres no deseados
    }

    Serial.print("Comando recibido: ");
    Serial.print(command);
    Serial.print(" (ASCII: ");
    Serial.print((int)command);
    Serial.println(")");

    // Procesar comandos
    switch (command) {
      case 'A': // Motor 1 hacia adelante
        rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
        break;
      case 'B': // Motor 1 hacia atrás
        rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
        break;
      case 'C': // Motor 2 hacia adelante
        rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
        break;
      case 'D': // Motor 2 hacia atrás
        rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
        break;
      case 'S': // Detener motores
        stopMotors();
        break;
      // Control de servos con botones para izquierda y derecha
      case 'X': // Servo 1 mover a la derecha
        servo1Pos = min(servo1Pos + 10, 180);
        servo1.write(servo1Pos);
        break;
      case 'x': // Servo 1 mover a la izquierda
        servo1Pos = max(servo1Pos - 10, 0);
        servo1.write(servo1Pos);
        break;
      case 'Y': // Servo 2 mover a la derecha
        servo2Pos = min(servo2Pos + 10, 180);
        servo2.write(servo2Pos);
        break;
      case 'y': // Servo 2 mover a la izquierda
        servo2Pos = max(servo2Pos - 10, 0);
        servo2.write(servo2Pos);
        break;
      case 'Z': // Servo 3 mover a la derecha
        servo3Pos = min(servo3Pos + 10, 180);
        servo3.write(servo3Pos);
        break;
      case 'z': // Servo 3 mover a la izquierda
        servo3Pos = max(servo3Pos - 10, 0);
        servo3.write(servo3Pos);
        break;
      default:
        Serial.println("Comando no reconocido.");
        break;
    }
  }
}

void rotateStepper(int in1, int in2, int in3, int in4, int direction) {
  // Secuencia básica para el motor paso a paso (4 pasos)
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
    delay(10); // Ajustar para controlar la velocidad
  }
}

void stopMotors() {
  // Detener ambos motores
  digitalWrite(STEP1_IN1, LOW);
  digitalWrite(STEP1_IN2, LOW);
  digitalWrite(STEP1_IN3, LOW);
  digitalWrite(STEP1_IN4, LOW);

  digitalWrite(STEP2_IN1, LOW);
  digitalWrite(STEP2_IN2, LOW);
  digitalWrite(STEP2_IN3, LOW);
  digitalWrite(STEP2_IN4, LOW);
}
