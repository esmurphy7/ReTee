// Headers ========================
#include <Servo.h>

#include "Button.h"
#include "ServoMotor.h"
#include "IRSensor.h"
#include "Actuator.h"
#include "FiniteStateMachine.h"
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

// Hardware Objects ===============
//Button resetButton;
ServoMotor servo;
IRSensor sensor;
Actuator actuator;
// ================================

// State Functions =========
void OFFStateEnterFunction()
{
  // return arm to rest position
  // shut off power
  // close actuator
  // record data?
}
void OFFStateUpdateFunction()
{
}
void OFFStateExitFunction()
{
}

void IDLEStateEnterFunction()
{
  // move arm to rest position
  // close actuator
}
void IDLEStateUpdateFunction()
{
}
void IDLEStateExitFunction()
{  
}

void CALIBRATINGStateEnterFunction()
{
  // move arm to extended position
  // close actuator
}
void CALIBRATINGStateUpdateFunction()
{
  // wait for user to place device
}
void CALIBRATINGStateExitFunction()
{
  // move arm to rest position
}

void TEEINGStateEnterFunction()
{
  // close actuator
  // move arm to pickup position
}
void TEEINGStateUpdateFunction()
{
  // wait x seconds to collect ball
  // move arm to extended position
  // open actuator
  // close actuator
  // move arm to pickup position
}
void TEEINGStateExitFunction()
{
  // move arm to rest position
}
// ================================

// State Transition Triggers =======
enum Actions
{
  POWER = 0,
  CALIBRATE,
  RESET,
  TEE
};
// ================================

// State Definitions ===============
State OFFState = State(OFFStateEnterFunction, 
                      OFFStateUpdateFunction, 
                      OFFStateExitFunction);

State IDLEState = State(IDLEStateEnterFunction, 
                      IDLEStateUpdateFunction, 
                      IDLEStateExitFunction);
                      
State CALIBRATINGState = State(CALIBRATINGStateEnterFunction,
                      CALIBRATINGStateUpdateFunction, 
                      CALIBRATINGStateExitFunction);

State TEEINGState = State(TEEINGStateEnterFunction, 
                      TEEINGStateUpdateFunction,
                      TEEINGStateExitFunction);

// Start system in idle state                      
FSM stateMachine = FSM(IDLEState);
// ================================



void setup()
{  
  // Turn the Serial Protocol ON
  Serial.begin(9600);
  
  // Setup hardware components
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
  Actions previousAction;
  Actions latestAction;
  
  // latestAction = checkForButtonClicks and SensorTimeout
  
  // don't transition if the action hasn't changed
  if(previousAction != latestAction)
  {  
    // transition based on latest action
    switch(latestAction)
    {
      case POWER: 
        stateMachine.transitionTo(OFFState);
        break;
      case CALIBRATE: 
        stateMachine.transitionTo(CALIBRATINGState);
        break;
      case RESET: 
        stateMachine.transitionTo(IDLEState);
        break;
      case TEE: 
        stateMachine.transitionTo(TEEINGState);
        break;
      default: 
        Serial.print("Error: invalid action read: ");
        Serial.println(latestAction);
        break;
    }
  }
  
  // record this loop's action
  previousAction = latestAction;
  
  // Update the state machine, must be called
  stateMachine.update();
}






