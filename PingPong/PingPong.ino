// Definición de los pines para los LEDs
int LedUno = 8;  
int LedDos = 9;  
int LedTres = 10;  
int LedCuatro = 11;  
int LedCinco = 12;  

// Definición de los pines para los pulsadores
int pulsadorIzquierda = 2;  // Pin del pulsador que activa "izquierda"
int pulsadorDerecha = 3;    // Pin del pulsador que activa "derecha"

void setup() {
    // Configuramos los pines de los LEDs como salida
    pinMode(LedUno, OUTPUT);   
    pinMode(LedDos, OUTPUT);   
    pinMode(LedTres, OUTPUT);  
    pinMode(LedCuatro, OUTPUT); 
    pinMode(LedCinco, OUTPUT); 

    // Configuramos los pines de los pulsadores como entrada con resistencia de pull-up
    pinMode(pulsadorIzquierda, INPUT_PULLUP);  
    pinMode(pulsadorDerecha, INPUT_PULLUP);    
}

void loop() {
    // Leer el estado de los pulsadores
    if (digitalRead(pulsadorIzquierda) == LOW) { // Si el pulsador de "izquierda" está presionado
        // Encender los LEDs de "izquierda"
        digitalWrite(LedUno, HIGH);          // Enciende LedUno
        delay(500); 
        digitalWrite(LedUno, LOW);           // Apaga LedUno
        
        digitalWrite(LedDos, HIGH);          // Enciende LedDos
        delay(500); 
        digitalWrite(LedDos, LOW);           // Apaga LedDos
        
        digitalWrite(LedTres, HIGH);         // Enciende LedTres
        delay(500); 
        digitalWrite(LedTres, LOW);          // Apaga LedTres
        
        digitalWrite(LedCuatro, HIGH);       // Enciende LedCuatro
        delay(500); 
        digitalWrite(LedCuatro, LOW);        // Apaga LedCuatro
        
        digitalWrite(LedCinco, HIGH);        // Enciende LedCinco
        delay(500); 
        digitalWrite(LedCinco, LOW);         // Apaga LedCinco
        delay(500);  


    }

    if (digitalRead(pulsadorDerecha) == LOW) { // Si el pulsador de "derecha" está presionado
        // Encender los LEDs de "derecha"
        digitalWrite(LedCinco, HIGH);        // Enciende LedCinco
        delay(500); 
        digitalWrite(LedCinco, LOW);         // Apaga LedCinco
        
        digitalWrite(LedCuatro, HIGH);       // Enciende LedCuatro
        delay(500); 
        digitalWrite(LedCuatro, LOW);        // Apaga LedCuatro
        
        digitalWrite(LedTres, HIGH);         // Enciende LedTres
        delay(500); 
        digitalWrite(LedTres, LOW);          // Apaga LedTres
        
        digitalWrite(LedDos, HIGH);          // Enciende LedDos
        delay(500); 
        digitalWrite(LedDos, LOW);           // Apaga LedDos
        
        digitalWrite(LedUno, HIGH);          // Enciende LedUno
        delay(500); 
        digitalWrite(LedUno, LOW);           // Apaga LedUno
        
    }
}
