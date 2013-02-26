//System Class header
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

//Macros
#define WIN32_LEAN_AND_MEAN

//Includes
#include <Windows.h>

//System Class
#include "inputclass.h"
#include "graphicsclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	
private:
	LPCWSTR main_applicationName;
	HINSTANCE main_hinstance;
	HWND main_hwnd;

	InputClass* main_Input;
	GraphicsClass* main_Graphics;
};
// End System Class

// Function Prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global
static SystemClass* ApplicationHandle = 0;

#endif