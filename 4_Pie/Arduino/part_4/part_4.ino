int ML1[51] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} ; 
int pin1 = 2;
int PINS[6] = {2,3,4,5,6,7};
void setup() {
    Serial.begin(9600);
    for(int i=0; i <=5; i++)
    {
      pinMode(PINS[i],OUTPUT);
    }
    
   
 

}

void loop() {

    for(int i=0; i <=5; i++)
    {
      Serial.println(PINS[i]);
      delay(500);
    }

    Serial.println(10);
  for(int i=0; i <51; i++)
  {
      
      digitalWrite(pin1,ML1[i]);
      Serial.println(ML1[i]);
      delay(500);
    
  }

}
