#ifndef RESCUESYSTEM_H
#define RESCUESYSTEM_H

/*
BIG ISSUES:
-   EEPROM Read and Write

Explanation:
-   RescueLager and RescueServo is only for the positions of the server
-   RescueSystem is for the rest of the System resbonsible
*/

#include <Arduino.h>
#include <RescueServo.h>
#include <RescueLager.h>

#define STG_TOP_LEFT 0
#define STG_TOP_RIGHT 1
#define STG_BUTTON_LEFT 2
#define STG_BUTTON_RIGHT 3
#define STG_LEN 4

#define LEFT 0
#define RIGHT 1

#define TOP 0
#define MIDDLE 1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3

// TODO
#define PIN_BUTTON_LEFT 5
#define PIN_BUTTON_RIGHT 6
#define PIN_MIDDLE 7
#define PIN_TOP 8

class RescueSystem
{
private:
    uint8_t storage[STG_LEN];
    uint8_t targetStorageButton = 2;

    unsigned long currentTime;
    unsigned long delayTime;

    unsigned long ServoTopTime;
    RescueLager ServoTop;
    void setServoTop(uint8_t side)
    {
        ServoMiddle.setCurrentDegree(side);
        ServoMiddleTime = currentTime;
        (side) ? storage[STG_TOP_RIGHT]-- : storage[STG_TOP_LEFT]--;
    }

    unsigned long ServoMiddleTime;
    RescueLager ServoMiddle;
    void setServoMiddle(uint8_t side)
    {
        ServoMiddle.setCurrentDegree(side);
        ServoMiddleTime = currentTime;
        (side) ? storage[STG_BUTTON_RIGHT]++ : storage[STG_BUTTON_LEFT]++;
    }

    unsigned long ServoButtonLeftTime;
    RescueServo ServoButtonLeft;

    unsigned long ServoButtonRightTime;
    RescueServo ServoButtonRight;

    bool checkStorage()
    {
        if (!storage[STG_TOP_LEFT] && !storage[STG_TOP_RIGHT] && !storage[STG_BUTTON_LEFT] && !storage[STG_BUTTON_RIGHT])
            return true;
        else
            return false;
    }

public:
    RescueSystem() : // TODO
                     ServoButtonLeft(PIN_BUTTON_LEFT, 0, 180, 20, 100),
                     ServoButtonRight(PIN_BUTTON_RIGHT, 0, 180, 20, 100),
                     ServoMiddle(PIN_MIDDLE, 0, 90, 180),
                     ServoTop(PIN_TOP, 0, 90, 180)
    {

        storage[STG_BUTTON_LEFT] = 0;
        storage[STG_BUTTON_RIGHT] = 0;
        storage[STG_TOP_LEFT] = 4;
        storage[STG_TOP_RIGHT] = 4;
        this->updateStorage();
    }

    void pickTopStorage()
    {
        if (storage[STG_TOP_LEFT] > 0)
        {
            setServoTop(WORK_LEFT);
        }
        else if (storage[STG_TOP_RIGHT] > 0)
        {
            setServoTop(WORK_RIGHT);
        }
        delay(100); // TODO (BIG ISSUE)
        ServoTop.setCurrentDegree(STANDBY);
    }

    void updateStorage()
    {
        currentTime = millis();
        if (targetStorageButton < storage[STG_BUTTON_LEFT])
        {
            this->pickTopStorage();
            setServoMiddle(WORK_LEFT);
        }

        else if (targetStorageButton < storage[STG_BUTTON_RIGHT])
        {
            this->pickTopStorage();
            setServoMiddle(WORK_RIGHT);
        }
    }

    void update()
    { // If Servo Top is not on standby mode and time to change
        if (this->checkStorage())
        {
            this->updateStorage();
            if (ServoTop.getCurrentDegree() != ServoTop.getWorkingDegree(STANDBY) && (ServoTopTime + delayTime) > currentTime)
            {
                ServoTop.setCurrentDegree(STANDBY);
            }

            if (ServoMiddle.getCurrentDegree() != ServoMiddle.getWorkingDegree(STANDBY) && (ServoMiddleTime + delayTime) > currentTime)
            {
                ServoMiddle.setCurrentDegree(STANDBY);
            }

            if (ServoButtonLeft.getCurrentDegree() != ServoButtonLeft.getWorkingDegree(STANDBY) && (ServoButtonLeftTime + delayTime) > currentTime)
            {
                ServoButtonLeft.setCurrentDegree(STANDBY);
            }

            if (ServoButtonRight.getCurrentDegree() != ServoButtonRight.getWorkingDegree(STANDBY) && (ServoButtonRightTime + delayTime) > currentTime)
            {
                ServoButtonRight.setCurrentDegree(STANDBY);
            }
        }
    }

    void putOut(bool side)
    { // Put the Rescue shit out
        if (side == LEFT)
        {
            ServoButtonLeft.setCurrentDegree(WORK);
            storage[STG_BUTTON_LEFT]--;
        }

        else if (side == RIGHT)
        {
            ServoButtonRight.setCurrentDegree(WORK);
            storage[STG_BUTTON_RIGHT]--;
        }
        this->updateStorage();
    }

    void setServoManually(uint8_t ServoIndex, uint8_t state = 3)
    {
        switch (ServoIndex)
        {
        case TOP:
            setServoTop(state);
            break;

        case MIDDLE:
            setServoMiddle(state);
            break;

        case BUTTON_LEFT:
            putOut(LEFT);
            break;

        case BUTTON_RIGHT:
            putOut(RIGHT);
            break;

        default:
            Serial.print("ERROR setServoManually");
            break;
        }
    }
};

#endif // RESCUESYSTEM_H