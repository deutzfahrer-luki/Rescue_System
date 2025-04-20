#include <Servo.h>
#include "RescuePackageHandler.h"
#include <Arduino.h>


//RescueSystem RSL(9, 45, 80, 2000, 6);

RescuePackageHandler rescueHandler(9, 45, 80); // Beispiel: Servo an Pin 9, Standby = 90 Grad, Arbeitsposition = 90+30 = 120 Grad

void setup() {
  Serial.begin(9600);
  rescueHandler.begin();
}

void loop() {
  rescueHandler.update();

  if (Serial.available()) {
    char cmd = Serial.read();
    
    if (cmd == 'T') {
      rescueHandler.trigger(); 
    } 
    else if (cmd == 'C' || cmd == 'c') {
      rescueHandler.clearAll(); 
    } 
    else if (cmd == 'R' || cmd == 'r') {
      rescueHandler.resetPackages();
    } 
    else if (cmd >= '0' && cmd <= '9') {
      uint8_t zahl = cmd - '0';
      rescueHandler.trigger(zahl);
    }
  }
}
