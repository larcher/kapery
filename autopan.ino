SYSTEM_MODE(SEMI_AUTOMATIC);

Servo panner;
int angle = 0;
int interval=500;
bool cw = true;
int max_angle = 180;
int min_angle = 0;

void setup() {
  panner.attach(A5);
}

void loop() {
  if (cw) { 
      angle += angle_inc;
      if (angle > max_angle) {
          angle = max_angle;
          cw = false;
      }
  } else {
      angle -= angle_inc;
      if (angle < min_angle) {
          angle = min_angle;
          cw = true;
      }
  }  
  panner.write(angle);
  delay(interval);
}
