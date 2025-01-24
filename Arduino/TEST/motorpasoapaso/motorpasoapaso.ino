// Definición de pines para el primer motor
const int motor1_pin1 = 4;  // Motor 1 - IN1
const int motor1_pin2 = 5;  // Motor 1 - IN2
const int motor1_pin3 = 6;  // Motor 1 - IN3
const int motor1_pin4 = 7;  // Motor 1 - IN4

// Definición de pines para el segundo motor
const int motor2_pin1 = 8;  // Motor 2 - IN1
const int motor2_pin2 = 9;  // Motor 2 - IN2
const int motor2_pin3 = 10; // Motor 2 - IN3
const int motor2_pin4 = 11; // Motor 2 - IN4

// Variables para ambos motores
int velocidadMotor = 2000;  // Velocidad en microsegundos por paso
int contadorPasos1 = 0;     // Contador para motor 1
int contadorPasos2 = 0;     // Contador para motor 2
int pasosPorVuelta = 19300;  // Pasos para una vuelta completa

// Secuencia para media fase
const int cantidadPasos = 8;
const int tablaPasos[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup() {
  // Configurar pines como salida para ambos motores
  pinMode(motor1_pin1, OUTPUT);
  pinMode(motor1_pin2, OUTPUT);
  pinMode(motor1_pin3, OUTPUT);
  pinMode(motor1_pin4, OUTPUT);

  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);
  pinMode(motor2_pin3, OUTPUT);
  pinMode(motor2_pin4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Motores paso a paso en movimiento automático.");
}

void loop() {
  // Mover hacia adelante durante 10 segundos
  for (int i = 0; i < (10000000L / velocidadMotor); i++) {
    moverMotorHorario(1);
    moverMotorHorario(2);
    delayMicroseconds(velocidadMotor);
  }
  delay(500); // Pausa de 500 ms antes de cambiar de dirección

  // Mover hacia atrás durante 10 segundos
  for (int i = 0; i < (10000000L / velocidadMotor); i++) {
    moverMotorAntihorario(1);
    moverMotorAntihorario(2);
    delayMicroseconds(velocidadMotor);
  }
  delay(500); // Pausa de 500 ms antes de cambiar de dirección
}

void moverMotorHorario(int motor) {
  if (motor == 1) {
    contadorPasos1++;
    if (contadorPasos1 >= cantidadPasos) contadorPasos1 = 0;
    escribirSalidasMotor(1, contadorPasos1);
  } else if (motor == 2) {
    contadorPasos2++;
    if (contadorPasos2 >= cantidadPasos) contadorPasos2 = 0;
    escribirSalidasMotor(2, contadorPasos2);
  }
}

void moverMotorAntihorario(int motor) {
  if (motor == 1) {
    contadorPasos1--;
    if (contadorPasos1 < 0) contadorPasos1 = cantidadPasos - 1;
    escribirSalidasMotor(1, contadorPasos1);
  } else if (motor == 2) {
    contadorPasos2--;
    if (contadorPasos2 < 0) contadorPasos2 = cantidadPasos - 1;
    escribirSalidasMotor(2, contadorPasos2);
  }
}

void escribirSalidasMotor(int motor, int paso) {
  if (motor == 1) {
    digitalWrite(motor1_pin1, bitRead(tablaPasos[paso], 0));
    digitalWrite(motor1_pin2, bitRead(tablaPasos[paso], 1));
    digitalWrite(motor1_pin3, bitRead(tablaPasos[paso], 2));
    digitalWrite(motor1_pin4, bitRead(tablaPasos[paso], 3));
  } else if (motor == 2) {
    digitalWrite(motor2_pin1, bitRead(tablaPasos[paso], 0));
    digitalWrite(motor2_pin2, bitRead(tablaPasos[paso], 1));
    digitalWrite(motor2_pin3, bitRead(tablaPasos[paso], 2));
    digitalWrite(motor2_pin4, bitRead(tablaPasos[paso], 3));
  }
}
