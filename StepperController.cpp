#include "Constants.h"
#include <Arduino.h>
#include "Stepper.h"
#include "StepperController.h"
#include "Queue.h"
#include "State.h"
#include "Tools.h"

// StepperController::StepperController(){
void StepperController::begin(void) {
  _designerQueue.clear();
  repeat = false;
  _counter = 0;
  _numOfAttachedSteppers = 0;
  _isExecutingMovement = false;
  _maxSpeed = 0;
  for(uint8_t i = 0; i < MAX_STEPPERS; i++){
    _steppers[i] = {0};
    _speeds[i] = 0;
  }
  Serial.println("Steppers Automatic Control Module initialized.");
}

void StepperController::attach(Stepper *stepper){
  if (stepper->id < MAX_STEPPERS){
    _steppers[stepper->id] = stepper;
    _numOfAttachedSteppers++;
  }
}

void StepperController::addMoveDesigner(MoveDesigner md){
  _designerQueue.push(md);
  _designerQueue.setResetPoint();
}

void StepperController::addMotionMoveDesigner(MoveDesigner md){
  _designerQueue.push(md);
}

MoveDesigner StepperController::popMoveDesigner(){
  return _designerQueue.pop();
}

MoveDesigner StepperController::peekMoveDesigner(){
  return _designerQueue.peek();
}

void StepperController::setFrequencyFrom(double moveDuration){
  _frequency = 0.0001 * M_PI / moveDuration;
}

void StepperController::setSteppersToZero(){
  for(uint8_t i = 0; i < _numOfAttachedSteppers; i++){
    if(_steppers[i]!=0){
      _steppers[i]->currentAnglePosition = 0.0;
    }
  }
}



void StepperController::update(){
  if(!_isExecutingMovement){
    // delay(100);
    if(_designerQueue.count() > 0) {

      double bufvalue;
      int _counter;
      MoveDesigner md = popMoveDesigner();

      tool.PrintMoveDesigner(md, "_designerQueue");

      for(uint8_t i = 0; i < _numOfAttachedSteppers; i++){
        if(md.Designer[i].isActive){
          _steppers[i]->setDesiredMovement(md.Designer[i].position, md.moveDuration);
          // Serial.println((String) "lapse " + i + ": " + _steppers[i]->moveDuration);
        }
      }
      stateled.Red();
      _isExecutingMovement = true;
    }
    else if(repeat){
      _designerQueue.reset();
    }
  } else {
    _counter = 0;
    for(uint8_t i = 0; i < MAX_STEPPERS; i++){
      if(_steppers[i] != 0){
        _steppers[i]->update();
        if(_steppers[i]->lastMoveComplete) _counter++;
      }
    }
    if(_counter >= _numOfAttachedSteppers){
      stateled.Green();
      _isExecutingMovement = false;
      Serial.println("md finish");
    }
  }
}

