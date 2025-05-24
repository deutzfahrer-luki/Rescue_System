#include <Arduino.h>

#define MODUS 2  // Ändere zu 2 für „alle geradeaus“

const int STBY = 27;
const int pwmValue = 100;

// Motor 1 (VL)
const int PWM_1 = 11;
const int AIN1_1 = 23;
const int AIN2_1 = 25;

// Motor 2 (VR)
const int PWM_2 = 6;
const int AIN1_2 = 31;
const int AIN2_2 = 29;

// Motor 3 (HL)
const int PWM_3 = 5;
const int AIN1_3 = 49;
const int AIN2_3 = 47;

// Motor 4 (HR)
const int PWM_4 = 4;
const int AIN1_4 = 43;
const int AIN2_4 = 45;

// Bremsfunktion
void braking(int ain1, int ain2, int pwm) {
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, HIGH);
  analogWrite(pwm, 0);
}

// Ein Motor vorwärts und rückwärts fahren
void driveMotor(int pwmPin, int ain1, int ain2) {
  analogWrite(pwmPin, pwmValue);
  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  delay(2000);

  braking(ain1, ain2, pwmPin);
  delay(500);

  analogWrite(pwmPin, pwmValue);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, HIGH);
  delay(2000);

  braking(ain1, ain2, pwmPin);
  delay(500);
}

// Ein Motor nur vorwärts fahren
// Motor 3 (HL) – Drehrichtung korrigiert
void driveForward(int pwmPin, int ain1, int ain2, bool reverse = false) {
  analogWrite(pwmPin, pwmValue);
  if (reverse) {
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
  } else {
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
  }
}


void setup() {
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  // TB6612 aktivieren

  int motorPins[] = {
    PWM_1, AIN1_1, AIN2_1,
    PWM_2, AIN1_2, AIN2_2,
    PWM_3, AIN1_3, AIN2_3,
    PWM_4, AIN1_4, AIN2_4
  };

  for (int i = 0; i < sizeof(motorPins) / sizeof(motorPins[0]); i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

void loop() {
#if MODUS == 1
  // Original-Modus: Motoren nacheinander vorwärts/rückwärts
  //driveMotor(PWM_1, AIN1_1, AIN2_1);
  //driveMotor(PWM_2, AIN1_2, AIN2_2);
  driveMotor(PWM_3, AIN1_3, AIN2_3);
  //driveMotor(PWM_4, AIN1_4, AIN2_4);

#elif MODUS == 2
  // Alle Motoren gleichzeitig vorwärts
  driveForward(PWM_1, AIN1_1, AIN2_1);              // VL
driveForward(PWM_2, AIN1_2, AIN2_2);              // VR
driveForward(PWM_3, AIN1_3, AIN2_3, true);        // HL (umdrehen!)
driveForward(PWM_4, AIN1_4, AIN2_4, true);        // HR (umdrehen!)


  delay(3000);

  braking(AIN1_1, AIN2_1, PWM_1);
  braking(AIN1_2, AIN2_2, PWM_2);
  braking(AIN1_3, AIN2_3, PWM_3);
  braking(AIN1_4, AIN2_4, PWM_4);

  delay(2000);
#endif
}
