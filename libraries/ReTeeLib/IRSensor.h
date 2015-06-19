#include "Arduino.h"

// Wrapper class for infrared sensor.
// The greater the distance value, the closer an object is to the sensor.
// 1cm is equal to about 15 sensor units.
class IRSensor
{
	private:
		int Pin;
		const int MIN_DISTANCE = 200;
		const int MAX_DISTANCE = 300;

	public:
		void Init(int pin)
		{
			Pin = pin;
		}

		bool BallIsDetected()
		{
			int currentDistance = GetDistance();

			// if the current distance is outside the range
			if((currentDistance < MIN_DISTANCE) or (currentDistance > MAX_DISTANCE))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		int GetDistance()
		{
			int currentDistance = analogRead(Pin);
			return currentDistance;
		}	

		void PrintDistance()
		{
			Serial.print("Current Distance: ");
			Serial.println(GetDistance());
		}
};