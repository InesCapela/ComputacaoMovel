/*
 * Turn on LED A:   CMD_SETLED 0,1,1;
 * Turn off LED A:   CMD_SETLED 0,1,0;
 * 
 * Turn on LED B:   CMD_SETLED 0,2,1;
 * Turn off LED B:   CMD_SETLED 0,2,0;
 * 
 */


#include <CmdMessenger.h>

const int pinLed1 = 13;
const int pinLed2 = 12;
bool ledState1 = false;
bool ledState2 = false;

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger msg = CmdMessenger(Serial);

// List of Command Ids
enum {
  CMD_SETLED = 0, // Command to request led to be set in specific state
};

// Callbacks define on which received commands we take action 
void attachCommandCallbacks(){
  msg.attach(CMD_SETLED, callbackOnSetLed);
}

// Callback function that sets led on/off
void callbackOnSetLed(){
  
  int ledNumber = msg.readInt32Arg();
  int state = msg.readBoolArg();

  if(ledNumber == 1){
    ledState1 = !ledState1;
    digitalWrite(pinLed1, ledState1);
    
  } else {
    ledState2 = !ledState2;
    digitalWrite(pinLed2, ledState2);
  }
}



void setup() {
  Serial.begin(9600); 
  msg.printLfCr();   
  attachCommandCallbacks();
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT); 
}

void loop() {
  msg.feedinSerialData();
}
