#include "Arduino.h"
#include "Stepper.h"
#include "Constants.h"

#define float_error 0.02

Stepper::Stepper(uint8_t canAddress, uint8_t stepperID) {
  currentAnglePosition = 0.0;
  _canAddress = canAddress;
  id = stepperID;
  _desiredAnglePosition = 0.0;
  _instructionSentTime = 0;
  _instructionFinishCheckTime = 0;
  _moveDuration = 0;
  _moveDurationInt = 0;
  _angleSent = false;
  lastMoveComplete = false;
}

void Stepper::update() {
  if(!lastMoveComplete) {
    if(!_angleSent) {
      Serial.printf("Sending smooth 0x%2X\r\n", _canAddress);
      if(canSupervisor.sendSmoothMove(_desiredAnglePosition, _moveDuration, _canAddress)) {
        Serial.printf("Received smooth 0x%2X\r\n", _canAddress);
        currentAnglePosition = _desiredAnglePosition;
        _instructionSentTime = micros();
        _angleSent = true;
        _finishCount = 0;
      } else {
        Serial.printf("Rejected smooth 0x%2X\r\n", _canAddress);
        return;
      }
    } else {
      if(micros() - _instructionSentTime >= STEPPER_TIME_OFFSET + _moveDurationInt && micros() - _instructionFinishCheckTime > 250) {
        // Serial.printf("Checking finish 0x%2X\r\n", _canAddress);
        float entry = canSupervisor.requestSetPoint(_canAddress);
        if(entry > currentAnglePosition - float_error && entry < currentAnglePosition + float_error) {
          lastMoveComplete = true;
          _angleSent = false;
          // Serial.printf("finish 0x%2X\r\n", _canAddress);
          return;
        }
        _finishCount++;
        _instructionFinishCheckTime = micros();
        if(_finishCount > 100) {
          _finishCount = 0;
          _angleSent = false;
        }
      }
    }
  }
}

void Stepper::setDesiredMovement(float desiredPosition, float timeInverval){
  _desiredAnglePosition = desiredPosition;
  _moveDuration = timeInverval;
  _moveDurationInt = (int)(_moveDuration * 1000000.0);
  _angleSent = false;
  lastMoveComplete = false;

  // Serial.println();
  // Serial.printf("_desiredAnglePosition 0x%02X: %0.2f.\r\n", _canAddress, _desiredAnglePosition);
  // Serial.printf("_moveDuration 0x%02X: %0.2f.\r\n", _canAddress, _moveDuration);
  // Serial.printf("_moveDurationInt 0x%02X: %u\r\n", _canAddress, _moveDurationInt);
}
