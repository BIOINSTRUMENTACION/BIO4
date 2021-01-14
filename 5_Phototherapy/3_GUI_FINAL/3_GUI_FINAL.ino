
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



long  incoming[13];
int wait = 2500;

int pwmled(int RGBLED_RedPin, int RGBLED_GreenPin, int RGBLED_BluePin,int R,int G, int B) {
    analogWrite(RGBLED_RedPin,  R);
    analogWrite(RGBLED_GreenPin,G);
    analogWrite(RGBLED_BluePin, B);
   
}

void setup() {
  Serial.begin(9600); 
}

void loop() {
  while(Serial.available() >= 13) {
    for (int i = 0; i < 13; i++) {
      incoming[i] = Serial.read();
    }
    int Ra = incoming[0];
    int Ga = incoming[1];
    int Ba = incoming[2];

    int Rb = incoming[3];
    int Gb = incoming[4];
    int Bb = incoming[5];

    int Rc = incoming[6];
    int Gc = incoming[7];
    int Bc = incoming[8];

    int Rd = incoming[9];
    int Gd = incoming[10];
    int Bd = incoming[11];
    int wait = incoming[12]*1000;


    
    pwmled(RGBLED1_RedPin, RGBLED1_GreenPin, RGBLED1_BluePin, Ra, Ga, Ba);
    pwmled(RGBLED2_RedPin, RGBLED2_GreenPin, RGBLED2_BluePin, Rb, Gb, Bb);
    pwmled(RGBLED3_RedPin, RGBLED3_GreenPin, RGBLED3_BluePin, Rc, Gc, Bc);
    pwmled(RGBLED4_RedPin, RGBLED4_GreenPin, RGBLED4_BluePin, Rd, Gd, Bd);
    delay(wait);
  }
}
