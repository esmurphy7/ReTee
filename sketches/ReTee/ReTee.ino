
// Headers ========================
#include <Servo.h>

#include "State.h"
#include "Button.h"
#include "ServoMotor.h"
#include "IRSensor.h"
#include "Actuator.h"
// ================================


// Pin definitions ================
int servoPinIn = 3;
int sensorPinIn = A0;
int LEDPinOut = 2;
//int actuatorPinOut = ?;
// int powerPinIn = ?;
// int resetPinIn = ?;
// int calibratePinIn = ?;
// ================================


// System state ==================
//State currentState;
int currentState;
// ================================

// Hardware Objects =======================
Button resetButton;
ServoMotor servo;
//Servo servo;
IRSensor sensor;
Actuator actuator;
// ================================

void setup()
{
  // Turn the Serial Protocol ON
  Serial.begin(9600);
  
  // Start in off state
  currentState = OFF;     
 
  // Setup hardware components
  //servo.attach(servoPinIn);
  servo.Init(servoPinIn);
  servo.MoveToRest();
  
  actuator.Init(LEDPinOut);
  
  sensor.Init(sensorPinIn);
  
}

void loop()
{
  // Testing
  const bool debug = false;
  if(debug)
  {
    servo.MoveToPos(90);
    servo.PrintPosition();    
    
    servo.MoveToPos(100);
    servo.PrintPosition();
    
    servo.MoveToPos(80);
    servo.PrintPosition();
  }
  
  // State Machine Implementation
  //Action previousAction;
  //Action latestAction;
  
  // check if power pressed
  //latestAction = checkPowerButton();
  
  // check if calibrate pressed
  //latestAction = checkCalibrateButton();
  
  // check if reset pressed
  //latestAction = checkResetButton();
  
  // check if sensor has timedout
  //latestAction = checkSensorTimeout();
  
  // move to new state if signals sensed
  /*
  if(previousAction != latestAction)
  { 
     currentState = currentState.NextState(latestAction);
  }
  */
  
  // run a loop of the current state
  //currentState.Run();
  
  // previousAction = latestAction;
  
  switch(currentState)
  {
    case OFF:
      runOFFState();
      break;
    case IDLE:
      runIDLEState();
      break;
    case CALIBRATING:
      runCALIBRATINGState();
      break;
    case TEEING:
      runTEEINGState();
      break;
    default:
      Serial.println("Error: Invalid current state");
      break;
  } 
 
 // update current state
 //
 
}

void runOFFState()
{
  
}

void runIDLEState()
{
  
}

void runCALIBRATINGState()
{
  
}

void runTEEINGState()
{
  
}
