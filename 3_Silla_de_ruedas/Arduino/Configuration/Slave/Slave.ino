int dataFromMaster = 0;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
  Serial.begin(9600);
  mySerial.begin(38400);
}

void loop() {
  if(mySerial.available() > 0){        // Checks whether data is comming from the serial port
   dataFromMaster = mySerial.read();   // Reads the data from the serial port and store it in dataFromMaster variable
   Serial.println(dataFromMaster);   // Send data from master to plot
  }
}
