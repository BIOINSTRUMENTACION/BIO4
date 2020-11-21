// Code For Master Bluetooth Module 
#include <SoftwareSerial.h>      // PACKAGE FOR SERIAL COMMUNICATION
int X;                           // STORE X COORDINATE
int Y;                           // STORE Y COORDINATE
int SW;                          // BREAK VARIABLE 
int Transmit;                   // Transmit value  
int STOP = 10;                   // BREAK SIGNAL
SoftwareSerial Bluetooth(10, 11); // RX (CONNECTED TO DEVICE TX), TX (CONNECTED TO DEVICE RX)

void setup() {
  // Analogic inpunts do not require initalization
  pinMode(STOP,INPUT);   // Break button
  Serial.begin(9600);    // ARDUINO BAUD RATE
  Bluetooth.begin(38400); // BLUETOOTH BAUD RATE
  
}

void loop() {
  Y  =  analogRead(A0);     // Read Y COORDINATE 
  X  =  analogRead(A1);     // READ X COORDINATE 
  SW =  digitalRead(STOP);  // READ BREAK BUTTON 

  //-----------------Rest Area--------------------//
  if (X >= 500 && X <= 505 && Y >= 500 && Y <= 508) 
  {
  Transmit=0;
  }

  //-----------------  Left  --------------------//
  if (X >= 0 && X <500) 
  {
  Transmit=1;
  }

  //----------------- Right --------------------//
  if (X > 505 && X <= 1023) 
  {
  Transmit=2;
  }

 //----------------- Front --------------------//
  if (Y > 508 && Y <= 1023) 
  {
  Transmit=3;
  }

   //----------------- Back --------------------//
  if (Y >= 0 && Y < 500) 
  {
  Transmit=4;
  }

  // SEND DATA VIA BLUETOOTH
  
  Bluetooth.write(Transmit); // Send Value from master
 
 
  Serial.println(Transmit); // 

 
  delay(500);
  
}
