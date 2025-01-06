#include <Arduino.h>

#include <RescueSystem.h>

RescueSystem rescueSystem;

uint8_t dir;
uint8_t oldDir = dir;
  uint8_t result[2];

void splitNumber(uint8_t number, uint8_t* result) {
    result[0] = number / 10;
    result[1] = number % 10;
}

void updatePWMFromSerial()
{
  if (Serial.available() > 0)
  {
    float newDir = Serial.parseInt();
    if (newDir >= 0 && newDir <= 99)
    {
      dir = newDir;
      splitNumber(dir, result);
      Serial.print("Result: [");
      Serial.print(result[0]);
      Serial.print(", ");
      Serial.print(result[1]);
      Serial.println("]");
    }

    else
      Serial.println("Ungueltiger Wert");
    while (Serial.available() > 0)
      Serial.read();
  }
}


void setup() {
  rescueSystem.begin();
}

void loop() {
  rescueSystem.update();
  if (dir!=oldDir)
  {
    oldDir = dir;
    rescueSystem.setServoManually(result[0], result[1]);
  }
}