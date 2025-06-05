#ifndef MYNEOPIXEL_H
#define MYNEOPIXEL_H

#include <Adafruit_NeoPixel.h>

enum Color {
  OFF,
  RED,
  YELLOW,
  GREEN
};

enum Position {
  LEFT,
  RIGHT
};

class MyNeoPixel {
private:
  Adafruit_NeoPixel _pixels;
  uint8_t _offset;
  static const uint8_t NUM_LEDS = 12;
  Color _ledColors[NUM_LEDS];  // Array für aktuellen Farbzustand

  uint32_t getColor(Color c);
  uint8_t ledIndex(uint8_t i);
  void update();  // aktualisiert LEDs basierend auf _ledColors

public:
  MyNeoPixel(uint8_t pin, uint8_t offset = 0);
  void begin();
  void setPositionColor(Position pos, Color c);
  void clear();
};

#endif
