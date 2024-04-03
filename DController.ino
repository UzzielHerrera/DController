#include "Constants.h"
#include "GReceiver.h"
#include "CANSupervisor.h"
#include "DeltaKinematics.h"
#include "Stepper.h"
#include "StepperController.h"
#include "Motion.h"
#include "Data.h"
#include "Tools.h"
#include "MoveDesigner.h"
#include "GExecuter.h"
#include "State.h"

GReceiver gReceiver;
CANSupervisor canSupervisor;
GExecuter gExecuter;
Tools tool;
Datas data;
DeltaKinematics DKinematics;
StepperController stepperControl;
Motion motion;
StateLed stateled;

Stepper stepperArm1(0xC1, 0);
Stepper stepperArm2(0xC2, 1);
Stepper stepperArm3(0xC3, 2);

void treeTestProgram(float maxHeight, float minHeight, float maxX, float maxY, float duration);
void infiniteLoopTestProgram(void);
void lineTestProgram(float maxHeight, float minHeight, float duration);

void setup() {
  gReceiver.begin();
  canSupervisor.begin();
  gExecuter.begin();
  tool.begin();
  data.begin();
  DKinematics.begin();
  stepperControl.begin();
  motion.begin();
  stateled.begin();

  Serial.println("Initialized");
  stepperControl.attach(&stepperArm1);
  stepperControl.attach(&stepperArm2);
  stepperControl.attach(&stepperArm3);

  data.currentPoint = data.homePoint;
  data.currentAngle = data.homeAngle;
  tool.PrintAngle(data.currentAngle, "Current");
  tool.PrintPoint(data.currentPoint, "Current");

  // treeTestProgram(350.0, 250.0, 75.0, 75.0, 0.4);
  lineTestProgram(350.0, 180.0, 0.5);
}

void loop() {
    // gExecuter.Run();
    if(Serial.available()) {
        char ch = (char)Serial.read();
        if(ch == '2') {
            for(uint16_t i = 0; i < MAX_SIZE; i++){
                // Serial.printf("%02X  ", c2_angles[i].identifier);
                Serial.printf("%4u  ", i);
                for(uint8_t j = 0; j < c2_angles[i].data_length_code; j++){
                    Serial.printf("%02X  ", c2_angles[i].data[j]);
                }
                Serial.println();
            }
           
            Serial.printf("checkpoint: %u\r\n", c2_point);
        }
    }
    stepperControl.update();
}

void treeTestProgram(float maxHeight, float minHeight, float maxX, float maxY, float duration) {
  Point pbuf;
  MoveDesigner md;
  Angle abuf;

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "1");

  pbuf = tool.Convert2Point(maxX, 0, minHeight);
  md.moveDuration = duration;
    DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "2");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "3");

  pbuf = tool.Convert2Point(maxX, maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "4");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "5");

  pbuf = tool.Convert2Point(0, maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "6");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "7");

  pbuf = tool.Convert2Point(-maxX, maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "8");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "9");

  pbuf = tool.Convert2Point(-maxX, 0, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "10");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "11");

  pbuf = tool.Convert2Point(-maxX, -maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "12");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "13");

  pbuf = tool.Convert2Point(0, -maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "14");

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "15");

  pbuf = tool.Convert2Point(maxX, -maxY, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "16");

  stepperControl.repeat = true;
}

void infiniteLoopTestProgram(void) {

}

void lineTestProgram(float maxHeight, float minHeight, float duration) {
  Point pbuf;
  MoveDesigner md;
  Angle abuf;

  pbuf = tool.Convert2Point(0, 0, maxHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "1");

  pbuf = tool.Convert2Point(0, 0, minHeight);
  md.moveDuration = duration;
  DKinematics.InverseKinematics(pbuf, abuf);
  md = DKinematics.InverseCalculations(pbuf, md);
  stepperControl.addMoveDesigner(md);
  tool.PrintMoveDesigner(md, "2");

  stepperControl.repeat = true;
}