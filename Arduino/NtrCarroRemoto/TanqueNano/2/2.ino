#include <SoftwareSerial.h>

// Configuración del módulo Bluetooth en los pines D2 (RX) y D3 (TX)
SoftwareSerial bluetooth(2, 3);

void setup() {
  // Inicializar Bluetooth y Monitor Serial
  bluetooth.begin(9600);     // Comunicación con el módulo Bluetooth
  Serial.begin(9600);        // Comunicación con el Monitor Serial

  // Configurar el LED integrado como salida
  pinMode(LED_BUILTIN, OUTPUT);

  // Mensajes iniciales
  Serial.println("Arduino Nano con Bluetooth configurado en D2 (RX) y D3 (TX).");
  bluetooth.println("Conexión Bluetooth establecida. Envíe '1' para encender o '0' para apagar el LED.");
}

void loop() {
  // Verificar si hay datos disponibles desde Bluetooth
  if (bluetooth.available()) {
    char data = bluetooth.read(); // Leer comando recibido
    Serial.print("Recibido desde Bluetooth: ");
    Serial.println(data);

    // Acciones basadas en el comando recibido
    if (data == '1') {
      digitalWrite(LED_BUILTIN, HIGH); // Encender LED
      Serial.println("LED encendido.");
      bluetooth.println("LED encendido.");
    } else if (data == '0') {
      digitalWrite(LED_BUILTIN, LOW); // Apagar LED
      Serial.println("LED apagado.");
      bluetooth.println("LED apagado.");
    } else {
      Serial.println("Comando no reconocido.");
      bluetooth.println("Comando no reconocido.");
    }
  }

  // Opcional: Leer datos desde el Monitor Serial y enviarlos al Bluetooth
  if (Serial.available()) {
    char data = Serial.read();
    bluetooth.print("Desde Serial: ");
    bluetooth.println(data);
  }
}
