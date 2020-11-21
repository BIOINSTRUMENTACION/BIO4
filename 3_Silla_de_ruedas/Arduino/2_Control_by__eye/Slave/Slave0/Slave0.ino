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
  dataFromMaster =  Bluetooth.read();   // Reads the data from the serial port and store it in dataFromMaster variable
     // ---------------- HAULT --------------- 
     if (dataFromMaster ==  0) 
     {
     Serial.println("Halut");
     }
     
      // 1 LEFT
      else if (dataFromMaster ==  1) 
      {
      Serial.println("LEFT");
      }
      
      // 2 RIGHT
      else if (dataFromMaster ==  2) 
      {
      Serial.println("RIGHT");
      }
      
      // 3 FRONT
      else if (dataFromMaster ==  3)
      {
      Serial.println("FRONT");
      }

      // 4 FRONT
     else if (dataFromMaster ==  4) 
     {
    Serial.println("BACK");
     }
     
    delay(500);
  }
} 
