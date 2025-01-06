#ifndef RESCUESERVO_H
#define RESCUESERVO_H

#define STANDBY 2
#define WORK 1

#include <Arduino.h>
#include <servo.h>


class RescueServo
{
private:
    uint8_t workingDegrees[2]; // standby, work
    uint8_t currentDegree;
    uint8_t pin;
    Servo ServoRS;

public:
    RescueServo(uint8_t Pin, uint8_t min, uint8_t max, uint8_t standby, uint8_t work)
    {
        workingDegrees[STANDBY] = standby;
        workingDegrees[WORK] = work;
        ServoRS.attach(pin);
        ServoRS.write(workingDegrees[STANDBY]);
    }

    // getter and setter
    void setWorkingDegree(uint8_t index, uint8_t value) { workingDegrees[index] = value; }
    uint8_t getWorkingDegree(uint8_t index) const { return workingDegrees[index]; }

    void setCurrentDegree(uint8_t targetPosition)
    {
        currentDegree = workingDegrees[targetPosition];
        ServoRS.write(currentDegree);
    }
    uint8_t getCurrentDegree() { return currentDegree; }
};

#endif