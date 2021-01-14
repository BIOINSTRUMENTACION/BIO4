void setup() {
  // put your setup code here, to run once:
  Serial.begin(74880);

}

void loop() {

  if (Serial.available() > 0){                  //If there is data to read
  String val = Serial.readStringUntil('\n') ;   //Read String
  int valint = val.toInt();                     //Cast String into Integer
  Serial.println(valint);                       //Print Intiger
  }
  
  

}
