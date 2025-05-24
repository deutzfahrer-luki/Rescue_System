// RotatingLight.h
#ifndef ROTATINGLIGHT_H
#define ROTATINGLIGHT_H

#include <Adafruit_NeoPixel.h>

enum class RotatingLightState {
  Driving,            // all green
  FoundVictimBig,     // red
  FoundVictimMiddlel, // orange
  FoundVictimLiddle,  // yellow
  Error               // all red
};

class RotatingLight {
private:
  static const uint8_t _numPixels = 12;
  uint8_t _delayMs = 30;
  static const uint8_t _delayRotating = 30;
  static const uint8_t _delayBlinking = 200;

  Adafruit_NeoPixel _pixels;
  int _position;
  int _counter;

  RotatingLightState _state;

  uint32_t _green;
  uint32_t _orange;
  uint32_t _yellow;
  uint32_t _red;

  uint32_t _getDimmedColor(uint32_t color, float factor);
  void _runningLed(uint32_t color);
  void _setFull(uint32_t color);

public:
  RotatingLight(uint8_t pin);
  void begin();
  void set(RotatingLightState state, uint8_t rotations = 4);
  void update();
};

#endif // ROTATINGLIGHT_H
