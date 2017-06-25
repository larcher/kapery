
SYSTEM_MODE(SEMI_AUTOMATIC);

Servo panner;
int angle = 0;
int min_angle = 0;
int max_angle = 180;
int angle_inc = 15;
int interval=500;
bool pan_enabled = false;
bool cw = true;

bool connectToCloud = true;

void setup() {
    panner.attach(A5);
    pinMode(D7, OUTPUT);
    attachInterrupt(D1, connect, FALLING);
}

void loop() {
    if(connectToCloud && Particle.connected() == false) {
        Particle.connect();
        //connectToCloud = false;
    }
  
  if (pan_enabled) {
  if (cw) { 
      angle += angle_inc;
      if (angle >= max_angle) {
          angle = max_angle;
          cw = false;
      }
  } else {
      angle -= angle_inc;
      if (angle <= min_angle) {
          angle = min_angle;
          cw = true;
      }
  }
  panner.write(angle);
  delay(interval);
  }

}

void connect() {
    connectToCloud = true;
}
