//Input Class (User Input)
#include "inputclass.h"

//Constructor
InputClass::InputClass()
{
}

//Copy Constructor
InputClass::InputClass(const InputClass& other)
{
}

//Deconstructor
InputClass::~InputClass()
{
}


void InputClass::Initialize()
{
	// Initialize all the keys to being released and not pressed.
	for(int i=0; i<256; i++)
	{
		main_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	// Press key
	main_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// Release key
	main_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Key state
	return main_keys[key];
}