#include <SoftwareSerial.h>
#include <Servo.h>

// Configuración del módulo Bluetooth en los pines D2 (RX) y D3 (TX)
SoftwareSerial bluetooth(2, 3);

// Pines para los servos
const int servoPin1 = A0; // Subir y bajar
const int servoPin2 = A1; // Abrir y cerrar
const int servoPin3 = A2; // Izquierda, centro, derecha

// Variables de ángulos de los servos
int servo1Position = 180;  // Posición inicial (subir y bajar), rango: 10-25
int servo2Position = 90;  // Posición inicial (abrir y cerrar), rango: 0-105
int servo3Position = 180; // Posición inicial (izquierda, centro, derecha), rango: 0-180

// Objetos servo
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  // Inicializar Bluetooth y Monitor Serial
  bluetooth.begin(9600);
  Serial.begin(9600);

  // Configurar servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  // Establecer posiciones iniciales
  servo1.write(servo1Position);
  servo2.write(servo2Position);
  servo3.write(servo3Position);

  // Mensajes iniciales
  Serial.println("Sistema de control de servos listo. Envíe comandos desde Bluetooth.");
  bluetooth.println("Conexión establecida. Use comandos para controlar los servos.");
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read(); // Leer comando recibido
    Serial.print("Comando recibido: ");
    Serial.println(command);

    // Procesar el comando recibido y actualizar las posiciones
    switch (command) {
      case 'U': // Subir
        moveServo(servo1, servo1Position, 2, 10, 25, "Subiendo.");
        break;
      case 'D': // Bajar
        moveServo(servo1, servo1Position, -2, 10, 25, "Bajando.");
        break;
      case 'O': // Abrir
        moveServo(servo2, servo2Position, 2, 0, 105, "Abriendo.");
        break;
      case 'C': // Cerrar
        moveServo(servo2, servo2Position, -2, 0, 105, "Cerrando.");
        break;
      case 'I': // Izquierda
        moveServo(servo3, servo3Position, 2, 0, 180, "Moviendo a la izquierda.");
        break;
      case 'T': // Centro
        moveServoTo(servo3, servo3Position, 90, 0, 180, "Moviendo al centro.");
        break;
      case 'E': // Derecha
        moveServo(servo3, servo3Position, -2, 0, 180, "Moviendo a la derecha.");
        break;
      default:
        Serial.println("Comando no reconocido.");
        bluetooth.println("Comando no reconocido.");
        break;
    }
  }
}

// Función para mover el servo incrementando o disminuyendo su posición
void moveServo(Servo &servo, int &position, int delta, int minLimit, int maxLimit, const char *message) {
  // Calcular la nueva posición y restringirla dentro de los límites
  int newPosition = constrain(position + delta, minLimit, maxLimit);
  
  // Mover el servo a la nueva posición
  servo.write(newPosition);

  // Actualizar la posición guardada
  position = newPosition;

  // Imprimir mensaje
  Serial.println(message);
  bluetooth.println(message);
}

// Función para mover el servo directamente a una posición específica
void moveServoTo(Servo &servo, int &position, int targetPosition, int minLimit, int maxLimit, const char *message) {
  // Asegurar que la posición objetivo está dentro de los límites
  targetPosition = constrain(targetPosition, minLimit, maxLimit);
  
  // Mover el servo a la posición objetivo
  servo.write(targetPosition);

  // Actualizar la posición guardada
  position = targetPosition;

  // Imprimir mensaje
  Serial.println(message);
  bluetooth.println(message);
}
