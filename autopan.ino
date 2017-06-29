
SYSTEM_MODE(SEMI_AUTOMATIC);

Servo panner;

int angle = 0;
int min_angle = 0;
int max_angle = 180;
int angle_inc = 15;
int servo_interval=500;
bool pan_enabled = false;
bool cw = true;

bool connectToCloud = true;

void setup() {
  panner.attach(A5);
  pinMode(D7, OUTPUT);
  attachInterrupt(D1, connect, FALLING);

  Particle.variable("angle", angle);
  Particle.variable("max_angle", max_angle);
  Particle.variable("min_angle", min_angle);
  Particle.variable("inc", angle_inc);

  Particle.function("toggle_pan", togglePanning);
  Particle.function("max_angle", setMaxAngle);
  Particle.function("min_angle", setMinAngle);
  Particle.function("angle", setAngle);
  Particle.function("inc", setIncrement);
}

int togglePanning(String foo) {
  pan_enabled = ! pan_enabled;
}

int setIncrement(String new_increment) {
  angle_inc = new_increment.toInt();
}

int setAngle(String new_angle) {
  angle = new_angle.toInt();
  panner.write(angle);
}

int setMaxAngle(String new_max_angle) {
  max_angle = new_max_angle.toInt();
}

int setMinAngle(String new_min_angle) {
  min_angle = new_min_angle.toInt();
}

void loop() {
  if(connectToCloud && Particle.connected() == false) {
    Particle.connect();
    //connectToCloud = false;
  }

  if (pan_enabled) {
    if (cw) {
      angle += angle_inc;
    } else {
      angle -= angle_inc;
    }
    if (angle >= max_angle) {
      angle = max_angle;
      cw = false;
    }
    if (angle <= min_angle) {
      angle = min_angle;
      cw = true;
    }
    panner.write(angle);
    delay(servo_interval);
  }
}

void connect() {
  connectToCloud = true;
}
