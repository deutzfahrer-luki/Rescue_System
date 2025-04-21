#ifndef RESCUEPACKAGEHANDLER_H
#define RESCUEPACKAGEHANDLER_H

#include <Arduino.h>
#include <Servo.h>

class RescuePackageHandler {
  public:
    RescuePackageHandler(uint8_t servoPin, int16_t standbyPos, int8_t degToWorking, uint8_t packagesCount = 6);
    void begin();
    void update();
    void trigger(uint8_t len = 1);
    void clearAll();
    void resetPackages(uint8_t amount = 6);
    uint8_t getPackageCount() const;
    bool isBusy() const;
    void stop();
    const char* getStateName() const;

  private:
    Servo _servo;
    const uint8_t _servoPin;
    const int16_t _standbyPosition;
    const int8_t _degToWorkingPositionFromStandByPosition;
    uint8_t _packageCount;
    uint8_t _pendingTriggers;
    bool _clearAllMode;
    unsigned long _lastStateChangeMillis;
    static const unsigned long _moveDuration = 500;
    static const unsigned long _dwellDuration = 300;

    enum State {
      IDLE,              // Servo in Standby
      MOVING_TO_WORKING, // Servo fährt in die Arbeitsposition (Auswerfen)
      AT_WORKING,        // Servo hält in Arbeitsposition
      RETURNING          // Servo kehrt in die Standby-Position zurück
    };
    State _currentState;
};

#endif // RESCUEPACKAGEHANDLER_H
