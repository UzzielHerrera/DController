#include "CANSupervisor.h"

volatile CanFrame c2_angles[MAX_SIZE];
volatile uint16_t c2_point = 0;

void CANSupervisor::begin() {
    ESP32Can.setPins(CAN_TX, CAN_RX);
    ESP32Can.setRxQueueSize(5);
    ESP32Can.setTxQueueSize(5);
    ESP32Can.setSpeed(ESP32Can.convertSpeed(500));
    if(ESP32Can.begin()) {
        Serial.println("CAN bus started!");
    } else {
        Serial.println("CAN bus failed!");
    }
}

void CANSupervisor::request(int canAddress, int command) {
  CanFrame request = {0};
  request.identifier = IDENTIFIER;
  request.extd = 0;
  request.data_length_code = 2;
  request.data[0] = canAddress;
  request.data[1] = command;
  ESP32Can.writeFrame(request, 0);
}

float CANSupervisor::getFloat(void) {
  if(ESP32Can.readFrame(incomingFrame, 100)) {
    float value = (incomingFrame.data[3] << 8) + incomingFrame.data[4] + (incomingFrame.data[5] / 100.0);
    value = incomingFrame.data[2] == 1 ? +value : -value;
    // if(incomingFrame.identifier == 0xC1){
    //   Serial.printf("ID: %2X, ", incomingFrame.identifier);
    //   for(int i = 0; i < incomingFrame.data_length_code; i ++){
    //     Serial.printf("data[%d]: %02X, ", i,incomingFrame.data[i]);
    //   }
    //   Serial.println();

    // Serial.printf("ID: 0x%02X, Value:%0.2f\r\n", incomingFrame.identifier, value);
    // }
    return value;
  }
  return ERROR_FLOAT;
}

float CANSupervisor::requestSetPoint(int canAddress) {
  request(canAddress, REQUEST_SETPOINT_CMD);
  delayMicroseconds(300);
  return getFloat();
}

float CANSupervisor::requestCurrentPosition(int canAddress) {
  request(canAddress, REQUEST_CURRENT_POSITION_CMD);
  return getFloat();
}

bool CANSupervisor::getBool(void) {
  if(ESP32Can.readFrame(incomingFrame, 100)) {
    // Serial.printf("ID: 0x%02X, CMD: 0x%02X, MSG: 0x%02X\r\n", incomingFrame.identifier, incomingFrame.data[1], incomingFrame.data[2]);
    bool value = incomingFrame.data[2] == 0x01 ? true : false;
    return value;
  }
  return false;
}

bool CANSupervisor::requestDirection(int canAddress) {
  request(canAddress, REQUEST_DIR_CMD);
  return getBool();
}

bool CANSupervisor::requestEnable(int canAddress) {
  request(canAddress, REQUEST_ENABLE_CMD);
  return getBool();
}

void CANSupervisor::sendEnable(bool newState, int canAddress) {
  CanFrame stateFrame = {0};
  stateFrame.identifier = IDENTIFIER;
  stateFrame.extd = 0;
  stateFrame.data_length_code = 3;
  stateFrame.data[0] = canAddress;
  stateFrame.data[1] = ENABLE_CMD;
  stateFrame.data[2] = newState ? 0x01 : 0x00;
  ESP32Can.writeFrame(stateFrame, 0);
}

void CANSupervisor::sendSetPoint(float angle, int canAddress) {
  int x = angle * 100.0;
  CanFrame angleFrame = { 0 };
  angleFrame.identifier = IDENTIFIER;
  angleFrame.extd = 0;
  angleFrame.data_length_code = x == 0 ? 2 : 6;
  // Direction
  angleFrame.data[0] = canAddress;
  // Command
  angleFrame.data[1] = SETPOINT_CMD;
  if (x != 0) { 
    // Angle direction
    angleFrame.data[2] = x >= 0 ? 0x01 : 0x00;
    x = abs(x);
    // Angle integer msb bits 
    angleFrame.data[3] = ((x / 100) >> 8) & 0xFF;
    // Angle integer lsb bits
    angleFrame.data[4] = (x / 100) & 0xFF;
    // Angle decimals as integer
    angleFrame.data[5] = (x % 100) & 0xFF;
  }
  ESP32Can.writeFrame(angleFrame, 0);
}

void CANSupervisor::sendDirection(bool stepperDirection, int canAddress) {
  CanFrame direction = {0};
  direction.identifier = IDENTIFIER;
  direction.extd = 0;
  direction.data_length_code = 3;
  direction.data[0] = canAddress;
  direction.data[1] = DIR_CMD;
  direction.data[2] = stepperDirection ? 0x01 : 0x00;
  ESP32Can.writeFrame(direction, 0);
}

void CANSupervisor::sendStep(int canAddress) {
  CanFrame step = {0};
  step.identifier = IDENTIFIER;
  step.extd = 0;
  step.data_length_code = 3;
  step.data[0] = canAddress;
  step.data[1] = STEP_CMD;
  ESP32Can.writeFrame(step, 0);
}

bool CANSupervisor::sendSmoothMove(float angle, float time, int canAddress) {
  int32_t angleInt = angle * 100.0;
  int32_t timeInt = time * 100.0;
  CanFrame smoothFrame = { 0 };
  smoothFrame.identifier = IDENTIFIER;
  smoothFrame.extd = 0;
  smoothFrame.data_length_code = 8;

  // Direction
  smoothFrame.data[0] = canAddress;
  // Command
  smoothFrame.data[1] = SMOOTH_MOVE_CMD;
  // Angle direction
  smoothFrame.data[2] = angleInt >= 0 ? 0x01 : 0x00;
  angleInt = abs(angleInt);
  //  Angle integer msb bits
  smoothFrame.data[3] = ((angleInt / 100) >> 8) & 0xFF;
  // Angle integer lsb bits
  smoothFrame.data[4] = (angleInt / 100) & 0xFF;
  // Angle decimals as integer
  smoothFrame.data[5] = (angleInt % 100) & 0xFF;
  // Time * 100 msb
  smoothFrame.data[6] = (timeInt >> 8) & 0xFF;
  // Time * 100 lsb
  smoothFrame.data[7] = timeInt & 0xFF;

  if(canAddress == 0xC2){
      c2_angles[c2_point].identifier = smoothFrame.identifier;
      c2_angles[c2_point].data_length_code = smoothFrame.data_length_code;
      for(uint16_t j = 0; j < smoothFrame.data_length_code; j++){
        c2_angles[c2_point].data[j] = smoothFrame.data[j];
      }
      c2_point++;
      if(c2_point >= MAX_SIZE) c2_point = 0;
  }

  ESP32Can.writeFrame(smoothFrame);

  delayMicroseconds(300);

  return getBool();
}
