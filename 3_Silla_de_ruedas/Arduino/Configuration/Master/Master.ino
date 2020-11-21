// Code For Master Bluetooth Module 
int value = 1;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  delay(1500);
  mySerial.write(value); // Send Value from master
}
