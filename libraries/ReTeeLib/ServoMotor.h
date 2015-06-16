#include "Arduino.h"
#include <math.h>

class ServoMotor
{
	private:
		int Pin;
		Servo servo;
		const int EXTENDED_POSITION = 180;
		const int REST_POSITION = 90;
		const int PICKUP_POSITION = 10;

		// Moves the servo motor to a specific degree angle
		void MoveToDeg(int targetPos)
		{
			//PrintPosition();
			Serial.print("Target pos: ");
			Serial.println(targetPos);

			// get current position before executing the movement
			int curPos = servo.read();

			// move the servo to target position
			servo.write(targetPos);

			// Calculate time to delay the servo to let it catch up to system
			// get difference in current position vs target position
			int diff = targetPos - curPos;

			// get absolute value of difference, multiply it by 15ms
			int delayTime = sqrt((diff*diff)) * 15;

			/*
			Serial.print("Delaying for: ");
			Serial.println(delayTime);
			Serial.println();	
			*/
			delay(delayTime);
		}

	public:
		void Init(int pin)
		{
			Pin = pin;
			servo.attach(pin);
		}

		void MoveToExtended()
		{
			MoveToDeg(EXTENDED_POSITION);
		}

		void MoveToRest()
		{
			MoveToDeg(REST_POSITION);
		}			

		void MoveToPickup()
		{
			MoveToDeg(PICKUP_POSITION);
		}

		void MoveToPos(int pos)
		{
			MoveToDeg(pos);
		}

		int GetPosition()
		{
			return servo.read();
		}

		void SweepTest()
		{
			servo.attach(Pin);

			int pos = 0;
			for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
			{                                  // in steps of 1 degree 
				servo.write(pos);              // tell servo to go to position in variable 'pos' 
				delay(15);                       // waits 15ms for the servo to reach the position 
			} 
			for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
			{                                
				servo.write(pos);              // tell servo to go to position in variable 'pos' 
				delay(15);                       // waits 15ms for the servo to reach the position 
			} 
		}

		void PrintPosition()
		{
			Serial.print("Servo pos: ");
  			Serial.println(GetPosition());
		}
};