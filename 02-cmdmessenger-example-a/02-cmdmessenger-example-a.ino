// *** Arduino CmdMessenger IN Example ***
// Download CmsMessenger from: http://thijs.elenbaas.net/2013/09/arduino-to-pc-messaging/
// Or Install it from Tools > Manage Libraries...
//
// https://codebender.cc/search/find/?query=CmdMessenger
// Using the CmdMessenger for IO commands exchanged with PC:
// * Message format when using Serial Monitor: Id, param1, ..., paramN;
//
// * Possible to change the default parameter's separator (,) and command separater (;);
// * Possible to define up to 50 cmds (in both directions Tx/Rx) and
//   including 4 default command codes for the generic error handling;
// * Possible to increase message slots by changing MAXCALLBACKS macro in CmdMessenger.h;
// * All command IDs can be sent and/or received as long as we attach a function for each command;
// * Both Emmiter and Receiver must agree on the same list of command IDs.
//
// This scketch:
// - Handles received commands by attaching 1 function:
//   i) for setting led on/off (CMD_SETLED Id Command);
// - Messages from Serial Monitor -> Arduino must be like:
//   i) 0, 1; // Cmd 0, Turn led 1 (on)
//  ii) 0, 0; // Cmd 0, Turn led 0 (off)
//
// Example:
//  CMD_SETLED 0,1,0;



#include <CmdMessenger.h>  // CmdMessenger

// Blinking led variables 
const int pinLed13 = 13;  // Pin of internal Led
bool ledState = 0; // Current state of Led

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger msg = CmdMessenger(Serial);

// List of Command Ids
enum
{
  CMD_SETLED = 0, // Command to request led to be set in specific state
};

// Callbacks define on which received commands we take action 
void attachCommandCallbacks()
{
  msg.attach(CMD_SETLED, callbackOnSetLed);
}

// Callback function that sets led on/off
void callbackOnSetLed()
{
  // Read led state argument, interpreted from Rx string as boolean
  ledState = msg.readBoolArg();
  // Set led state
  digitalWrite(pinLed13, (ledState ? HIGH:LOW) );
}

// Setup function
void setup() 
{
  // Listen on serial connection for messages from the PC
  // 115200 is the max speed on Arduino Uno, Mega, with AT8u2 USB
  // Use 57600 for the Arduino Duemilanove and others with FTDI Serial
  Serial.begin(9600); 

  // Adds newline to every command for visual commodity
  msg.printLfCr();   

  // Attach all callback methods
  attachCommandCallbacks();

  // Set pin led for output
  pinMode(pinLed13, OUTPUT);
}

// Loop function
void loop() 
{
  // Process incoming serial data, and perform callbacks
  msg.feedinSerialData();
}
