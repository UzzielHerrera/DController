#include "Constants.h"
#include "Arduino.h"
#include "MoveDesigner.h"

MoveDesigner::MoveDesigner(){
  isActive = false;
  moveDuration = 1.0;
  for(uint8_t i = 0; i < MAX_STEPPERS; i++){
    Designer[i] = {false, 0.0};
  }
}

void MoveDesigner::addMove(uint8_t id, float nextAngle){
  isActive = true;
  if(id < MAX_STEPPERS){
    Designer[id] = {true, nextAngle};
  }
}

void MoveDesigner::reset(){
  for(uint8_t i = 0; i < MAX_STEPPERS; i++){
    Designer[i] = {false, 0.0};
  }
}