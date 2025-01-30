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
#define SERVO1_PIN A0  // Subir/bajar la garra
#define SERVO2_PIN A1  // Abrir/cerrar la garra
#define SERVO3_PIN A2  // Mover sensor ultrasónico

// Pines para el sensor ultrasónico
#define TRIG_PIN A3
#define ECHO_PIN A4

Servo servo1;
Servo servo2;
Servo servo3;

// Variables de posición de los servos
int servo1PosInicial = 0;  // Posición inicial del Servo 1 (subir/bajar)
int servo1PosFinal = 20;   // Posición final del Servo 1

int servo2PosInicial = 0;  // Posición inicial del Servo 2 (abrir/cerrar)
int servo2PosFinal = 80;   // Posición final del Servo 2

int servo3Centro = 90;      // Posición central del sensor ultrasónico (Corregido)
int servo3Izquierda = 45;   // Posición izquierda del sensor
int servo3Derecha = 135;    // Posición derecha del sensor

// Secuencia de 4 pasos para motores paso a paso
const int stepSequence[4][4] = {
    {1, 0, 0, 0},  // Paso 1
    {0, 1, 0, 0},  // Paso 2
    {0, 0, 1, 0},  // Paso 3
    {0, 0, 0, 1}   // Paso 4
};

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Configurar pines de motores como salida
  for (int i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT);
  }

  // Configurar servomotores
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  // Posicionar los servos en la posición inicial
  servo1.write(servo1PosInicial);
  servo2.write(servo2PosInicial);
  servo3.write(servo3Centro);

  // Configuración del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Sistema listo. Controlar con Bluetooth.");
  bluetooth.println("Sistema listo. Envíe comandos para controlar.");
}

void loop() {
  // Verifica si hay datos desde Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read();
    Serial.print("Comando recibido: ");
    Serial.println(command);
    handleBluetoothCommand(command);
  }

  // Mide la distancia cada 1 segundo y la muestra en el Monitor Serial
  static unsigned long lastMeasureTime = 0;
  if (millis() - lastMeasureTime >= 1000) { 
    lastMeasureTime = millis();
    float distancia = medirDistancia();
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    bluetooth.print("Distancia: ");
    bluetooth.print(distancia);
    bluetooth.println(" cm");
  }
}

// Función para manejar los comandos Bluetooth
void handleBluetoothCommand(char command) {
  switch (command) {
    // Control de motores
    case 'F': moveForward(); break;  // Avanzar
    case 'B': moveBackward(); break; // Retroceder
    case 'L': turnLeft(); break;     // Girar a la izquierda
    case 'R': turnRight(); break;    // Girar a la derecha
    case 'S': stopMotors(); break;   // Detener motores

    // Control de servos
    case 'G': servo1.write(servo1PosFinal); break;  // Subir la garra
    case 'g': servo1.write(servo1PosInicial); break; // Bajar la garra
    case 'O': servo2.write(servo2PosFinal); break;  // Abrir la garra
    case 'C': servo2.write(servo2PosInicial); break; // Cerrar la garra
    case 'Z': servo3.write(servo3Izquierda); break; // Mover sensor a la izquierda
    case 'X': servo3.write(servo3Derecha); break;   // Mover sensor a la derecha
    case 'M': servo3.write(servo3Centro); break;    // Volver sensor al centro (Corregido)

    // Comando para obtener distancia manualmente
    case 'D': {
      float distancia = medirDistancia();
      Serial.print("Distancia: ");
      Serial.print(distancia);
      Serial.println(" cm");
      bluetooth.print("Distancia: ");
      bluetooth.print(distancia);
      bluetooth.println(" cm");
      break;
    }

    default:
      Serial.println("Comando no reconocido.");
      bluetooth.println("Comando no reconocido.");
      break;
  }
}

// Función para mover hacia adelante
void moveForward() {
  Serial.println("Moviendo hacia adelante.");
  for (int i = 0; i < 100; i++) {
    moveStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
    moveStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
  }
}

// Función para mover hacia atrás
void moveBackward() {
  Serial.println("Moviendo hacia atrás.");
  for (int i = 0; i < 100; i++) {
    moveStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
    moveStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
  }
}

// Función para girar a la izquierda
void turnLeft() {
  Serial.println("Girando a la izquierda.");
  for (int i = 0; i < 50; i++) {
    moveStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, -1);
    moveStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
  }
}

// Función para girar a la derecha
void turnRight() {
  Serial.println("Girando a la derecha.");
  for (int i = 0; i < 50; i++) {
    moveStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
    moveStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, -1);
  }
}

// Función para detener motores
void stopMotors() {
  Serial.println("Deteniendo motores.");
  for (int i = 4; i <= 11; i++) {
    digitalWrite(i, LOW);
  }
}

// Función para mover motores paso a paso con secuencia correcta
void moveStepper(int in1, int in2, int in3, int in4, int direction) {
  for (int step = 0; step < 4; step++) {
    int index = (direction > 0) ? step : (3 - step);
    digitalWrite(in1, stepSequence[index][0]);
    digitalWrite(in2, stepSequence[index][1]);
    digitalWrite(in3, stepSequence[index][2]);
    digitalWrite(in4, stepSequence[index][3]);
    delay(5); // Ajuste de velocidad
  }
}

// Función para medir la distancia con el sensor ultrasónico
float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;  // Conversión a cm
}
