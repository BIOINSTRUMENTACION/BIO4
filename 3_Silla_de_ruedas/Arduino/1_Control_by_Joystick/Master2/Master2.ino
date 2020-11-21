// Code For Master Bluetooth Module  with speed controller
#include <SoftwareSerial.h>       // PACKAGE FOR SERIAL COMMUNICATION
int A;                            // Analog Read for PWM
int PWM;                          // Store Convertion for PWM
int UPPERLIMIT = 220;             // Upper limit for PWM ( We do not want the motor to go full speed)
int lowerlimit = 70;              // Lower limit for PWM (MOtor won't move if PWM is really low)
int X;                            // STORE X COORDINATE
int Y;                            // STORE Y COORDINATE
int SW;                           // BREAK VARIABLE 
int Transmit;                     // Transmit value  
int STOP = 10;                    // BREAK SIGNAL
SoftwareSerial Bluetooth(10, 11); // RX (CONNECTED TO DEVICE TX), TX (CONNECTED TO DEVICE RX)

void setup() {
   // Analogic inpunts do not require initalization
  Serial.begin(9600);    // ARDUINO BAUD RATE
  pinMode(STOP,INPUT);   // Break button
  Bluetooth.begin(38400); // BLUETOOTH BAUD RATE

}

void loop() {
  // PWM 
  A = analogRead(A2);                   // Read Potenciometer for Speed Control
  PWM    = map(A, 0, 1023, 0, 255);     // Map values from 0-1023 to 0-255
  if (PWM >  UPPERLIMIT ) {             // If upper limit is surpassed
    PWM =  UPPERLIMIT ;                 // Assigneupperlimit  to PWM 
  }
  
  else if (PWM < lowerlimit) {           // If lowerlimit is surpassed
    PWM = lowerlimit;                    // Assigne lowerlimit to PWM
  }

  Bluetooth.write(PWM);                  // Send  PWM Value from master

  // JOYSTICK
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


}
