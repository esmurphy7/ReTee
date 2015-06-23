// Headers ========================
#include <Servo.h>
#include <Button.h>

#include "ReTeeLib.h"
// ================================

// Pin definitions ================
const int servoPinIn = 3;
const int sensorPinIn = A0;
const int LEDPinOut = 2;
//const int actuatorPinOut = ?;
//const int powerPinIn = ?;
const int resetPinIn = 4;
//const int calibratePinIn = ?;
// ================================

// Hardware Objects ===============
ReTeeButton resetButton;
ServoMotor servo;
IRSensor sensor;
Actuator actuator;
// ================================

// State Functions ================
void OFFStateEnterFunction()
{
  // return arm to rest position
  // close actuator
  // record data?  
  // shut off power
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
  servo.MoveToRest();
  
  // close actuator
  actuator.Close();
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
}

void TEEINGStateEnterFunction()
{
  // close actuator
  actuator.Close();
  
  // move arm to pickup position
  servo.MoveToPickup();
}
void TEEINGStateUpdateFunction()
{
  // if no ball is detected
  if(!sensor.BallIsDetected())
  {
    Serial.println("NO BALL DETECTED");
    
    // wait to collect ball
    servo.WaitForBall();
    
    // move arm to extended position
    servo.MoveToExtended();
    
    // open actuator
    actuator.Open();
    
    // close actuator
    actuator.Close();
    
    // move arm to pickup position
    servo.MoveToPickup();
  }
  else
  {
    Serial.println("BALL DETECTED");
  }
}
void TEEINGStateExitFunction()
{
}
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


// Button Checkers =================
Action CheckResetButton()
{   
   if(resetButton.wasPressed())
   {   
     Serial.println("RESET PRESSED");
     delay(1000); 
   }
   else
   {
     Serial.println("RESET NOT PRESSED");
     delay(1000);  
     return NONE;
   }
   
   if(&stateMachine.getCurrentState() == &IDLEState)
   {
     return TEE;
   }
   else
   {
     return RESET; 
   }   
}
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
  
  resetButton.Init(resetPinIn, PULLDOWN);
  
}

void loop()
{
  // Testing
  const int debug = false;
  if(debug)
  {
  }
  else
  {
    // State Machine Implementation
    Action previousAction;
    Action latestAction;
    
    latestAction = CheckResetButton();
    
    // don't transition if the action hasn't changed
    if(previousAction != latestAction)
    {  
      // transition based on latest action
      switch(latestAction)
      {
        case NONE:
          break;
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
          Serial.print("Error: invalid action: ");
          Serial.println(latestAction);
          delay(1000);
          break;
      }
    }
    
    // record this loop's action
    previousAction = latestAction;
    
    // Update the state machine, must be called
    stateMachine.update();
    delay(1000);
  }
  
  
}

