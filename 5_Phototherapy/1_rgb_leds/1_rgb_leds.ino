int RGBLED1_RedPin    = 13;
int RGBLED1_GreenPin  = 12;
int RGBLED1_BluePin   = 11;

int RGBLED2_RedPin    = 10;
int RGBLED2_GreenPin  = 9;
int RGBLED2_BluePin   = 8;

int RGBLED3_RedPin    = 7;
int RGBLED3_GreenPin  = 6;
int RGBLED3_BluePin   = 5;

int RGBLED4_RedPin    = 2;
int RGBLED4_GreenPin  = 3;
int RGBLED4_BluePin   = 4;



//int R[4] = {255, 0, 0, 0};
//int G[4] = {0, 255, 0, 0};
//int B[4] = {0, 0, 255, 0};

int R[4] = {189, 16, 255, 105};
int G[4] = {234, 67, 190, 113};
int B[4] = {70, 240, 10, 255};

int wait = 2500;

int pwmled(int RGBLED_RedPin, int RGBLED_GreenPin, int RGBLED_BluePin, int R[4], int G[4], int B[4], int wait, int i) {
    analogWrite(RGBLED_RedPin,  R[i]);
    analogWrite(RGBLED_GreenPin, G[i]);
    analogWrite(RGBLED_BluePin, B[i]);
    Serial.print("RGB (");
    Serial.print(R[i]);
    Serial.print(", ");
    Serial.print(G[i]);
    Serial.print(", ");
    Serial.print(B[i]);
    Serial.println(") ");

   
}

void setup()
{ Serial.begin(9600); // initialize serial communications at 9600 bps
  pinMode(RGBLED1_RedPin,   OUTPUT);
  pinMode(RGBLED1_GreenPin, OUTPUT);
  pinMode(RGBLED1_BluePin,  OUTPUT);

  pinMode(RGBLED2_RedPin,   OUTPUT);
  pinMode(RGBLED2_GreenPin, OUTPUT);
  pinMode(RGBLED2_BluePin,  OUTPUT);

  pinMode(RGBLED3_RedPin,   OUTPUT);
  pinMode(RGBLED3_GreenPin, OUTPUT);
  pinMode(RGBLED3_BluePin,  OUTPUT);

  pinMode(RGBLED4_RedPin,   OUTPUT);
  pinMode(RGBLED4_GreenPin, OUTPUT);
  pinMode(RGBLED4_BluePin,  OUTPUT);
}

void loop()
{
  for (int i = 0; i < 4; i++) {
  pwmled(RGBLED1_RedPin, RGBLED1_GreenPin, RGBLED1_BluePin, R, G, B, wait,i);
  pwmled(RGBLED2_RedPin, RGBLED2_GreenPin, RGBLED2_BluePin, R, G, B, wait,i);
  pwmled(RGBLED3_RedPin, RGBLED3_GreenPin, RGBLED3_BluePin, R, G, B, wait,i);
  pwmled(RGBLED4_RedPin, RGBLED4_GreenPin, RGBLED4_BluePin, R, G, B, wait,i);
  delay(wait);
  }
}
