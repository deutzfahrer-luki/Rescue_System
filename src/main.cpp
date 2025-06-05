#include <Arduino.h>
#include "RotatingLight.h"

MyNeoPixel _ring(10, 0);

void setup() {
  Serial.begin(9600);
  _ring.begin();
  _ring.clear();
  Serial.println("MyNeoPixel ready");
  Serial.println("Send keys 1-6 to set colors:");
  Serial.println("1: LEFT RED, 2: LEFT YELLOW, 3: LEFT GREEN");
  Serial.println("4: RIGHT RED, 5: RIGHT YELLOW, 6: RIGHT GREEN");
  Serial.println("0: Clear LEDs");
}

void loop() {
  //_ring.update();

  if (Serial.available() > 0) {
    char input = Serial.read();
    Serial.print("Received: ");
    Serial.println(input);

    switch (input) {
      case '1':
        Serial.println("Set LEFT RED");
        _ring.setPositionColor(LEFT, RED);
        break;
      case '2':
        Serial.println("Set LEFT YELLOW");
        _ring.setPositionColor(LEFT, YELLOW);
        break;
      case '3':
        Serial.println("Set LEFT GREEN");
        _ring.setPositionColor(LEFT, GREEN);
        break;
      case '4':
        Serial.println("Set RIGHT RED");
        _ring.setPositionColor(RIGHT, RED);
        break;
      case '5':
        Serial.println("Set RIGHT YELLOW");
        _ring.setPositionColor(RIGHT, YELLOW);
        break;
      case '6':
        Serial.println("Set RIGHT GREEN");
        _ring.setPositionColor(RIGHT, GREEN);
        break;
      case '0':
        Serial.println("Clear LEDs");
        _ring.clear();
        break;
      default:
        Serial.println("Unknown input");
        break;
    }
  }
}
