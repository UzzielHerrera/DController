#ifndef DATA_H
#define DATA_H

#include "Constants.h"
#include "Arduino.h"

class Datas {
  public:
    // Datas();
    void begin();
    Point currentPoint;
    Point desiredPoint;
    Point homePoint;

    Angle currentAngle;
    Angle desiredAngle;
    Angle homeAngle;
    bool isExecutedGCode;
    float zOffset;
    
    uint32_t sleepTime;
    uint32_t lastSleepSet;
    bool isSleeping;
};

extern Datas data;


#endif