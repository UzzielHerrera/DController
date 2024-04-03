#ifndef STEPPERCONTROLLER_H
#define STEPPERCONTROLLER_H

#include "Constants.h"
#include "Arduino.h"
#include "Stepper.h"
#include "Queue.h"
#include "MoveDesigner.h"

class StepperController{
  public:
    // StepperController();
    void begin();
    void update();
    void attach(Stepper *stepper);
    void addMoveDesigner(MoveDesigner md);
    void addMotionMoveDesigner(MoveDesigner md);
    MoveDesigner popMoveDesigner();
    MoveDesigner peekMoveDesigner();
    bool repeat;
    void setSteppersToZero();

  private:
    void setFrequencyFrom(double moveDuration);
    bool _isExecutingMovement;
    bool _endlessRepeat;
    uint8_t _numOfAttachedSteppers;
    uint32_t _counter = 0;
    // int32_t _maxSteps;
    double _maxAngle;
    double _maxSpeed;
    uint16_t _speeds[MAX_STEPPERS];
    Queue<MoveDesigner> _designerQueue = Queue<MoveDesigner>(MAX_DESIGNER_MOVES);
    Stepper *_steppers[MAX_STEPPERS];
    double _frequency;
};

extern StepperController stepperControl;

#endif