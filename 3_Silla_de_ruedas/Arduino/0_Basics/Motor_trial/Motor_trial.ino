 int IN1 = 3;      // RIGHT BACK   
int IN2 = 2;      // RIGHT FRONT
int ENA = 5;      // RIGHT ENABLE

int IN3 = 8;      // LEFT BACK
int IN4 = 7;      // LEFT FRONT  
int ENB = 6;      // LEFT 


void Demo() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void loop() {
  // RIGHT 
  // Range 0-255
  analogWrite(ENA,200);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(3000);

   // SET TO ZERO 
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(3000);


  // LEFT
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  analogWrite(ENB,200);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(3000);

   // SET TO ZERO 
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(3000);


  // FRONT
  analogWrite(ENA,200);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENB,100);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(3000);

  // SET TO ZERO 
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(3000);

  // BACK
  analogWrite(ENA,200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENB,200);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(3000);

    // SET TO ZERO 
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(3000);

  
}

void setup() {
Demo();
}
