#ifndef ROTATINGLIGHT_H
#define ROTATINGLIGHT_H

#include <Adafruit_NeoPixel.h>

enum class RotatingLightState {
  Driving,
  FoundVictimBig,
  FoundVictimMiddlel,
  FoundVictimLiddle,
  Error,
  Reset,
  BlueFill
};

enum Position {
  LEFT,
  RIGHT
};

enum Color {
  OFF,
  RED,
  YELLOW,
  GREEN,
  BLUE
};

class RotatingLight {
private:
  static const uint8_t _numPixels = 12;
  static const uint8_t _delayRotating = 30;
  static const uint8_t _delayBlinking = 200;

  uint8_t _delayMs;
  int _position;
  int _counter;

  Adafruit_NeoPixel _pixels;
  RotatingLightState _state;

  uint32_t _green;
  uint32_t _orange;
  uint32_t _yellow;
  uint32_t _red;
  uint32_t _blue;

  Color _ledColors[_numPixels];

  int _rotationOffset;

  bool _blueFillingActive;
  uint8_t _blueIndex;
  unsigned long _blueStartTime;
  unsigned long _blueWaitStart;

  uint32_t _getDimmedColor(uint32_t color, float factor);
  void _runningLed(uint32_t color);
  void _setFull(uint32_t color);
  uint32_t _getColor(Color c);
  void _updateFromColors();
  void _handleBlueFill(unsigned long currentTime);

public:
  RotatingLight(uint8_t pin, int rotationOffset = 0);
  void begin();
  void set(RotatingLightState state, uint8_t rotations = 4);
  void update();

  void setPositionColor(Position pos, Color c);
  void clear();
  void reset();
  void setAllGreen();
  void setRotationOffset(int offset);
};

#endif
