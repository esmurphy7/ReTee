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
			delay(1000);
		}

		void Close()
		{
			// use LED for testing
			digitalWrite(Pin, LOW);
			delay(1000);
		}
};