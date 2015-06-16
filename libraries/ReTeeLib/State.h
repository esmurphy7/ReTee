#include "Arduino.h"
#include "HashMap.h"

enum Action
{
	POWER = 0,
	CALIBRATE,
	RESET,
	SENSOR_TIMEOUT
};

enum States
{
	OFF = 0,
	IDLE,
	CALIBRATING,
	TEEING
};


// Base state
class State
{
	protected:
		static const int SIZE = 4;	
		HashType<int,int> targetStatesByActionRaw[SIZE];	
		HashMap<int,int> targetStatesByAction;

	public:
		void Init()
		{
			targetStatesByAction = HashMap<int,int>(targetStatesByActionRaw, SIZE);
		}
};

// OFF state
class OFFState : public State
{
	public:
		void Init()
		{
			State::Init();
			targetStatesByAction[0](POWER, IDLE);
		}
};

// IDLE state
class IDLEState : public State
{
	public:	
};

// TEEING state
class TEEINGState : public State
{
	public:		
};

// CALIBRATING state
class CALIBRATINGState : public State
{
	public:	
};
