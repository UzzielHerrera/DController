#ifndef MODEDESIGNER_H
#define MODEDESIGNER_H
#include "Constants.h"
#include "Arduino.h"

struct MoveCommand{
  bool isActive;
  float position;
};

class MoveDesigner{
  public:
    MoveDesigner();
    void reset();
    void addMove(uint8_t id, float nextAngle);
    MoveCommand Designer[MAX_STEPPERS];
    bool isActive;
    double moveDuration;
};

#endif