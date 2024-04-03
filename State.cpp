#include "State.h"

// StateLed::StateLed(){
void StateLed::begin(void) {
  _blinkCycleTime = TIME_BETWEEN_BLINK_CYCLES;
  _blinkLapse = BLINK_LAPSE;
  _canBlink = true;
  _lastBlink = 0;
  _lastBlinkCycle = 0;
  _currentBlink = 0;
  _lastState = false;
  blinksPerCycle = 0;
  directModeOutput(RED_LED_PIN);
  directWriteHigh(RED_LED_PIN);
  directModeOutput(GREEN_LED_PIN);
  directWriteHigh(GREEN_LED_PIN);
  directModeOutput(EXECUTING_ISR_CODE);
  directWriteLow(EXECUTING_ISR_CODE);
  directModeOutput(MODE_LED_PIN);
  directWriteLow(MODE_LED_PIN);
  // Serial.println("State Led Module initialized.");
}

void StateLed::Green(){
  directWriteHigh(RED_LED_PIN);
  directWriteLow(GREEN_LED_PIN);
}

void StateLed::Red(){
  directWriteHigh(GREEN_LED_PIN);
  directWriteLow(RED_LED_PIN);
}

void StateLed::isr_on(){
  directWriteHigh(EXECUTING_ISR_CODE);
}

void StateLed::isr_off(){
  directWriteLow(EXECUTING_ISR_CODE);
}

void StateLed::BlinkUpdate(){
  if(blinksPerCycle!=0){
    if(!_canBlink && millis() - _lastBlinkCycle >= _blinkCycleTime){
      _lastBlinkCycle = millis();
      _canBlink = true;
    }

    if(_canBlink && millis() - _lastBlink >= _blinkLapse){
      _lastBlink = millis();
      if(_currentBlink < blinksPerCycle){
        if(_lastState)
            directWriteLow(MODE_LED_PIN);
        else
            directWriteHigh(MODE_LED_PIN);
        if(_lastState) _currentBlink++;
        _lastState = !_lastState;
      } else {
        _currentBlink = 0;
        _canBlink = false;
      }
    }
  } else {
    if(!_lastState){
      directWriteHigh(MODE_LED_PIN);
    }
  }
}
