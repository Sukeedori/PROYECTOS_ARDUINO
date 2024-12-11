#include <SoftwareSerial.h>

// Definición de pines del módulo Bluetooth
#define BT_RX 2
#define BT_TX 3

SoftwareSerial Bluetooth(BT_RX, BT_TX);

// Definición de pines para el motor
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

// Variable de control para el estado del motor
bool motorActivo = false;

void setup() {
  // Configurar pines del motor como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicializar pines en LOW
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Configurar comunicación serial
  Serial.begin(9600);      // Para depuración por USB
  Bluetooth.begin(9600);   // Configuración del módulo Bluetooth

  Serial.println("Esperando comandos Bluetooth...");
}

void loop() {
  // Leer y manejar comandos Bluetooth
  if (Bluetooth.available()) {
    char command = Bluetooth.read(); // Leer el comando
    Serial.print("Comando recibido: ");
    Serial.println(command);

    if (command == 'A') {
      Serial.println("Motor activado, girando en sentido horario...");
      motorActivo = true;
    } else if (command == 'S') {
      Serial.println("Motor detenido.");
      motorActivo = false;
      detenerMotor();
    } else {
      Serial.println("Comando no reconocido.");
    }
  }

  // Mover el motor si está activo
  if (motorActivo) {
    motorHorario();
  }
}

// Secuencia para girar el motor en sentido horario
void motorHorario() {
  digitalWrite(IN1, HIGH);
  delay(10);  // Velocidad del motor
  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH);
  delay(10);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  delay(10);
  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH);
  delay(10);
  digitalWrite(IN4, LOW);
}

// Secuencia para detener el motor
void detenerMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
