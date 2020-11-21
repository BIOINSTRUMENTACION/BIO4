// ------ INITIALIZE VARIABLES FOR MOTOR ----- 
int IN1 = 3;             // RIGHT BACK   
int IN2 = 2;             // RIGHT FRONT
int ENA = 5;             // RIGHT ENABLE

int IN3 = 8;             // LEFT BACK
int IN4 = 7;             // LEFT FRONT  
int ENB = 6;             // LEFT ENABLE
int dataFromMaster = 0;  // VARIABLE TO STORE DATA FROM RECIVER (Associated with control of axis)
int RawData;             // Varaibale to store incomeing data from bluetooth
int SPEED = 100;         // PWM
// INFO FROM MASTER
// 0 HALT
// 1 LEFT
// 2 RIGHT
// 3 FRONT
// 4 BACK 
#include <SoftwareSerial.h>
SoftwareSerial  Bluetooth(10, 11); // RX, TX
void setup() 
{
  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(9600);    // ARDUINO BAUD RATE
  Bluetooth.begin(38400); // BLUETOOTH BAUD RATE
}

void loop() {
  // ---------------- RECIVE DATA FROM MASTER ---------------
  if (Bluetooth.available()){
    RawData = Bluetooth.read();   // Reads the data from the serial port and store it in dataFromMaster variable
    if (  RawData < 5 ) {
        dataFromMaster=RawData;
    }
    else if ( RawData > 69){
      SPEED=RawData;
      
    }

     // ---------------- HAULT --------------- 
     if (dataFromMaster ==  0) 
     {
       Serial.println("Halut");
       digitalWrite(ENA,LOW);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       digitalWrite(ENB,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,LOW);
       delay(5);

           
     }
     
      // 1 LEFT
      else if (dataFromMaster ==  1) 
      {
       Serial.println("LEFT");
       digitalWrite(ENA,LOW);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       analogWrite(ENB,SPEED);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(5);

     
    
     
      
      }
      
      // 2 RIGHT
      else if (dataFromMaster ==  2) 
      {
      // Serial.println("RIGHT");

      analogWrite(ENA,SPEED);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(ENB,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      delay(5);

      }
      
      // 3 FRONT
      else if (dataFromMaster ==  3)
      {
      // Serial.println("FRONT");
       analogWrite(ENA,SPEED);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       analogWrite(ENB,SPEED);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(5);

      }

      // 4 BACK
     else if (dataFromMaster ==  4) 
     {
    //Serial.println("BACK");
     analogWrite(ENA,SPEED);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     analogWrite(ENB,SPEED);
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
     delay(5);

     }
     
     
    delay(5);
   
  }
} 
