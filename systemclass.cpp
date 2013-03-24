//System Class
#include "systemclass.h"


//Constructor
SystemClass::SystemClass() 
{
	main_Input = 0;
	main_Graphics = 0;
}

//Copy Constructor
SystemClass::SystemClass(const SystemClass&)
{
}

//Deconstructor
SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	bool result;

	//Initialize the busy flag for key combinations
	busy=false;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	//User Input Object
	main_Input = new InputClass;
	if(!main_Input)
	{
		return false;
	}
	main_Input->Initialize();


	// Graphics Object
	main_Graphics = new GraphicsClass;
	if(!main_Graphics)
	{
		return false;
	}
	result = main_Graphics->Initialize(screenWidth, screenHeight, main_hwnd);
	if(!result)
	{
		return false;
	}

	stage1 = new TestStage(main_Graphics, main_Input); //Initializing the test stage

	return true;
}


void SystemClass::Shutdown()
{
	// Clear the graphics object.
	if(main_Graphics)
	{
		main_Graphics->Shutdown();
		delete main_Graphics;
		main_Graphics = 0;
	}

	// Clear the input object.
	if(main_Input)
	{
		delete main_Input;
		main_Input = 0;
	}

	// Shutdown the program, not Windows itself :D
	ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool exit, result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// The main loop
	exit = false;
	while(!exit)
	{
		// Message Handling
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to exit the program.
		if(msg.message == WM_QUIT)
		{
			exit = true;
		}
		else
		{
			// Processing everything else
			result = Frame();
			if(!result)
			{
				exit = true;
			}
		}

	}

	return;
}

//Test Variables
GraphicWrapper* MousePos;

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Mouse

		//Getting the position of the mouse on mouse movement
		case WM_MOUSEMOVE:
		{
			main_Input->MCoord(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			main_Graphics->RemoveObject(MousePos);
			MousePos=main_Graphics->AddObject(new FontWrapper(0, 0, 50, 50, 
				JoinWSTR(SafeWSTR(L"Mouse Pos: "), 
						JoinWSTR(IntToWSTR(main_Input->MGetX()), IntToWSTR(main_Input->MGetY()), true, true)
						, true)));
			return 0;
		}
		//Mouse Left Button Click
		case WM_LBUTTONDOWN:
		{	
			//MessageBox(main_hwnd, IntToWSTR(wparam), L"Mouse Click", MB_OK);
			main_Input->MKeyDown(wparam);
			return 0;
		}
		//Fix Release Keys
		case WM_LBUTTONUP:
		{	
			//MessageBox(main_hwnd, IntToWSTR(wparam), L"Mouse Release", MB_OK);
			main_Input->MKeyUp(1);
			return 0;
		}

		//Mouse Right Button Click
		case WM_RBUTTONDOWN:
		{
			main_Input->MKeyDown(wparam);
			return 0;
		}

		case WM_RBUTTONUP:
		{
			main_Input->MKeyUp(2);
			return 0;
		}
		//End Mouse

		//Keyboard
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			main_Input->KeyDown((unsigned int)wparam);

			//Cycle Windowed/FullScreen
			if((busy==false) && 
			   (main_Input->KeysDown()==2) && 
			   (main_Input->IsKeyDown(VK_RETURN)) && 
			   (main_Input->IsKeyDown(VK_CONTROL))) 
			{
				busy=true;
				if(FULLSCREEN==false) 
				{
					//Fullscreen
					posX=posY=0;
					screenWidth = dmScreenSettings.dmPelsWidth;
					screenHeight = dmScreenSettings.dmPelsHeight;
					SetWindowLongPtr(main_hwnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_VISIBLE);
					MoveWindow(main_hwnd, 0, 0, dmScreenSettings.dmPelsWidth, dmScreenSettings.dmPelsHeight, true);
					ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
					main_Graphics->ResetDevice(true, dmScreenSettings.dmPelsWidth, dmScreenSettings.dmPelsHeight);
					
					FULLSCREEN=true;
				} else 
				{
					//Windowed mode
					screenWidth = GetSystemMetrics(SM_CXSCREEN)*0.75;
					screenHeight = GetSystemMetrics(SM_CYSCREEN)*0.75;
					posX=(GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
					posY=(GetSystemMetrics(SM_CXSCREEN) - screenHeight)  / 2;
					SetWindowLongPtr(main_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_VISIBLE);
					MoveWindow(main_hwnd, posX, posY, screenWidth, screenHeight, true);
					ChangeDisplaySettings(NULL, 0);
					main_Graphics->ResetDevice(false, screenWidth, screenHeight);

					FULLSCREEN=false;
				}
			}
			return 0;
		}
		//End Keyboard

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			busy=false;
			main_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Non-processed Messages
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

// Code Loop
bool SystemClass::Frame()
{
	stage1->Run();
	
	if(main_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//Implement Making Steaks for Happy Stanev

	// Do the frame processing for the graphics object.
	if(main_Graphics->Frame()) return true;

	return false;
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	// Get an external pointer to this object.
	pApplicationHandle = this;

	// Get the instance of this application.
	main_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	main_applicationName = L"The Game";

	// Setup the Window Class
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = main_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = main_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	// Register the Window Class.
	RegisterClassEx(&wc);

	// Determine desktop resolution.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup FullScreen mode struct for later use
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
	dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Set Windowed Size;
	screenWidth*=0.75;
	screenHeight*=0.75;

	// Place the window in the middle of the screen.
	posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

	// Create the window with the screen settings and get the handle to it.
	if(FULLSCREEN) 
	{
		main_hwnd = CreateWindowEx(WS_EX_APPWINDOW, main_applicationName, main_applicationName, 
								   WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
								   posX, posY, screenWidth, screenHeight, NULL, NULL, main_hinstance, NULL);
	} else 
	{
		main_hwnd = CreateWindowEx(WS_EX_APPWINDOW, main_applicationName, main_applicationName, 
								   WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
								   posX, posY, screenWidth, screenHeight, NULL, NULL, main_hinstance, NULL);
	}
	
	// Bring the window up on the screen and set it as main focus.
	ShowWindow(main_hwnd, SW_SHOW);
	SetForegroundWindow(main_hwnd);
	SetFocus(main_hwnd);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the Cursor if not shown.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULLSCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(main_hwnd);
	main_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(main_applicationName, main_hinstance);
	main_hinstance = NULL;

	// Release the pointer to this class.
	pApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// Default: Pass to System Class
		default:
		{
			return pApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}