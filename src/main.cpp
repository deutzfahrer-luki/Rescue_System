#include <Servo.h>
#include "RescuePackageHandler.h"
#include <Arduino.h>


//RescuePackageHandler rescueHandler(10, 128, -70); // right
RescuePackageHandler rescueHandler(9, 45, 70);  //left


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
