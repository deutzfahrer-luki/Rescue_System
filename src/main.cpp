#include <Arduino.h>
// FORM CHATI
#define pinCLK A10
#define pinDT  A12
#define pinBtn A11

int counter = 0;
int lastCLKState;

void setup() {
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);
  pinMode(pinBtn, INPUT);

  Serial.begin(9600);
  lastCLKState = digitalRead(pinCLK);
}

void loop() {
  int currentCLKState = digitalRead(pinCLK);

  if (currentCLKState != lastCLKState) {
    if (digitalRead(pinDT) != currentCLKState) {
      counter++;
    } else {
      counter--;
    }
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  lastCLKState = currentCLKState;

  // Button direkt lesen, LOW = gedrückt
  int btnState = digitalRead(pinBtn);
  if (btnState == LOW) {
    Serial.println("Button gedrückt");
  }
}

