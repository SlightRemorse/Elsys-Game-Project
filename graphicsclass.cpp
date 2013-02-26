//Graphics Class
#include "graphicsclass.h"

//Constructor
GraphicsClass::GraphicsClass()
{
}

//Copy Constructor
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

//Deconstructor
GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	return true;
}


void GraphicsClass::Shutdown()
{
	return;
}


bool GraphicsClass::Frame()
{
	return true;
}


bool GraphicsClass::Render()
{
	return true;
}
