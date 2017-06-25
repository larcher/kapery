SYSTEM_MODE(SEMI_AUTOMATIC);

Servo panner;
int angle = 0;
int interval=500;

void setup() {
  panner.attach(A5);
}

void loop() {
  for (angle=0; angle<180; angle++) {
    panner.write(angle);
    delay(interval);
  }
  for (angle=180; angle>0; angle--) {
    panner.write(angle);
    delay(interval);
  }
}
