#include "RotatingLight.h"

MyNeoPixel::MyNeoPixel(uint8_t pin, uint8_t offset)
  : _pixels(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800), _offset(offset)
{
  // Alle LEDs initial auf OFF
  for(uint8_t i=0; i<NUM_LEDS; i++) {
    _ledColors[i] = OFF;
  }
}

void MyNeoPixel::begin() {
  _pixels.begin();
  update();
}

uint32_t MyNeoPixel::getColor(Color c) {
  switch(c) {
    case RED: return _pixels.Color(255, 0, 0);
    case YELLOW: return _pixels.Color(255, 255, 0);
    case GREEN: return _pixels.Color(0, 255, 0);
    case OFF:
    default: return _pixels.Color(0, 0, 0);
  }
}

uint8_t MyNeoPixel::ledIndex(uint8_t i) {
  return (i + _offset) % NUM_LEDS;
}

void MyNeoPixel::update() {
  for(uint8_t i=0; i<NUM_LEDS; i++) {
    _pixels.setPixelColor(ledIndex(i), getColor(_ledColors[i]));
  }
  _pixels.show();
}

void MyNeoPixel::setPositionColor(Position pos, Color c) {
  if(pos == LEFT) {
    for(uint8_t i = 0; i <= 2; i++) {
      _ledColors[i] = c;
    }
  } else if(pos == RIGHT) {
    for(uint8_t i = 6; i <= 8; i++) {
      _ledColors[i] = c;
    }
  }
  update();
}

void MyNeoPixel::clear() {
  for(uint8_t i=0; i<NUM_LEDS; i++) {
    _ledColors[i] = OFF;
  }
  update();
}
