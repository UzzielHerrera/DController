#ifndef CANSUPERVISOR_H
#define CANSUPERVISOR_H

#include <Arduino.h>
#include "Constants.h"
#include "ESP32-TWAI-CAN.hpp"

#define ERROR_FLOAT -99999.99
#define NOP_CMD 0x00

#define SMOOTH_MOVE_CMD 0xAF
#define REQUEST_CURRENT_POSITION_CMD 0xAE

#define SETPOINT_CMD 0xA0
#define REQUEST_SETPOINT_CMD 0xA1

#define ENABLE_CMD 0xA2
#define REQUEST_ENABLE_CMD 0xA3

#define MODE_CMD 0xA4
#define REQUEST_MODE_CMD 0xA5

#define DIR_CMD 0xB0
#define REQUEST_DIR_CMD 0xB1

#define STEP_CMD 0xB2

#define MAX_SIZE 2000
extern volatile CanFrame c2_angles[MAX_SIZE];
extern volatile uint16_t c2_point;

class CANSupervisor {
    public:
        void begin(void);

        void sendEnable(bool newState, int canAddress);
        void sendSetPoint(float angle, int canAddress);
        void sendDirection(bool stepperDirection, int canAddress);
        void sendStep(int canAddress);
        bool sendSmoothMove(float angle, float time, int canAddress);

        float requestSetPoint(int canAddress);
        float requestCurrentPosition(int canAddress);
        bool requestDirection(int canAddress);
        bool requestEnable(int canAddress);
        
        float getFloat(void);
        bool getBool(void);

        CanFrame incomingFrame = {0};

    private:
        void request(int canAddress, int command);
};

extern CANSupervisor canSupervisor;

#endif