
class ReTeeButton
{
	private:
		Button button = NULL;

	public:
		void Init(int pin, int mode)
		{
			button = Button(pin, mode);	
		}

		bool wasPressed()
		{
			return button.isPressed();
		}
};