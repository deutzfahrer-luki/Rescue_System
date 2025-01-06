#ifndef RESCUELAGER_H
#define RESCUELAGER_H

#define STANDBY 2
#define WORK_LEFT 0
#define WORK_RIGHT 1

#include <Arduino.h>
#include <servo.h>


class RescueLager
{
private:
    uint8_t workingDegrees[3]; // standby, work left, work right
    uint8_t currentDegree;
    uint8_t pin;
    Servo ServoRS;

public:
    RescueLager(uint8_t Pin, uint8_t work_l, uint8_t standby, uint8_t work_r)
    {
        workingDegrees[STANDBY] = standby;
        workingDegrees[WORK_LEFT] = work_l;
        workingDegrees[WORK_RIGHT] = work_r;
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



#endif //RESCUELAGER_H