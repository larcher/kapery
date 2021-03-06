# KAPery

Some Photon/Arduino code relating to Kite Aerial Photography

It's fun to hang a camera from a kite and take pictures from way up high.  It's not so easy to aim that camera once everything is off the ground.  To increase the chances of capturing some interesting pictures, we'll make the camera pan back and forth.  There are lots of ways to make this happen, but I'm using a servo and a [Photon](https://particle.io) microcontroller.

For now, this program will continually pan a servo, within specified limits and at a specified speed. These parameters are controllable through the Particle app or the [Particle Cloud API](https://docs.particle.io/reference/api/).


## Hardware

**Current Setup**:
- I have a single servo attached to the Photon, wired into pin A5 as well as GND and VIN for power. This servo is embedded as the "pan" part of [one of these mini pan-tilt things](https://www.adafruit.com/product/1967) -- the "tilt" servo isn't connected yet.
- A barometer/altimeter/thermometer chip is attached via I2C.  It's an MPL3115A2, with it's SDA wired into pin D0, and SCL to pin D1.

This runs on a Photon

# TODO

* add support for other devices
  - ~~altimeter/barometer~~
  - ~~temperature~~
  - accelerometer, gyroscope, compass ([one of these](https://www.adafruit.com/product/1604))
* log sensor values to memory, including mininmum and maximum values observed, with timestamps
  - just how high did the kite get?
  - and how cold is it up there?
  - how much did it bounce around?
* better (web-based) UI for controlling servo parameters, viewing sensor data, via the Particle Cloud API
* interrupt support for sensors that can send interrupts
* react smartly to sensor data
  - keep the camera pointed in a certain compass direction, or at the horizon
  - enable/disable panning once altitude crosses a given threshold
