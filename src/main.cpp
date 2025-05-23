#include <Arduino.h>

#define motor 1

const int STBY = 27;
const int pwm =100;

#if motor == 1 //VL
const int PWM_A = 7;
const int AIN1 = 23;
const int AIN2 = 25;
#endif

#if motor == 2 // VR
const int PWM_A = 6;
const int AIN1 = 31;
const int AIN2 = 29;
#endif

#if motor == 3 // VR
const int PWM_A = 5;
const int AIN1 = 49;
const int AIN2 = 47;
#endif

#if motor == 4 // VR
const int PWM_A = 4;
const int AIN1 = 43;
const int AIN2 = 45;
#endif




bool dir = 1;

void breaking()
{
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2,1);
  delay(2000);
}

void setup() {
  pinMode(PWM_A, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);  // TB6612 aktivieren
}



void loop() {
  // Vorwärts
  dir=!dir;
  analogWrite(PWM_A, pwm);
  digitalWrite(AIN1, true);
  digitalWrite(AIN2, false);
  delay(2000);
  breaking();
  analogWrite(PWM_A, pwm);
  digitalWrite(AIN1, false);
  digitalWrite(AIN2, true);
  delay(2000);
  breaking();

}
