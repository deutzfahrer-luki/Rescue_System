#include "RotatingLight.h"
#include <Arduino.h>

RotatingLight::RotatingLight(uint8_t pin, int rotationOffset)
  : _pixels(_numPixels, pin, NEO_GRB + NEO_KHZ800),
    _position(0),
    _counter(0),
    _state(RotatingLightState::Driving),
    _rotationOffset(rotationOffset),
    _blueFillingActive(false),
    _blueIndex(0),
    _blueStartTime(0),
    _blueWaitStart(0) 
{
  _green = _pixels.Color(0, 255, 0);
  _orange = _pixels.Color(255, 100, 0);
  _yellow = _pixels.Color(255, 255, 0);
  _red = _pixels.Color(255, 0, 0);
  _blue = _pixels.Color(0, 0, 255);

  _delayMs = _delayRotating;

  for (uint8_t i = 0; i < _numPixels; i++) {
    _ledColors[i] = OFF;
  }
}

void RotatingLight::begin() {
  _pixels.begin();
  _pixels.show();
  _state = RotatingLightState::Driving;
  _counter = 0;
  reset();
}

void RotatingLight::setRotationOffset(int offset) {
  _rotationOffset = offset % _numPixels;
  if (_rotationOffset < 0) _rotationOffset += _numPixels;
}

void RotatingLight::set(RotatingLightState state, uint8_t rotations) {
  if (_blueFillingActive && state != RotatingLightState::BlueFill) {
    return;
  }

  _state = state;

  switch (state) {
    case RotatingLightState::FoundVictimBig:
      setRotationOffset(0);    // Links vorne
      _counter = rotations * _numPixels;
      break;
    case RotatingLightState::FoundVictimMiddlel:
      setRotationOffset(6);    // Rechts hinten
      _counter = rotations * _numPixels;
      break;
    case RotatingLightState::FoundVictimLiddle:
      setRotationOffset(3);    // Mitte (optional)
      _counter = rotations * _numPixels;
      break;
    case RotatingLightState::Error:
      _delayMs = _delayBlinking;
      break;
    case RotatingLightState::BlueFill:
      _blueIndex = 0;
      _blueStartTime = millis();
      _blueWaitStart = 0;
      _blueFillingActive = true;
      _delayMs = 30;
      for (uint8_t i = 0; i < _numPixels; i++) {
        _ledColors[i] = OFF;
      }
      _updateFromColors();
      break;
    case RotatingLightState::Reset:
      reset();
      break;
    default:
      _counter = 0;
      _delayMs = _delayRotating;
      break;
  }

  if (state != RotatingLightState::BlueFill && state != RotatingLightState::Reset) {
    for (uint8_t i = 0; i < _numPixels; i++) {
      _ledColors[i] = OFF;
    }
  }
}

void RotatingLight::update() {
  unsigned long _currentTime = millis();

  if (_state == RotatingLightState::BlueFill) {
    _handleBlueFill(_currentTime);
    return;
  }

  static unsigned long _lastUpdateTime = 0;
  static bool redOn = false;

  if (_currentTime - _lastUpdateTime < _delayMs) return;
  _lastUpdateTime = _currentTime;

  _pixels.clear();

  switch (_state) {
    case RotatingLightState::Error:
      if (redOn) {
        _setFull(_red);
      } else {
        _pixels.clear();
      }
      redOn = !redOn;
      break;

    case RotatingLightState::FoundVictimBig:
      _runningLed(_red);
      if (--_counter == 0) set(RotatingLightState::Driving);
      break;

    case RotatingLightState::FoundVictimMiddlel:
      _runningLed(_orange);
      if (--_counter == 0) set(RotatingLightState::Driving);
      break;

    case RotatingLightState::FoundVictimLiddle:
      _runningLed(_yellow);
      if (--_counter == 0) set(RotatingLightState::Driving);
      break;

    case RotatingLightState::Driving:
    case RotatingLightState::Reset:
      _updateFromColors();  // Seitenanzeige zeigen (meist grün oder gesetzt)
      break;

    default:
      break;
  }

  _pixels.show();
}

