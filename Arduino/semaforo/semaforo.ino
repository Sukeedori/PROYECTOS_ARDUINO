// C++ code
//
// Configura el pin 13 como salida para controlar el LED
void setup()
{
  // Led
  pinMode(10, OUTPUT); // Rojo
  pinMode(9, OUTPUT); // Amarillo
  pinMode(8, OUTPUT);  // Verde
}

void loop()
{
  // Luz verde 3000
  digitalWrite(8, HIGH); 
  delay(4000);
  digitalWrite(8, LOW);
    
  // Luz amarilla 3000
  digitalWrite(9, HIGH); 
  delay(2000);
  digitalWrite(9, LOW);

  // Luz roja 30000
  digitalWrite(10, HIGH); 
  delay(4000);
  digitalWrite(10, LOW);
}
