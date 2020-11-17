#include <Chrono.h>

Chrono myChrono;
static int timerDelay = 1000;
static int ledPin = 13;
static int ledState = LOW;


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  
  if(myChrono.hasPassed(timerDelay)){
      myChrono.restart();

      if(ledState == LOW)
        ledState = HIGH;
      else
         ledState = LOW;
         
      digitalWrite(ledPin, ledState);
  }

  Serial.println("Loop still Running");
}
