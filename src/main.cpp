#include <Arduino.h>
#include "RotatingLight.h"

RotatingLight _ring(10);

void setup() {
  Serial.begin(9600);
  _ring.begin();
  _ring.reset();

  Serial.println("RotatingLight ready");
  Serial.println("Send keys:");
  Serial.println("1: LEFT RED, 2: LEFT YELLOW, 3: LEFT GREEN");
  Serial.println("4: RIGHT RED, 5: RIGHT YELLOW, 6: RIGHT GREEN");
  Serial.println("0: Reset LEDs (grün alle)");
  Serial.println("7: FoundVictimBig (rotierend rot)");
  Serial.println("8: FoundVictimMiddlel (rotierend orange)");
  Serial.println("9: FoundVictimLiddle (rotierend gelb)");
  Serial.println("e: ERROR blink rot");
  Serial.println("d: Driving (zeige Seitenfarben)");
}

void loop() {
  _ring.update();

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
        Serial.println("Reset LEDs (grün alle)");
        _ring.reset();
        break;
      case '7':
        Serial.println("Set State: FoundVictimBig");
        _ring.set(RotatingLightState::FoundVictimBig, 6);
        break;
      case '8':
        Serial.println("Set State: FoundVictimMiddlel");
        _ring.set(RotatingLightState::FoundVictimMiddlel, 6);
        break;
      case '9':
        Serial.println("Set State: FoundVictimLiddle");
        _ring.set(RotatingLightState::FoundVictimLiddle, 6);
        break;
      case 'e':
        Serial.println("Set State: ERROR");
        _ring.set(RotatingLightState::Error);
        break;
      case 'd':
        Serial.println("Set State: DRIVING");
        _ring.set(RotatingLightState::Driving);
        break;
      case 'b':
        Serial.println("Set State: DRIVING");
        _ring.set(RotatingLightState::BlueFill);
      default:
        Serial.println("Unknown input");
        break;
    }
  }
}
