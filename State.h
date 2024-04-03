#ifndef STATE_H
#define STATE_H

#include "Constants.h"
#include "Arduino.h"
#include "DirectIO.h"

class StateLed{
  public:
    // StateLed();
    void begin();
    void Red();
    void Green();
    void isr_on();
    void isr_off();
    void BlinkUpdate();
    int blinksPerCycle;
    uint16_t _blinkCycleTime;
    uint16_t _blinkLapse;
  private:
    bool _canBlink;
    uint32_t _lastBlinkCycle;
    uint32_t _lastBlink;
    bool _lastState;
    int _currentBlink;
};

extern StateLed stateled;

#endif