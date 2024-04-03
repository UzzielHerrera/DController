#ifndef Stepper_h
#define Stepper_h

#include "Constants.h"
#include <Arduino.h>
#include "CANSupervisor.h"

#define STEPPER_TIME_OFFSET 4000

class Stepper{
  public:
    Stepper(uint8_t canAddress, uint8_t stepperID);
    void update();
    void setDesiredMovement(float desiredPosition, float timeInverval);
    double currentAnglePosition;
    int8_t id;
    bool lastMoveComplete;

  private:
    bool _angleSent;
    uint16_t _finishCount;
    double _moveDuration;
    uint32_t _moveDurationInt;
    uint8_t _canAddress;
    double _desiredAnglePosition;
    uint32_t _instructionSentTime;
    uint32_t _instructionFinishCheckTime;
};

#endif