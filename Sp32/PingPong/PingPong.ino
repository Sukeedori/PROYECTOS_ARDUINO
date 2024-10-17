// Definición de pines
const int pulsadorIzq = 2;    // Pulsador del jugador izquierdo
const int pulsadorDer = 3;    // Pulsador del jugador derecho
const int bocina = 13;         // Bocina que sonará cuando la bola llegue al LED 8 o 12

// Pines para los LEDs
const int leds[] = {12, 11, 10, 9, 8};

// Variables de juego
int posicionBola = -1;         // La posición inicial de la bola será definida por el jugador que presione primero
int direccion = 0;             // La dirección será determinada cuando un jugador presione su botón

void setup() {
  // Configurar pines de los pulsadores
  pinMode(pulsadorIzq, INPUT);
  pinMode(pulsadorDer, INPUT);
  
  // Configurar pines de los LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Configurar el pin de la bocina
  pinMode(bocina, OUTPUT);

  // Apagar la bocina inicialmente
  noTone(bocina);

  // Apagar todos los LEDs al inicio
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  // Leer el estado de los pulsadores
  int estadoIzq = digitalRead(pulsadorIzq);
  int estadoDer = digitalRead(pulsadorDer);

  // Si el juego no ha comenzado (posiciónBola = -1), esperar que un jugador presione su botón para iniciar
  if (posicionBola == -1) {
    if (estadoIzq == HIGH) {
      // Si el jugador izquierdo presiona primero, la bola empieza en el extremo izquierdo (LED 12)
      posicionBola = 0;
      direccion = 1;  // La bola irá hacia la derecha
      digitalWrite(leds[posicionBola], HIGH);  // Encender el LED inicial
    } else if (estadoDer == HIGH) {
      // Si el jugador derecho presiona primero, la bola empieza en el extremo derecho (LED 8)
      posicionBola = 4;
      direccion = -1; // La bola irá hacia la izquierda
      digitalWrite(leds[posicionBola], HIGH);  // Encender el LED inicial
    }
    return;  // Esperar hasta que un jugador presione su botón
  }

  // Apagar el LED actual antes de mover la bola
  digitalWrite(leds[posicionBola], LOW);

  // Cambiar la dirección de la bola si llega a un extremo y el jugador correspondiente presiona su botón
  if (posicionBola == 0 && estadoIzq == HIGH) {
    direccion = 1;  // Rebotar hacia la derecha si el jugador izquierdo presiona el botón
  } 
  if (posicionBola == 4 && estadoDer == HIGH) {
    direccion = -1; // Rebotar hacia la izquierda si el jugador derecho presiona el botón
  }

  // Mover la bola en la dirección establecida
  posicionBola += direccion;

  // Si la bola llega al LED más a la izquierda o derecha, sonar la bocina
  if (posicionBola == 0 || posicionBola == 4) {
    tone(bocina, 1000, 500);  // Sonar la bocina a 1000 Hz por 500 ms
  }

  // Evitar que la bola salga del rango
  if (posicionBola < 0) {
    posicionBola = 0;
    direccion = 1;  // Rebote hacia la derecha
  } 
  if (posicionBola > 4) {
    posicionBola = 4;
    direccion = -1; // Rebote hacia la izquierda
  }

  // Encender el nuevo LED que corresponde a la nueva posición de la bola
  digitalWrite(leds[posicionBola], HIGH);

  // Esperar un poco antes de mover la bola de nuevo (control de velocidad)
  delay(200);  // Puedes ajustar este valor para cambiar la velocidad del juego
}
