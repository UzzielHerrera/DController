#ifndef DELTAKINEMATICS_H
#define DELTAKINEMATICS_H

#include "Constants.h"
#include <Arduino.h>
#include "MoveDesigner.h"

class DeltaKinematics{
  public:
    // DeltaKinematics();
    void begin(void);
    bool nanErrorOccured;
    MoveDesigner InverseCalculations(Point point, MoveDesigner &md);
    bool InverseKinematics(Point point, Angle &angle);
    Point FowardCalculations(Angle angle);

  private:
    bool AngleThetaCalculations(float x0, float y0, float z0, float &theta);
    void NAN_OCCURED();
    double _realAngle[MAX_STEPPERS];
    double _angleError[MAX_STEPPERS];
    double _angleToTake[MAX_STEPPERS];
    float _y0;
    float _y1;
    float _deltaE;
    float _deltaF;
    float _deltaRE;
    float _deltaRF;
    float _deltaRFpow2;
    float _deltaREpow2;
    const double tan30 = 1/sqrt(3);
    const double tan30x05 = 0.5/sqrt(3);
    const double tan60 = sqrt(3);
    const double sin30 = 0.5;
    const double cos30 = sqrt(3) / 2;
    const double cos120 = -0.5;
    const double sin120 = sqrt(3) / 2;
};

extern DeltaKinematics DKinematics;
#endif