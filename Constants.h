#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

typedef struct{
  float x;
  float y;
  float z;
} Point;

typedef struct{
  float x;
  float y;
  float z;
} Vector;

typedef struct{
  float theta1;
  float theta2;
  float theta3;
} Angle;

#define S2US 1000000

// Pin Definition.
// #define ARM1_STEP_PIN 4
// #define ARM1_DIR_PIN 2
// #define ARM2_STEP_PIN 18
// #define ARM2_DIR_PIN 5
// #define ARM3_STEP_PIN 23
// #define ARM3_DIR_PIN 19

#define BTN_MODE 35
#define BTN_MODE_COOLDOWN 3000

#define ARM1_SWITCH 4
#define ARM2_SWITCH 5
#define ARM3_SWITCH 6

// #define MANUAL_ENCODER_COOLDOWN 3000
// #define MANUAL_ENCODER_A 13
// #define MANUAL_ENCODER_B 12
// #define MANUAL_ENCODER_SW 32
// #define MANUAL_ENCODER_SW_COOLDOWN 5000
// #define ENCODER_SCALER 10

#define MAX_STEPPER_SPEED 500 //uSec for step

#define RED_LED_PIN 15
#define GREEN_LED_PIN 16
#define EXECUTING_ISR_CODE 17
#define NAN_LED_PIN 18
#define MODE_LED_PIN 10

#define BLINK_LAPSE 150
#define TIME_BETWEEN_BLINK_CYCLES 1500

#define MAX_STEPPERS 3
#define MAX_DESIGNER_MOVES 100
#define MAX_GCODES 60
#define MAX_GPARAMETERS 14

#define DEFAULT_FEED_SPEED 3000.0

#define MOVING_AREA_X 150.0
#define MOVING_AREA_Y 150.0
#define MOVING_AREA_Z 300.0

#define MOVING_AREA_LARGEST_DIAMETER 500

#define UPPER_BASE_OFFSET 21.5
#define LOWER_BASE_OFFSET 10.0
#define END_EFFECTOR_OFFSET 15.0

#define THETA1_HOME_POSITION 17.00
#define THETA2_HOME_POSITION 17.00
#define THETA3_HOME_POSITION 17.00

#define MAX_THETA1 20.0
#define MAX_THETA2 20.0
#define MAX_THETA3 20.0

#define LCD_SDA 21
#define LCD_SCL 22
#define LCD_DIRECTION 39
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Geometry.
// Lower arm axle intersection
#define DELTA_E 145.49 // DeltaV4
// Upper arm axle intersection
#define DELTA_F 314.64 // DeltaV4
// Lower arm length
#define DELTA_RE 253.0 // DeltaV4
// Upper arm length
#define DELTA_RF 120.0 // DeltaV4

#define MM_PER_LINEAR_SEGMENT 2.0  //mm

#define THETA1_STEPS_PER_2PI 600
#define THETA2_STEPS_PER_2PI 600
#define THETA3_STEPS_PER_2PI 600

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

#define TRANSMISION_RELATION 3.0
#define SECTIONS_PER_MOVE 10.0

#define CAN_TX 5
#define CAN_RX 4

#define IDENTIFIER 0xC0

#define ANGLE_TOLERANCE 0.01

#endif