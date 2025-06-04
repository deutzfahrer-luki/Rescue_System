#include <Servo.h>
#include "RescuePackageHandler.h"
#include <Arduino.h>


//RescueSystem RSL(9, 45, 80, 2000, 6);


// TODO SET PINS CORRECT
//RescuePackageHandler rescueHandler(10, 135, -70); // right -> servo1 
RescuePackageHandler rescueHandler(9, 45, 70);  //left -> servo2


void setup() {
  Serial.begin(9600);
  rescueHandler.begin();
}

void loop() {
  rescueHandler.update();

  if (Serial.available()) {
    char cmd = Serial.read();
    Serial.println(cmd);
    
    if (cmd == 'T' || cmd == 't') {
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
