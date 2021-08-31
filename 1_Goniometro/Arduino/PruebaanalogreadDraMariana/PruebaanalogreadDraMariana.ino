// Variables For Sliding Window (3 Units) 
int sensorValue0_0;
int sensorValue1_0;
int sensorValue2_0;
int sensorValue3_0;
int sensorValue4_0;
int sensorValue5_0;

int sensorValue0_1;
int sensorValue1_1;
int sensorValue2_1;
int sensorValue3_1;
int sensorValue4_1;
int sensorValue5_1;

int sensorValue0_2;
int sensorValue1_2;
int sensorValue2_2;
int sensorValue3_2;
int sensorValue4_2;
int sensorValue5_2;


// Declare Values For Average 
float sensorValue0_average;
float sensorValue1_average;
float sensorValue2_average;
float sensorValue3_average;
float sensorValue4_average;
float sensorValue5_average;

void setup() {
 Serial.begin(9600);
}

void loop() {
  // Read Varaibles 
  sensorValue0_0= analogRead(A0);
  sensorValue0_1= analogRead(A0);
  sensorValue0_2= analogRead(A0);
  
  sensorValue1_0= analogRead(A1);
  sensorValue1_1= analogRead(A1);
  sensorValue1_2= analogRead(A1);
  
  sensorValue2_0= analogRead(A2);
  sensorValue2_1= analogRead(A2);
  sensorValue2_2= analogRead(A2);
  
  sensorValue3_0= analogRead(A3);
  sensorValue3_1= analogRead(A3);
  sensorValue3_2= analogRead(A3);
  
  sensorValue4_0= analogRead(A4);
  sensorValue4_1= analogRead(A4);
  sensorValue4_2= analogRead(A4);
  
  sensorValue5_0= analogRead(A5);
  sensorValue5_1= analogRead(A5);
  sensorValue5_2= analogRead(A5);
  

  // Apply Average 
  sensorValue0_average = (sensorValue0_0 + sensorValue0_1 + sensorValue0_2)/3;
  sensorValue1_average = (sensorValue1_0 + sensorValue1_1 + sensorValue1_2)/3;
  sensorValue2_average = (sensorValue2_0 + sensorValue2_1 + sensorValue2_2)/3;
  sensorValue3_average = (sensorValue3_0 + sensorValue3_1 + sensorValue3_2)/3;
  sensorValue4_average = (sensorValue4_0 + sensorValue4_1 + sensorValue4_2)/3;
  sensorValue5_average = (sensorValue5_0 + sensorValue5_1 + sensorValue5_2)/3;

  // Prepare Data for Serial Transmition 
  String coma = ","; 
  String resultado = ""; 
  
  String valor_string1 = "s:";     
  valor_string1.concat(sensorValue0_average);
  
  String valor_string2 = "";    
  valor_string2.concat(sensorValue1_average);
  
  String valor_string3 = "";    
  valor_string3.concat(sensorValue2_average);
  
  String valor_string4 = "";     
  valor_string4.concat(sensorValue3_average);
  
  String valor_string5 = "";     
  valor_string5.concat(sensorValue4_average);
  
  String valor_string6 = "";     
  valor_string6.concat(sensorValue5_average);
  
  resultado=valor_string1+coma+valor_string2+coma+valor_string3+coma+valor_string4+coma+valor_string5+coma+valor_string6;
    
  Serial.println(resultado);
  delay(1);
}
