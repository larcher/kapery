// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MPL3115A2.h>

SYSTEM_MODE(SEMI_AUTOMATIC);

////////////////////////////

bool connectToCloud = true;

////////////////////////////
// Sensors
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
double pascals = 0;
double altm = 0 ;
double tempC = 0;
double recorded_max_temp;
double recorded_min_temp;
double recorded_max_alt;
double recorded_min_alt;
double recorded_max_pressure;
double recorded_min_pressure;

int sensor_interval = 5000;

void update_record_min_max(double var, double *min, double *max, String name) {
  if (var > *max) {
      *max = var;
      Particle.publish("New max " + name, String(var));
  }
  if (var < *min) {
      *min =var;
      Particle.publish("New min " + name, String(var));
  }
}

void read_sensors() {
  tempC = baro.getTemperature();
  altm = baro.getAltitude();
  pascals = baro.getPressure();
  update_record_min_max(tempC, &recorded_min_temp, &recorded_max_temp, "Temp");
  update_record_min_max(altm, &recorded_min_alt, &recorded_max_alt, "Alt");
  update_record_min_max(pascals, &recorded_min_pressure, &recorded_max_pressure, "Pressure");
}

Timer sensor_timer(sensor_interval, read_sensors);

int setSensorInterval(String new_sensor_interval) {
  sensor_timer.changePeriod(new_sensor_interval.toInt());
}

void setup_sensors() {
  delay(1000);
  Wire.setSpeed(200000);
  Wire.begin();
  while (! baro.begin()) {
    Particle.publish("msg","Couldnt find sensor");
    delay(500);
  }

  // initialize recorded min/max's
  tempC = baro.getTemperature();
  altm = baro.getAltitude();
  pascals = baro.getPressure();

  recorded_max_temp = tempC;
  recorded_min_temp = tempC;
  recorded_max_alt = altm;
  recorded_min_alt = altm;
  recorded_max_pressure = pascals;
  recorded_min_pressure = pascals;

  Particle.variable("max_temp", recorded_max_temp);
  Particle.variable("min_temp", recorded_min_temp);
  Particle.variable("max_alt", recorded_max_alt);
  Particle.variable("min_alt", recorded_min_alt);
  Particle.variable("max_pressure", recorded_max_pressure);
  Particle.variable("min_pressure", recorded_min_pressure);

  Particle.variable("altm", altm);
  Particle.variable("tempC", tempC);
  Particle.variable("pascals", pascals);

  Particle.function("sens_intvl", setSensorInterval);

  sensor_timer.start();
}

////////////////////////////
// Servo
Servo panner;
int angle = 0;
int min_angle = 0;
int max_angle = 180;
int angle_inc = 15;
int servo_interval = 500;
bool pan_enabled = false;
bool cw = true;

void work_servo() {
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
  }
}

Timer servo_timer(servo_interval, work_servo);

int setServoInterval(String new_interval) {
  servo_timer.changePeriod(new_interval.toInt());
}

int togglePanning(String foo) { pan_enabled = ! pan_enabled; }
int setIncrement(String new_increment) { angle_inc = new_increment.toInt(); }
int setMaxAngle(String new_max_angle) { max_angle = new_max_angle.toInt(); }
int setMinAngle(String new_min_angle) { min_angle = new_min_angle.toInt(); }

int setAngle(String new_angle) {
  angle = new_angle.toInt();
  panner.write(angle);
}

void setup_servo() {
  panner.attach(A5);

  Particle.variable("angle", angle);
  Particle.variable("max_angle", max_angle);
  Particle.variable("min_angle", min_angle);
  Particle.variable("inc", angle_inc);

  Particle.function("toggle_pan", togglePanning);
  Particle.function("max_angle", setMaxAngle);
  Particle.function("min_angle", setMinAngle);
  Particle.function("angle", setAngle);
  Particle.function("inc", setIncrement);
  Particle.function("servo_intvl", setServoInterval);

  servo_timer.start();
}

////////////////////////////

void connect() {
  connectToCloud = true;
}

////////////////////////////

void setup() {
  pinMode(D7, OUTPUT);
  attachInterrupt(D1, connect, FALLING);

  setup_servo();
  setup_sensors();
}

void loop() {
  if(connectToCloud && Particle.connected() == false) {
    Particle.connect();
    //connectToCloud = false;
  }
}

