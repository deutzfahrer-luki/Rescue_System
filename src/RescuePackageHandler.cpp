#include "RescuePackageHandler.h"

RescuePackageHandler::RescuePackageHandler(uint8_t servoPin, int16_t standbyPos, int8_t degToWorking, uint8_t packagesCount)
  : _servoPin(servoPin),
    _standbyPosition(standbyPos),
    _degToWorkingPositionFromStandByPosition(degToWorking),
    _packageCount(packagesCount),
    _pendingTriggers(0),
    _clearAllMode(false),
    _currentState(IDLE),
    _lastStateChangeMillis(0)
{
  _servo.write(standbyPos);

}

void RescuePackageHandler::begin() {
  _servo.attach(_servoPin);
  _servo.write(_standbyPosition);
  _currentState = IDLE;
  _clearAllMode = false;
  _pendingTriggers = 0;
  _lastStateChangeMillis = millis();
}

void RescuePackageHandler::update() {
  unsigned long now = millis();
  switch (_currentState) {
    case IDLE:
      if (_pendingTriggers > 0) {
        _currentState = MOVING_TO_WORKING;
        _lastStateChangeMillis = now;
      }
      else if (_clearAllMode && _packageCount > 0) {
        _pendingTriggers = 1;
      }
      else if (_clearAllMode && _packageCount == 0) {
        _clearAllMode = false;
      }
      break;
    case MOVING_TO_WORKING:
      if (now - _lastStateChangeMillis >= _moveDuration) {
        _servo.write(_standbyPosition + _degToWorkingPositionFromStandByPosition);
        _currentState = AT_WORKING;
        _lastStateChangeMillis = now;
        if (_packageCount > 0) {
          _packageCount--;
        }
        _pendingTriggers--;
      }
      break;
    case AT_WORKING:
      if (now - _lastStateChangeMillis >= _dwellDuration) {
        _servo.write(_standbyPosition);
        _currentState = RETURNING;
        _lastStateChangeMillis = now;
      }
      break;
    case RETURNING:
      if (now - _lastStateChangeMillis >= _moveDuration) {
        _currentState = IDLE;
        _lastStateChangeMillis = now;
      }
      break;
  }
}

void RescuePackageHandler::trigger(uint8_t len) {
  if (_packageCount > 0) {
    uint8_t toTrigger = (len > _packageCount) ? _packageCount : len;
    _pendingTriggers += toTrigger;
  }
}

void RescuePackageHandler::clearAll() {
  _clearAllMode = true;
}

void RescuePackageHandler::resetPackages(uint8_t amount) {
  _packageCount = amount;
}

uint8_t RescuePackageHandler::getPackageCount() const {
  return _packageCount;
}

bool RescuePackageHandler::isBusy() const {
  return (_currentState != IDLE || _pendingTriggers > 0);
}

void RescuePackageHandler::stop() {
  _servo.write(_standbyPosition);
  _currentState = IDLE;
  _pendingTriggers = 0;
  _clearAllMode = false;
  _lastStateChangeMillis = millis();
}

const char* RescuePackageHandler::getStateName() const {
  switch (_currentState) {
    case IDLE:
      return "IDLE";
    case MOVING_TO_WORKING:
      return "MOVING_TO_WORKING";
    case AT_WORKING:
      return "AT_WORKING";
    case RETURNING:
      return "RETURNING";
    default:
      return "UNKNOWN";
  }
}
