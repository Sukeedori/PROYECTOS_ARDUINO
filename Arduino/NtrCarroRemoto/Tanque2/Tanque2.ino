#include <SoftwareSerial.h>
#include <Servo.h>

// Definición de pines del módulo Bluetooth
#define BT_RX 2
#define BT_TX 3

SoftwareSerial Bluetooth(BT_RX, BT_TX);

// Definición de pines para los motores paso a paso
#define STEP1_IN1 6
#define STEP1_IN2 7
#define STEP1_IN3 8
#define STEP1_IN4 9

#define STEP2_IN1 10
#define STEP2_IN2 11
#define STEP2_IN3 12
#define STEP2_IN4 13

// Definición de pines para los servomotores
Servo servo1;
Servo servo2;
#define SERVO1_PIN 4
#define SERVO2_PIN 5

// Definición de pines para el sensor ultrasónico
#define TRIG_PIN A0
#define ECHO_PIN A1

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

  // Configuración de servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  // Configuración de pines del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuración de comunicación serial
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Sistema listo. Esperando comandos Bluetooth...");
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (Bluetooth.available()) {
    char command = Bluetooth.read();
    Serial.print("Comando recibido: ");
    Serial.println(command);

    // Procesar comandos
    switch (command) {
      case '1': // Motor paso a paso 1, sentido horario
        rotateStepper(STEP1_IN1, STEP1_IN2, STEP1_IN3, STEP1_IN4, 1);
        break;
      case '2': // Motor paso a paso 2, sentido horario
        rotateStepper(STEP2_IN1, STEP2_IN2, STEP2_IN3, STEP2_IN4, 1);
        break;
      case 'P': // Leer sensor ultrasónico
        measureDistance();
        break;
      default:
        Serial.println("Comando no reconocido.");
        break;
    }
  }
}

// Función para mover un motor paso a paso
void rotateStepper(int in1, int in2, int in3, int in4, int direction) {
  const int steps[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
  };

  for (int step = 0; step < 8; step++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(in1, steps[(step + direction + 8) % 8][0]);
      digitalWrite(in2, steps[(step + direction + 8) % 8][1]);
      digitalWrite(in3, steps[(step + direction + 8) % 8][2]);
      digitalWrite(in4, steps[(step + direction + 8) % 8][3]);
    }
    delay(2); // Ajustar para velocidad
  }
}

// Función para medir la distancia con el sensor ultrasónico
void measureDistance() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular la distancia (en centímetros)
  distance = (duration / 2) / 29.1;

  // Mostrar la distancia medida
  Serial.print("Distancia medida: ");
  Serial.print(distance);
  Serial.println(" cm");
}
