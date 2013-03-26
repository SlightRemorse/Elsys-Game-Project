//System Class header
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

//Macros
#define WIN32_LEAN_AND_MEAN

//Includes
#include <Windows.h>
#include <WindowsX.h>

//System Class
#include "inputclass.h"
#include "graphicsclass.h"
#include "typeconv.h"
#include "objectwrapper.h"

#include "teststage.h"

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
	
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int screenWidth, screenHeight;

	void SetInsideFrame();
	int inScreenWidth, inScreenHeight;

	int posX, posY;
	bool busy;

	LPCWSTR main_applicationName;
	HINSTANCE main_hinstance;
	HWND main_hwnd;

	InputClass* main_Input;
	GraphicsClass* main_Graphics;

	TestStage* stage1;
};
// End System Class

// Function Prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global
static SystemClass* pApplicationHandle = 0;

#endif