// main.cpp
#include <Arduino.h>
#include "RotatingLight.h"

RotatingLight _ring(10);

void setup() {
  _ring.begin();
  Serial.begin(9600);
}

void loop() {
  _ring.update();

  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '1') {
      _ring.set(RotatingLightState::FoundVictimBig);
    } else if (input == '2') {
      _ring.set(RotatingLightState::FoundVictimMiddlel);
    } else if (input == '3') {
      _ring.set(RotatingLightState::FoundVictimLiddle);
    } else if (input == '4') {
      _ring.set(RotatingLightState::Error);
    } else if (input == '5') {
      _ring.set(RotatingLightState::Driving);
    }
  }
}
