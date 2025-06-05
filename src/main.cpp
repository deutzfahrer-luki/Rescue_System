// main.cpp
#include <Arduino.h>
#include "RotatingLight.h"

RotatingLight _ring(30, 0);

void setup() {
  _ring.begin();
  Serial.begin(9600);
  Serial.println("Send '1' for LEFT green, '2' for RIGHT green");
}

void loop() {
  _ring.update();

  if (Serial.available() > 0) {
    char input = Serial.read();
    Serial.print("Received: ");
    Serial.println(input);  // Debug-Ausgabe

    if (input == '1') {
      Serial.println("Set LEFT GREEN");
      _ring.set(RotatingLightState::GREEN, Direction::LEFT);
    } else if (input == '2') {
      Serial.println("Set RIGHT GREEN");
      _ring.set(RotatingLightState::GREEN, Direction::RIGHT);
    } else {
      Serial.println("Unknown input");
    }
  }

  delay(100); // Optional: Nicht zu oft updaten
}
