// Definición de pines
#define IN1  6  // Entrada IN1 del ULN2003AN conectada al pin D6 del Arduino
#define IN2  7  // Entrada IN2 del ULN2003AN conectada al pin D7 del Arduino
#define IN3  8  // Entrada IN3 del ULN2003AN conectada al pin D8 del Arduino
#define IN4  9  // Entrada IN4 del ULN2003AN conectada al pin D9 del Arduino

// Secuencia de pasos para controlar el motor de pasos 28BYJ-48
int stepSequence[8][4] = {
  {1, 0, 0, 0},  // Paso 1
  {1, 1, 0, 0},  // Paso 2
  {0, 1, 0, 0},  // Paso 3
  {0, 1, 1, 0},  // Paso 4
  {0, 0, 1, 0},  // Paso 5
  {0, 0, 1, 1},  // Paso 6
  {0, 0, 0, 1},  // Paso 7
  {1, 0, 0, 1}   // Paso 8
};

int currentStep = 0;  // Posición actual del motor (0-7)

void setup() {
  // Configurar los pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuración inicial de los pines en LOW
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.begin(9600); // Para depuración (opcional)
}

void loop() {
  // Girar varias revoluciones completas en sentido horario
  rotateSteps(2048 * 5, 1); // 2048 pasos por revolución, 5 revoluciones
  delay(1000);

  // Girar varias revoluciones completas en sentido antihorario
  rotateSteps(2048 * 5, -1); // 2048 pasos por revolución, 5 revoluciones
  delay(1000);

  // Gira indefinidamente en sentido horario (si deseas)
  // rotateIndefinitely(1);
}

// Función para controlar el motor paso a paso
void rotateSteps(int steps, int direction) {
  for (int i = 0; i < steps; i++) {
    // Activar el motor en el paso actual
    stepMotor(currentStep);

    // Actualizar la posición actual según la dirección
    if (direction == 1) { // Sentido horario
      currentStep++;
      if (currentStep > 7) currentStep = 0; // Reinicia si se pasa del último paso
    } else { // Sentido antihorario
      currentStep--;
      if (currentStep < 0) currentStep = 7; // Reinicia si se pasa del primer paso
    }

    // Retardo para ajustar la velocidad
    delay(2); // Ajusta este valor para cambiar la velocidad del motor
  }
}

// Función para activar las bobinas del motor en el paso actual
void stepMotor(int step) {
  digitalWrite(IN1, stepSequence[step][0]);
  digitalWrite(IN2, stepSequence[step][1]);
  digitalWrite(IN3, stepSequence[step][2]);
  digitalWrite(IN4, stepSequence[step][3]);
}

// Función para girar indefinidamente
void rotateIndefinitely(int direction) {
  while (true) {
    stepMotor(currentStep);

    if (direction == 1) { // Sentido horario
      currentStep++;
      if (currentStep > 7) currentStep = 0;
    } else { // Sentido antihorario
      currentStep--;
      if (currentStep < 0) currentStep = 7;
    }

    delay(2);
  }
}
m
