// Desarrollado por: Juan Jose Benites Coronel
// github.com/jnbenites
// C++ code
//
// Configura el pin 13 como salida para controlar el LED
void setup()
{
  // Led
  pinMode(13, OUTPUT); // Rojo
  pinMode(12, OUTPUT); // Amarillo
  pinMode(8, OUTPUT);  // Verde

  pinMode(2, INPUT; // Led para ver si funciona el boton
}

void loop()
{
  // Luz verde 3000
  digitalWrite(8, HIGH); 
  delay(4000);
  digitalWrite(8, LOW);
    
  // Luz amarilla 3000
  digitalWrite(12, HIGH); 
  delay(2000);
  digitalWrite(12, LOW);

  // Luz roja 30000
  digitalWrite(13, HIGH); 
  delay(4000);
  digitalWrite(13, LOW);

}

if