void RotatingLight::_handleBlueFill(unsigned long currentTime) {
  unsigned long elapsed = currentTime - _blueStartTime;
  unsigned long fillDuration = 5000;  // 5 Sekunden füllen
  unsigned long waitDuration = 1000;  // 1 Sekunde warten

  if (elapsed <= fillDuration) {
    int ledsToLight = (int)((float)elapsed / fillDuration * _numPixels);

    if (ledsToLight > _blueIndex) {
      for (int i = _blueIndex; i < ledsToLight; i++) {
        _pixels.setPixelColor(i, _blue);
      }
      _pixels.show();
      _blueIndex = ledsToLight;
    }
  } else {
    if (_blueWaitStart == 0) {
      _blueWaitStart = currentTime;
    } else if (currentTime - _blueWaitStart >= waitDuration) {
      _blueFillingActive = false;
      set(RotatingLightState::Reset);
    }
  }
}

uint32_t RotatingLight::_getDimmedColor(uint32_t color, float factor) {
  uint8_t r = (uint8_t)((color >> 16) & 0xFF);
  uint8_t g = (uint8_t)((color >> 8) & 0xFF);
  uint8_t b = (uint8_t)(color & 0xFF);

  r = (uint8_t)(r * factor);
  g = (uint8_t)(g * factor);
  b = (uint8_t)(b * factor);

  return _pixels.gamma32(_pixels.Color(r, g, b));
}

void RotatingLight::_runningLed(uint32_t color) {
  int posWithOffset = (_position + _rotationOffset) % _numPixels;
  int prev = (posWithOffset - 1 + _numPixels) % _numPixels;
  int next = (posWithOffset + 1) % _numPixels;

  _pixels.setBrightness(255);
  _pixels.setPixelColor(posWithOffset, _pixels.gamma32(color));
  _pixels.setPixelColor(prev, _getDimmedColor(color, 0.7));
  _pixels.setPixelColor(next, _getDimmedColor(color, 0.7));

  _position = (_position + 1) % _numPixels;
}

void RotatingLight::_setFull(uint32_t color) {
  _pixels.setBrightness(100);
  for (int i = 0; i < _numPixels; i++) {
    _pixels.setPixelColor(i, color);
  }
}

uint32_t RotatingLight::_getColor(Color c) {
  switch (c) {
    case RED: return _red;
    case YELLOW: return _yellow;
    case GREEN: return _green;
    case BLUE: return _blue;
    case OFF:
    default: return _pixels.Color(0, 0, 0);
  }
}

void RotatingLight::_updateFromColors() {
  for (uint8_t i = 0; i < _numPixels; i++) {
    _pixels.setPixelColor(i, _getColor(_ledColors[i]));
  }
  _pixels.show();
}

void RotatingLight::setPositionColor(Position pos, Color c) {
  for (uint8_t i = 0; i < _numPixels; i++) {
    _ledColors[i] = OFF;
  }

  switch (pos) {
    case LEFT:
      _ledColors[0] = c;
      _ledColors[1] = c;
      _ledColors[2] = c;
      break;
    case RIGHT:
      _ledColors[6] = c;
      _ledColors[7] = c;
      _ledColors[8] = c;
      break;
  }

  _updateFromColors();
}

void RotatingLight::clear() {
  for (uint8_t i = 0; i < _numPixels; i++) {
    _ledColors[i] = OFF;
  }
  _pixels.clear();
  _pixels.show();
}

void RotatingLight::reset() {
  for (uint8_t i = 0; i < _numPixels; i++) {
    _ledColors[i] = GREEN;
  }

  _updateFromColors();
  _state = RotatingLightState::Reset;
  _position = 0;
  _counter = 0;
}


void RotatingLight::setAllGreen() {
  for (uint8_t i = 0; i < _numPixels; i++) {
    _ledColors[i] = GREEN;
  }
  _updateFromColors();
}
