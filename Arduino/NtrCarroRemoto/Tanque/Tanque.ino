#include <Servo.h>
#include <SoftwareSerial.h>

// Bluetooth
#define BT_RX 2
#define BT_TX 3
SoftwareSerial Bluetooth(BT_RX, BT_TX);

// Motores DC para movimiento del tanque
#define MOTOR_LEFT_PWM 5
#define MOTOR_LEFT_DIR 4
#define MOTOR_RIGHT_PWM 6
#define MOTOR_RIGHT_DIR 7

// Servos
Servo servoUltrasonic;  // Servo para mover el sensor ultrasónico
Servo servoGarraUpDown; // Servo para subir/bajar la garra
Servo servoGarraOpenClose; // Servo para abrir/cerrar la garra

#define ULTRASONIC_TRIG 8
#define ULTRASONIC_ECHO 9

// Variables
bool modoAutomatico = false;

void setup() {
  // Configuración de motores DC
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);

  // Configuración de sensor ultrasónico
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);

  // Configuración de servos
  servoUltrasonic.attach(10); // Servo para sensor ultrasónico
  servoGarraUpDown.attach(11); // Servo para subir/bajar garra
  servoGarraOpenClose.attach(12); // Servo para abrir/cerrar garra

  // Posición inicial de los servos
  servoUltrasonic.write(90);
  servoGarraUpDown.write(90);
  servoGarraOpenClose.write(90);

  // Configuración de Bluetooth
  Serial.begin(9600);
  Bluetooth.begin(9600);

  Serial.println("Sistema listo. Esperando comandos...");
}

void loop() {
  if (Bluetooth.available()) {
    char command = Bluetooth.read();
    Serial.print("Comando recibido: ");
    Serial.println(command);

    switch (command) {
      case 'A': // Cambiar a modo automático
        Serial.println("Modo automático activado.");
        modoAutomatico = true;
        break;
      case 'M': // Cambiar a modo manual
        Serial.println("Modo manual activado.");
        modoAutomatico = false;
        detenerTanque();
        break;
      case 'F': // Avanzar
        if (!modoAutomatico) avanzar();
        break;
      case 'B': // Retroceder
        if (!modoAutomatico) retroceder();
        break;
      case 'L': // Girar izquierda
        if (!modoAutomatico) girarIzquierda();
        break;
      case 'R': // Girar derecha
        if (!modoAutomatico) girarDerecha();
        break;
      case 'U': // Subir la garra
        moverGarraVertical(180); // Posición arriba
        break;
      case 'D': // Bajar la garra
        moverGarraVertical(0); // Posición abajo
        break;
      case 'O': // Abrir la garra
        moverPinza(180); // Posición abierta
        break;
      case 'C': // Cerrar la garra
        moverPinza(0); // Posición cerrada
        break;
      default:
        Serial.println("Comando no reconocido.");
        break;
    }
  }

  if (modoAutomatico) {
    ejecutarModoAutomatico();
  }
}

// Funciones de movimiento del tanque
void avanzar() {
  analogWrite(MOTOR_LEFT_PWM, 255);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  analogWrite(MOTOR_RIGHT_PWM, 255);
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
}

void retroceder() {
  analogWrite(MOTOR_LEFT_PWM, 255);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
  analogWrite(MOTOR_RIGHT_PWM, 255);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}

void girarIzquierda() {
  analogWrite(MOTOR_LEFT_PWM, 255);
  digitalWrite(MOTOR_LEFT_DIR, LOW);
  analogWrite(MOTOR_RIGHT_PWM, 255);
  digitalWrite(MOTOR_RIGHT_DIR, HIGH);
}

void girarDerecha() {
  analogWrite(MOTOR_LEFT_PWM, 255);
  digitalWrite(MOTOR_LEFT_DIR, HIGH);
  analogWrite(MOTOR_RIGHT_PWM, 255);
  digitalWrite(MOTOR_RIGHT_DIR, LOW);
}

void detenerTanque() {
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_RIGHT_PWM, 0);
}

// Funciones para los servos
void moverGarraVertical(int angulo) {
  servoGarraUpDown.write(angulo);
}

void moverPinza(int angulo) {
  servoGarraOpenClose.write(angulo);
}

// Sensor ultrasónico
long medirDistancia() {
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);

  long duracion = pulseIn(ULTRASONIC_ECHO, HIGH);
  return duracion / 58; // Distancia en cm
}

// Modo automático
void ejecutarModoAutomatico() {
  avanzar();
  long distancia = medirDistancia();
  if (distancia < 20) { // Si hay un obstáculo
    detenerTanque();
    servoUltrasonic.write(0);  // Mirar a la izquierda
    delay(500);
    long izquierda = medirDistancia();

    servoUltrasonic.write(180); // Mirar a la derecha
    delay(500);
    long derecha = medirDistancia();

    servoUltrasonic.write(90); // Volver al frente
    delay(500);

    if (izquierda > derecha) {
      girarIzquierda();
    } else {
      girarDerecha();
    }
    delay(1000); // Tiempo para girar
    detenerTanque();
  }
}
