// Main Entry Point
#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	
	// Create and initialize the system object.
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}
	result = System->Initialize();
	if(result)
	{
		System->Run();
	}

	// Shutdown and clean the system object.
	System->Shutdown();
	delete System; // Not System32
	System = 0;

	return 0;
}