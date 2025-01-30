#include <Servo.h>
#include <SoftwareSerial.h>

// Configuración del Bluetooth en los pines 2 (RX) y 3 (TX)
SoftwareSerial bluetooth(2, 3);

// Pines para motores paso a paso
#define STEP1_IN1 4
#define STEP1_IN2 5
#define STEP1_IN3 6
#define STEP1_IN4 7

#define STEP2_IN1 8
#define STEP2_IN2 9
#define STEP2_IN3 10
#define STEP2_IN4 11

// Pines para servomotores
#define SERVO1_PIN A0
#define SERVO2_PIN A1
#define SERVO3_PIN A2

// Pines para el sensor ultrasónico
#define TRIG_PIN A3
#define ECHO_PIN A4

Servo servo1, servo2, servo3;

// Variables de posición de los servos
int servo1PosInicial = 0, servo1PosFinal = 20;
int servo2PosInicial = 0, servo2PosFinal = 80;
int servo3Centro = 90, servo3Izquierda = 45, servo3Derecha = 135;

// Secuencia de 4 pasos para motores paso a paso
const int stepSequence[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

void setup() {
  // Eliminar Monitor Serial y Bluetooth para no activar TX
  // Serial.begin(9600);
  bluetooth.begin(9600);

  for (int i = 4; i <= 11; i++) pinMode(i, OUTPUT);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  servo1.write(servo1PosInicial);
  servo2.write(servo2PosInicial);
  servo3.write(servo3Centro);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();
    handleBluetoothCommand(command);
  }
}

// Función para manejar comandos Bluetooth
void handleBluetoothCommand(char command) {
  switch (command) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopMotors(); break;
    case 'G': servo1.write(servo1PosFinal); break;
    case 'g': servo1.write(servo1PosInicial); break;
    case 'O': servo2.write(servo2PosFinal); break;
    case 'C': servo2.write(servo2PosInicial); break;
    case 'Z': servo3.write(servo3Izquierda); break;
    case 'X': servo3.write(servo3Derecha); break;
    case 'M': servo3.write(servo3Centro); break;
    case 'D': medirDistancia(); break; // Mide distancia con el sensor ultrasónico
  }
}

// Funciones para mover motores paso a paso
void moveForward() { for (int i = 0; i < 100; i++) moveStepper(1, 1); }
void moveBackward() { for (int i = 0; i < 100; i++) moveStepper(-1, -1); }
void turnLeft() { for (int i = 0; i < 50; i++) moveStepper(-1, 1); }
void turnRight() { for (int i = 0; i < 50; i++) moveStepper(1, -1); }
void stopMotors() { for (int i = 4; i <= 11; i++) digitalWrite(i, LOW); }

// Función para mover motores sin usar TX
void moveStepper(int dir1, int dir2) {
  for (int step = 0; step < 4; step++) {
    int index1 = (dir1 > 0) ? step : (3 - step);
    int index2 = (dir2 > 0) ? step : (3 - step);
    for (int i = 0; i < 4; i++) {
      digitalWrite(STEP1_IN1 + i, stepSequence[index1][i]);
      digitalWrite(STEP2_IN1 + i, stepSequence[index2][i]);
    }
    delay(5);
  }
}

// Función para medir la distancia con el sensor ultrasónico sin activar TX
void medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  pulseIn(ECHO_PIN, HIGH);
}
