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
  Serial.begin(2000000);

  // initialize pins
  pinMode(FPA0, OUTPUT);
  pinMode(FPA1, OUTPUT);
  pinMode(FPA2, OUTPUT);
  pinMode(FPB0, OUTPUT);
  pinMode(FPB1, OUTPUT);
  pinMode(FPDATA, OUTPUT);
  pinMode(FPENABLE, OUTPUT);
  pinMode(COM, INPUT);  // not used yet
}

void loop() {
  // Toggle data pin
  bool data = !digitalRead(FPDATA);
  digitalWrite(FPDATA, data);

  // Loop through all the outputs and enable one after another
  int a, b;
  char buf[10];
  for (b = 0; b <= 3; b++) {
    digitalWrite(FPB0, (b >> 0) % 2);
    digitalWrite(FPB1, (b >> 1) % 2);
    for (a = 1; a <= 7; a++) {
      sprintf(buf, "%d, %d = %d", b, a, data);
      Serial.println(buf);
      digitalWrite(FPA0, (a >> 0) % 2);
      digitalWrite(FPA1, (a >> 1) % 2);
      digitalWrite(FPA2, (a >> 2) % 2);
      digitalWrite(FPENABLE, 1);
      delay(250);
      digitalWrite(FPENABLE, 0);
    }
  }
}
