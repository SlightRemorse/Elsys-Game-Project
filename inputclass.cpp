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
		pressed_keys=0;
		main_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	// Press key
	if(main_keys[input]!=true) {
		pressed_keys++;
		main_keys[input] = true;
	}
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// Release key
	if(main_keys[input]!=false) {
		pressed_keys--;
		main_keys[input] = false;
	}
	return;
}
void InputClass::MouseCoord(unsigned int x, unsigned int y)
{
	//Set mouse cursor coordinates within the window
	mouseX=x;
	mouseY=y;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Key state
	return main_keys[key];
}

int InputClass::KeysDown() 
{
	// Return number of keys pressed
	return pressed_keys;
}

int InputClass::MouseGetX()
{
	return mouseX;
}

int InputClass::MouseGetY()
{
	return mouseY;
}