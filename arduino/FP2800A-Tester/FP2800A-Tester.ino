// pin definitions
#define FPA0      4
#define FPA1      3
#define FPA2      5
#define FPB0      6
#define FPB1      7
#define FPDATA    8
#define FPENABLE  9
#define COM       2

void setup() {
  // start serial 
  Serial.begin(2000000);  //this speed only works with Arduino IDE 2.x or an external serial monitor. Use 115200 for older IDEs

  // initialize pins
  pinMode(FPA0, OUTPUT);
  pinMode(FPA1, OUTPUT);
  pinMode(FPA2, OUTPUT);
  pinMode(FPB0, OUTPUT);
  pinMode(FPB1, OUTPUT);
  pinMode(FPDATA, OUTPUT);
  pinMode(FPENABLE, OUTPUT);
  pinMode(COM, INPUT);  // only needed as output if the COM pin on the FP2800A doesn't work 
}

void loop() {
  // Toggle data pin for each loop so we switch between positive and negative output
  bool data = !digitalRead(FPDATA);
  digitalWrite(FPDATA, data);

  // Loop through all the outputs and enable one after another
  int a, b;
  char buf[10];
  for (b = 3; b >= 0; b--) {  
    digitalWrite(FPB0, (b >> 0) % 2);
    digitalWrite(FPB1, (b >> 1) % 2);
    for (a = 7; a >= 1; a--) {
      sprintf(buf, "%d, %d = %d", b, a, data);  
      Serial.println(buf);
      digitalWrite(FPA0, (a >> 0) % 2);
      digitalWrite(FPA1, (a >> 1) % 2);
      digitalWrite(FPA2, (a >> 2) % 2);
      digitalWrite(FPENABLE, 1);
      delayMicroseconds(100);  // use for inspection of all pins at once
      //delay(250); // use for visual inspection of each output
      digitalWrite(FPENABLE, 0);
    }
  }
}
