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
	// Initialize all keyboard keys.
	for(int i=0; i<256; i++)
	{
		pressed_keys=0;
		main_keys[i] = false;
	}
	// Initialize Mouse keys.
	for(int i=0; i<3; i++)
	{
		mouse_click[i] = false;
		mouse_keys[i] = false;
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

void InputClass::MKeyDown(unsigned int input)
{
	//Mouse Click
	mouse_keys[input] = true;
	return;
}

void InputClass::MKeyUp(unsigned int input)
{
	//Mouse Release
	mouse_keys[input] = false;
	return;
}


void InputClass::MCoord(unsigned int x, unsigned int y)
{
	//Set mouse cursor coordinates within the window
	mouseX=x;
	mouseY=y;
	return;
}

void InputClass::SetMouseClicks()
{
	for(int i=0; i<3; i++)
	{
		if(IsMKeyDown(i)) 
			MKeyClick(i, true);
		else MKeyClick(i, false);
	}
}

void InputClass::MKeyClick(unsigned int x, bool flag)
{
	mouse_click[x]=flag;
}

bool InputClass::IsMKeyDownHold(unsigned int x)
{
	return mouse_click[x];
}

bool InputClass::IsKeyDown(unsigned int key)
{
	// Key state
	return main_keys[key];
}

bool InputClass::IsMKeyDown(unsigned int key)
{
	return mouse_keys[key];
}

bool InputClass::IsMKeyClick(unsigned int key)
{
	if((IsMKeyDown(key)) && (IsMKeyDownHold(key)==false)) return true;
	else return false;
}

int InputClass::KeysDown() 
{
	// Return number of keys pressed
	return pressed_keys;
}

int InputClass::MGetX()
{
	return mouseX;
}

int InputClass::MGetY()
{
	return mouseY;
}