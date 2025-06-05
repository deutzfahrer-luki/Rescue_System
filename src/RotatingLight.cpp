// RotatingLight.cpp
#include "RotatingLight.h"

RotatingLight::RotatingLight(uint8_t pin, uint8_t offset)
  : _pixels(_numPixels, pin, NEO_GRB + NEO_KHZ800),
    _position(0),
    _offset(offset),
    _state(RotatingLightState::OFF)
{
  _green = _pixels.Color(0, 255, 0);
  _orange = _pixels.Color(255, 100, 0);
  _yellow = _pixels.Color(255, 255, 0);
  _red = _pixels.Color(255, 0, 0);
}

void RotatingLight::begin() {
  _pixels.begin();
  _pixels.show();
  _state = RotatingLightState::OFF;
}

void RotatingLight::setStates(RotatingLightState state, uint8_t position)
{
  _states[_offset+position] = state;
  _states[_offset+position+1] =  state;
}

void RotatingLight::set(RotatingLightState state, Direction dir) {
  switch (dir)
  {
  case Direction::LEFT: 
    setStates(state,0);
    Serial.println("Left");
    printArray();
    break;
  
  case Direction::RIGHT:
    setStates(state, _numPixels-1);
    Serial.println("Right");
    printArray();
  
  default:
    break;
  }
}

void RotatingLight::update() {
  printArray();
  Serial.println("up");
  _pixels.setBrightness(50);
  for (int i = 0; i < _numPixels; ++i) {
    switch (_states[_offset + i]) {
      case RotatingLightState::OFF:
        _pixels.setPixelColor(i, 0);
        break;
      case RotatingLightState::GREEN:
        _pixels.setPixelColor(i, _green);
        break;
      case RotatingLightState::YELLOW:
        _pixels.setPixelColor(i, _yellow);
        break;
      case RotatingLightState::RED:
        _pixels.setPixelColor(i, _red);
        break;
    }
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
