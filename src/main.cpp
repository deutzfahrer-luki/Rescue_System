#include <Arduino.h>

class MotorController {
  public:
    MotorController(int pwmA, int pwmB,
                    int ain1, int ain2,
                    int bin1, int bin2,
                    int stby)
    : pwmA(pwmA), pwmB(pwmB),
      ain1(ain1), ain2(ain2),
      bin1(bin1), bin2(bin2),
      stby(stby) {}

    void begin() {
      pinMode(pwmA, OUTPUT);
      pinMode(pwmB, OUTPUT);
      pinMode(ain1, OUTPUT);
      pinMode(ain2, OUTPUT);
      pinMode(bin1, OUTPUT);
      pinMode(bin2, OUTPUT);
      pinMode(stby, OUTPUT);
      digitalWrite(stby, HIGH); // Aktivieren
      stop();
    }

    // Gegensinnige Drehung: A vorwärts, B rückwärts (oder andersherum)
    void rotateOpposite(int speed, bool clockwise) {
      digitalWrite(ain1, clockwise ? HIGH : LOW);
      digitalWrite(ain2, clockwise ? LOW : HIGH);
      analogWrite(pwmA, speed);

      digitalWrite(bin1, clockwise ? LOW : HIGH);
      digitalWrite(bin2, clockwise ? HIGH : LOW);
      analogWrite(pwmB, speed);
    }

    // Motorbremse aktiv
    void stop() {
      analogWrite(pwmA, 0);
      analogWrite(pwmB, 0);

      digitalWrite(ain1, HIGH);
      digitalWrite(ain2, HIGH);

      digitalWrite(bin1, HIGH);
      digitalWrite(bin2, HIGH);
    }

  private:
    int pwmA, pwmB;
    int ain1, ain2;
    int bin1, bin2;
    int stby;
};

// 💡 Pins aus deinem Plan:
MotorController motor(
  7,    // MOT1_PWM
  6,    // MOT2_PWM
  31,   // MOT1_IN1
  29,   // MOT1_IN2
  23,   // MOT2_IN1
  25,   // MOT2_IN2
  27    // MOT_STBY
);

void setup() {
  motor.begin();
}

void loop() {
  // Dreht im Uhrzeigersinn (eine Seite vor, eine zurück)
  motor.rotateOpposite(100, true);
  delay(2000);

  // Bremsen
  motor.stop();
  delay(1000);

  // Gegendrehung
  motor.rotateOpposite(100, false);
  delay(2000);

  // Wieder bremsen
  motor.stop();
  delay(2000);
}
