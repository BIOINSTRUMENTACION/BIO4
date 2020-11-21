int X;
int Y;
int SW;
int STOP = 10;

void setup() {
  // Analogic inpunts do not require initalization
  pinMode(STOP,INPUT);
  Serial.begin(9600);

}

void loop() {
  Y  =  analogRead(A0);
  X  =  analogRead(A1);
  SW =  digitalRead(STOP);


  // Rest Area
  if (X >= 500 && X <= 505 && Y >= 500 && Y <= 508) 
  {
  Serial.println("off");    
  }

  //  Left
  if (X >= 0 && X <500) 
  {
  Serial.println("Izqueirda");
  Serial.println(X);
  }

  // Right
  if (X > 505 && X <= 1023) 
  {
  Serial.println("Derecha");
  Serial.println(X);
  }

  // Front
  if (Y > 508 && Y <= 1023) 
  {
  Serial.println("Front");
  Serial.println(Y);
  }

  // Back
   if (Y >= 0 && Y < 500) 
  {
  Serial.println("Back");
  Serial.println(Y);
  }

  delay(1500);
 

  



}
