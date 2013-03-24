//Graphic Wrapper Class
#include "graphicwrapper.h"


//Font Wrapper

//Constructor

FontWrapper::FontWrapper(int left, int top, int right, int bottom, LPWSTR text)
{
	classtype=FONT;
	text_str=text;
	pRect = new RECT();
	SetRect(pRect, left, top, right, bottom);
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

void FontWrapper::CleanUp() // Freeing Memory
{
	delete pRect;
	delete text_str;
}

void FontWrapper::MoveRectBy(int x, int y)
{
	pRect->left+=x;
	pRect->right+=x;
	pRect->top+=y;
	pRect->bottom+=y;
}

//End Font Wrapper