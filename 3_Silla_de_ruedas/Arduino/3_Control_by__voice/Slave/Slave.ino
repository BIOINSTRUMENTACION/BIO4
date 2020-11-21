// ------ INITIALIZE VARIABLES FOR MOTOR ----- 
int IN1 = 3;      // RIGHT BACK   
int IN2 = 2;      // RIGHT FRONT
int ENA = 5;      // RIGHT ENABLE

int IN3 = 8;      // LEFT BACK
int IN4 = 7;      // LEFT FRONT  
int ENB = 6;      // LEFT ENABLE
int a = 1;
int dataFromMaster = 0; // VARIABLE TO STORE DATA FROM RECIVER 

// INFO FROM MASTER
// 0 HALT
// 1 LEFT
// 2 RIGHT
// 3 FRONT
// 4 BACK 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() 
{
  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  mySerial.begin(9600); // BEGIN BAUD RATE FOR BLUETOOTH
}

void loop() {
  // ---------------- RECIVE DATA FROM MASTER ---------------
  dataFromMaster = Serial.read();   // Reads the data from the serial port and store it in dataFromMaster variable
  
  // ---------------- HAULT --------------- 
  if (dataFromMaster ==  0) {
    // Serial.println("Halut");
    digitalWrite(ENA,LOW);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    delay(5);
  }

  // 1 LEFT
  else if (dataFromMaster ==  1) {
    // Serial.println("LEFT");
      digitalWrite(ENA,LOW);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      analogWrite(ENB,200);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      delay(5);
  }
  delay(500);
  // SET TO ZERO
  digitalWrite(ENA,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);


} 
