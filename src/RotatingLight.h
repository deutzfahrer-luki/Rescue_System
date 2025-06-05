// RotatingLight.h
#ifndef ROTATINGLIGHT_H
#define ROTATINGLIGHT_H

#include <Adafruit_NeoPixel.h>

enum class RotatingLightState {
  RED,
  YELLOW,
  GREEN,
  OFF
};

enum class Direction {
  LEFT,
  RIGHT
};




class RotatingLight {
private:
  Adafruit_NeoPixel _pixels;
  uint8_t _numPixels = 12;
  RotatingLightState _states[12];
  int _position;
  uint8_t _offset;

  RotatingLightState _state;


  uint32_t _green;
  uint32_t _orange;
  uint32_t _yellow;
  uint32_t _red;

  uint32_t _getDimmedColor(uint32_t color, float factor);
  void _runningLed(uint32_t color);
  void _setFull(uint32_t color);
  void printArray() {
    for (int i = 0; i < _numPixels; i++) {
      Serial.print("Pixel ");
      Serial.print(i);
      Serial.print(": ");
  
      switch (_states[i]) {
        case RotatingLightState::OFF:
          Serial.println("OFF");
          break;
        case RotatingLightState::GREEN:
          Serial.println("GREEN");
          break;
        case RotatingLightState::YELLOW:
          Serial.println("YELLOW");
          break;
        case RotatingLightState::RED:
          Serial.println("RED");
          break;
        default:
          Serial.println("UNKNOWN");
          break;
      }
    }
    Serial.println();
  }
  

public:
  RotatingLight(uint8_t pin, uint8_t offset);
  void begin();
  void set(RotatingLightState state, Direction dir);
  void update();
  void setStates(RotatingLightState state, uint8_t position);
};

#endif // ROTATINGLIGHT_H
