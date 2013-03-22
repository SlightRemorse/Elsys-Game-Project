//Graphic Wrapper Class
#include "graphicwrapper.h"


//Font Wrapper

//Constructor

FontWrapper::FontWrapper(int left, int top, int right, int bottom, LPCWSTR text)
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
	delete pRect; // temporary here
}

//End Font Wrapper