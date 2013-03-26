//Graphic Wrapper Class
#include "graphicwrapper.h"


//Font Wrapper

//Constructor

FontWrapper::FontWrapper(RECT** ppRECT, LPWSTR* pText, D3DCOLOR* pColor, DWORD* Align)
{
	classtype=FONT;
	ptext_color=pColor;
	ptext_str=pText;
	ppRect = ppRECT;
	pAlign=Align;
}

//Copy Constructor
FontWrapper::FontWrapper(const FontWrapper&)
{
	//Not sure if I should touch this...
}

//Deconstructor
FontWrapper::~FontWrapper()
{
}

//End Font Wrapper