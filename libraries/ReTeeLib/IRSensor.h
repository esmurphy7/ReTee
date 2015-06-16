#include "Arduino.h"

class IRSensor
{
	private:
		int Pin;
		int currentDistance = -1;
		const int MIN_DISTANCE = 200;
		const int MAX_DISTANCE = 250;

	public:
		void Init(int pin)
		{
			Pin = pin;
		}

		bool BallIsDetected()
		{
			return not ((currentDistance < MIN_DISTANCE) or (currentDistance > MAX_DISTANCE));
		}

		int ReadDistance()
		{
			int currentDistance = analogRead(Pin);
			return currentDistance;
		}	
};