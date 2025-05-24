// RotatingLight.cpp
#include "RotatingLight.h"

RotatingLight::RotatingLight(uint8_t pin)
  : _pixels(_numPixels, pin, NEO_GRB + NEO_KHZ800),
    _position(0),
    _counter(0),
    _state(RotatingLightState::Driving)
{
  _green = _pixels.Color(0, 255, 0);
  _orange = _pixels.Color(255, 100, 0);
  _yellow = _pixels.Color(255, 255, 0);
  _red = _pixels.Color(255, 0, 0);
  _delayMs = _delayRotating;
}

void RotatingLight::begin() {
  _pixels.begin();
  _pixels.show();
  _state = RotatingLightState::Driving;
  _counter = 0;
}

void RotatingLight::set(RotatingLightState state, uint8_t rotations) {
  _counter = rotations * _numPixels;
  _state = state;
  (_state==RotatingLightState::Error) ? _delayMs = _delayBlinking: _delayMs = _delayRotating;
}

void RotatingLight::update() {
    static unsigned long _lastUpdateTime = 0;
    static bool redOn = false;
    unsigned long _currentTime = millis();

    if (_currentTime - _lastUpdateTime < _delayMs) {
      return;
    }
    _lastUpdateTime = _currentTime;

    _pixels.clear();

    if (_state == RotatingLightState::Error) {
        if (redOn) {
          _setFull(_red);
        } else {
          _pixels.clear();
        }
        redOn = !redOn;
    }
    else if (_state == RotatingLightState::FoundVictimBig) {
        _runningLed(_red);
        _counter--;
        if (_counter == 0) {
          _state = RotatingLightState::Driving;
          _delayMs = _delayRotating;
        }
    } 
    else if (_state == RotatingLightState::FoundVictimMiddlel) {
        _runningLed(_orange);
        _counter--;
        if (_counter == 0) {
          _state = RotatingLightState::Driving;
          _delayMs = _delayRotating;
        }
    } 
    else if (_state == RotatingLightState::FoundVictimLiddle) {
        _runningLed(_yellow);
        _counter--;
        if (_counter == 0) {
          _state = RotatingLightState::Driving;
          _delayMs = _delayRotating;
        }
    }
    else {
        _setFull(_green);
    }

    _pixels.show();
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
  int prev = (_position - 1 + _numPixels) % _numPixels;
  int next = (_position + 1) % _numPixels;
  _pixels.setBrightness(255);
  _pixels.setPixelColor(_position, _pixels.gamma32(color));
  _pixels.setPixelColor(prev, _getDimmedColor(color, 0.7));
  _pixels.setPixelColor(next, _getDimmedColor(color, 0.7));
  _position = (_position + 1) % _numPixels;
}

void RotatingLight::_setFull(uint32_t color) {
  _pixels.setBrightness(50);
  for (int i = 0; i < _numPixels; i++) {
    _pixels.setPixelColor(i, color);
  }
}
