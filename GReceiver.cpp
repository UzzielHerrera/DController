#include "Constants.h"
#include "Arduino.h"
#include "GReceiver.h"
#include "Queue.h"

void GReceiver::begin(){
  Serial.begin(115200);
  gCodeQueue.clear();
  
  _receiveString.reserve(100);
  _stringBackUp.reserve(100);
  _isStringComplete = false;
  _stringBackUp = "";
  _receiveString = "";
  Serial.println("\r\n\r\nGReceiver Module initialized.");
}

void GReceiver::PORTCheck(){
  while(Serial.available()>0){
    char inChar = (char) Serial.read();
    if(inChar == '\n'){
      _isStringComplete = true;
      break;
    }
    if(inChar != '\r'){
        _receiveString += inChar;
    }
  }
  if(!_isStringComplete){
    if(_receiveString.length() > 70)
      _receiveString = "";
  } else {
    if(_receiveString[0] == 'G') {
      gCodeQueue.push(_receiveString);
      _receiveString = "";
      _isStringComplete = false;
      return;
    }
  }
}
