
// Define constants //
int     push    = 7;
int     state   = 0;
int sensorValue_1 = 0;
int sensorValue_2 = 0;
int sensorValue_3 = 0;
float total_sensor_value = 0.0;
float   voltage = 0.0;
float   angle   = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(push,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 
  state = digitalRead(push);
  if (state == HIGH){
     sensorValue_1 = analogRead(A0);
     sensorValue_2 = analogRead(A0);
     sensorValue_3 = analogRead(A0);
     total_sensor_value = (sensorValue_1 + sensorValue_2 +  sensorValue_3  )/3;
     voltage = total_sensor_value*(5.031/1023.0);
     angle   = -50.05772339*voltage + 247.12090794;
     // Serial.println(voltage);
     Serial.println(angle);
     state = LOW;
     delay(1200);
    }

}
