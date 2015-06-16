#include "Arduino.h"
#include "ClickButton.h"

class Button
{
	private:
		ClickButton clickButton = NULL;

	public:
		void Init(int pin)
		{
			clickButton = ClickButton(pin, LOW, CLICKBTN_PULLUP);
		}

		int GetClickCount()
		{
			int clickCount = clickButton.clicks;
			return clickCount;
		}

		bool HasBeenPressed()
		{
			if(clickButton.clicks != 0)
			{
				return true;
			}

			return false;
		}
};