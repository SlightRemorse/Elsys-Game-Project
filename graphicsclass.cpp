//Graphics Class
#include "graphicsclass.h"

//Constructor
GraphicsClass::GraphicsClass()
{
	pGraph_DX9=0;
	pDX9_device=0;
}

//Copy Constructor
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

//Deconstructor
GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND current_hwnd)
{
	hwnd = current_hwnd; // Copy the hwnd

	HRESULT hresult;
	
	//Create DirectX9 object
	pGraph_DX9 = Direct3DCreate9(D3D_SDK_VERSION);
	if(pGraph_DX9==0) return false;

	//Setup DX 3D Present Parameters struct
	memset(&DX9pp, 0, sizeof(DX9pp));
	DX9pp.BackBufferCount=1; // single back buffer
	DX9pp.MultiSampleType=D3DMULTISAMPLE_NONE; // No Multisampling yet
	DX9pp.MultiSampleQuality=0; // No Multisampling yet
	DX9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // Throw away previous frames, we don't need them
	DX9pp.hDeviceWindow=hwnd; // The Window
	DX9pp.Flags=0; // No flags
	DX9pp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT; //Default Refresh Rate
	DX9pp.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT; //Default Presentation rate
	DX9pp.EnableAutoDepthStencil=false; //No depth/stencil buffer

	ToggleFullscreen(FULLSCREEN, screenWidth, screenHeight);

	//Initialize Background Color to Black
	BGCOLOR=0x00000000;

	//Create the device
	hresult = pGraph_DX9->CreateDevice(	D3DADAPTER_DEFAULT, // Default monitor
										D3DDEVTYPE_HAL, // Use Hardware acceleration
										hwnd, // Our Window
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, //Process vertices in software. (Slower, but works on all graphic cards)
										&DX9pp, // Present Parameters struct
										&pDX9_device); // Pointer to the device we just created
	
	if(FAILED(hresult))
	{ 
		//Handle failed Device creation
		return false;
	}

	//Any side features adding
	
	//Fonts
	pDX_Fonts = new DXFonts(pDX9_device);
	pDX_Fonts->SetFont(L"Arial", 20); //Loading Default 20px Arial font
	
	return true;
}


bool GraphicsClass::Frame()
{
	bool successful;
	HRESULT hresult;
	hresult=pDX9_device->TestCooperativeLevel();

	if(SUCCEEDED(hresult)) 
	{
		//Device cooperative (working)
		//Clearing the buffer
		hresult = pDX9_device->Clear(0,  //Number of rectangles to clear, we're clearing everything so set it to 0
								NULL, //Pointer to the rectangles to clear, NULL to clear whole display
								D3DCLEAR_TARGET,   //What to clear.  We don't have a Z Buffer or Stencil Buffer
								BGCOLOR, //Colour to clear to (AA RR GG BB)
								1.0f,  //Value to clear ZBuffer to, doesn't matter since we don't have one
								0);   //Stencil clear value, again, we don't have one, this value doesn't matter
		if(FAILED(hresult))
		{
			// Handle error
			return false;
		}

		//Rendering the new buffer
		pDX9_device->BeginScene();
		successful=Render();
		pDX9_device->EndScene();
	
		//Displaying
		if(successful) pDX9_device->Present(NULL, //Source rectangle to display, NULL for all of it
										NULL, //Destination rectangle, NULL to fill whole display
										NULL, //Target window, if NULL uses device window set in CreateDevice
										NULL); //Dirty Region, set it to NULL
	}
	else if(hresult==D3DERR_DEVICELOST)
	{
		//Device Lost

	} 
	else if(hresult==D3DERR_DEVICENOTRESET)
	{
		//Device Lost, but able to be reset
		hresult=pDX9_device->Reset(&DX9pp);

		pDX_Fonts = new DXFonts(pDX9_device);
		pDX_Fonts->SetFont(L"Arial", 20); //Loading Default 20px Arial font
		
		if(SUCCEEDED(hresult)) 
		{
			return true;

		} else 
		{
			return false;

		}
	}
	return true;
}


bool GraphicsClass::Render()
{
	for(int i=0; i<vec_pGObj.size(); i++)
	{
		if(vec_pGObj[i]->classtype==FONT)
		{
			pDX_Fonts->pD3DX_font->DrawText(NULL, // Sprite
											((FontWrapper*)vec_pGObj[i])->text_str, //Text string
											-1,
											((FontWrapper*)vec_pGObj[i])->pRect, //Text position
											DT_LEFT|DT_NOCLIP, //Aligned left, doesn't clip
											((FontWrapper*)vec_pGObj[i])->text_color); //Text Color

		}
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	//Any side features cleaning
	
	//Fonts
	pDX_Fonts->Shutdown();
	delete pDX_Fonts;
	pDX_Fonts=0;

	//Clear the DX9 device object.
	if(pDX9_device) pDX9_device->Release();
	pDX9_device=0;

	//Clear the DX9 object.
	if(pGraph_DX9) pGraph_DX9->Release();
	pGraph_DX9=0;
	return;
}

bool GraphicsClass::ToggleFullscreen(bool fullscr, int screenWidth, int screenHeight) 
{
	if(fullscr==true) 
	{
		DX9pp.Windowed=false;
		DX9pp.BackBufferWidth=screenWidth;
		DX9pp.BackBufferHeight=screenHeight;
		// Implement Format Support check via CheckDeviceType
		DX9pp.BackBufferFormat=D3DFMT_R5G6B5;
	} else
	{
		RECT* FullWindow = new RECT(); 
		RECT* InsideWindow = new RECT();
		GetClientRect(hwnd, InsideWindow);
		GetWindowRect(hwnd, FullWindow);
		int xdiff = (FullWindow->right - FullWindow->left) - InsideWindow->right;
		int ydiff = (FullWindow->bottom - FullWindow->top) - InsideWindow->bottom;
		delete FullWindow;
		delete InsideWindow;

		DX9pp.Windowed=true;
		DX9pp.BackBufferWidth=screenWidth-xdiff;
		DX9pp.BackBufferHeight=screenHeight-ydiff;
		DX9pp.BackBufferFormat=D3DFMT_UNKNOWN; // Desktop default
	}
	return true;
}

bool GraphicsClass::ResetDevice(bool fullscr, int screenWidth, int screenHeight) {
	HRESULT hresult;

	// Set the DX9 Present Parameters
	ToggleFullscreen(fullscr, screenWidth, screenHeight);

	// Reset device and check for errors.
	hresult=pDX9_device->Reset(&DX9pp);

	pDX_Fonts = new DXFonts(pDX9_device);
	pDX_Fonts->SetFont(L"Arial", 20); //Loading Default 20px Arial font

	if(FAILED(hresult)) 
	{
		return false;
	} else
	{
		return true;
	}
}

//Adding Graphic Objects
GraphicWrapper* GraphicsClass::AddObject(GraphicWrapper* pWrapper)
{
	vec_pGObj.push_back(pWrapper);
	return pWrapper;
}

//Removing Graphic Objects
bool GraphicsClass::RemoveObject(GraphicWrapper* pWrapper)
{
	for(int i=0; i<vec_pGObj.size(); i++)
	{
		if(vec_pGObj[i]==pWrapper)
		{
			vec_pGObj.erase(vec_pGObj.begin()+i);
			pWrapper->CleanUp();
			delete pWrapper;
			return true; // Object found and eraced
		}
	}
	return false; // Object not found :(
}