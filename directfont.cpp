//DirectX Fonts Class
#include "directfont.h"

//Constructor (Get the D3DX device we'll be working with)
DXFonts::DXFonts(IDirect3DDevice9* device) 
{
	pDevice=device;
}

//Copy Constructor
DXFonts::DXFonts(const DXFonts&)
{
}

//Deconstructor
DXFonts::~DXFonts()
{
}

bool DXFonts::SetFont(LPCWSTR fontname, int height, int width, unsigned int thickness, 
					int MipLevels, bool italic, DWORD quality)
{
	//Checks
	if((thickness>1000) || (thickness<0)) return false; // Makes sure thickness is correct 
	

	HRESULT hresult;
	hresult=D3DXCreateFont(pDevice,
							height,						//Font Height
							width,						//Font Width; Default is 0
							thickness,					//Font Weight/Thickness; Default is FW_NORMAL which is 400.
							1,							//MipLevels; Default 1
							italic,						//Italic; Default is false
							DEFAULT_CHARSET,			//CharSet
							OUT_DEFAULT_PRECIS,			//OutputPrecision
							quality,					//Quality; Default is ANTIALISED_QUALITY
							DEFAULT_PITCH|FF_DONTCARE,	//PitchAndFamily (I really don't)
							fontname,					//Name of the font
							&pD3DX_font);				//Reference to the font pointer
														//Check them perfect lines 8-)
	
	if(FAILED(hresult)) return false; //failed loading

	return true;
}

//Shutdown function
void DXFonts::Shutdown()
{
	//Clear the font pointer
	pD3DX_font->Release();
	pD3DX_font=0;
};