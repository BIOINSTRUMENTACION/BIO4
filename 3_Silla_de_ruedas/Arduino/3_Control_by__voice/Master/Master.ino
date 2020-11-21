// Code For Master Bluetooth Module 
#include <SoftwareSerial.h>       // PACKAGE FOR SERIAL COMMUNICATION
char dataFrompython;              // Variable for Data recived from python
int Transmit;                     // Transmit value  
SoftwareSerial Bluetooth(10, 11); // RX (CONNECTED TO DEVICE TX), TX (CONNECTED TO DEVICE RX)

void setup() {
  Serial.begin(9600);    // ARDUINO BAUD RATE
  Bluetooth.begin(38400); // BLUETOOTH BAUD RATE
  
}

void loop() {
  if (Serial.available() > 0){
    dataFrompython =  Serial.read();
    //-----------------STOP --------------------//
    if (dataFrompython == '0') {
      Transmit=0; 
     }
    //-----------------  Left  --------------------//
    if (dataFrompython == '1') {
      Transmit=1;
      }
    //----------------- Right --------------------//
    if (dataFrompython == '2') {
     Transmit=2;
      }
      
    //----------------- Front --------------------//
    if (dataFrompython == '3') {
     Transmit=3;
      }

    //----------------- Back --------------------//
    if (dataFrompython == '4') {
      Transmit=4;
      }
  }
  // SEND DATA VIA BLUETOOTH
  
  Bluetooth.write(Transmit); // Send Value from master
 
 
  //Serial.println(Transmit); // 
  delay(5);
  
}
