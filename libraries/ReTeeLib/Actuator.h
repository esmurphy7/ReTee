#include "Arduino.h"

class Actuator
{
	private:
		int Pin;

	public:
		void Init(int pin)
		{
			Pin = pin;
			// use LED for testing
			pinMode(Pin, OUTPUT);
		}

		void Open()
		{
			// use LED for testing
			digitalWrite(Pin, HIGH);
		}

		void Close()
		{
			// use LED for testing
			digitalWrite(Pin, LOW);
		}
};