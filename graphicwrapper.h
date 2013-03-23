//Graphic Wraper header (Wrapper for multiple different graphic objects)
#ifndef _GRAPHIC_WRAPPER_H_
#define _GRAPHIC_WRAPPER_H_

//Includes
#include <d3dx9.h>


#pragma comment (lib, "d3dx9.lib")
//Graphic Object Class

enum GraphType
{
	NONE,
	FONT,
};

class GraphicWrapper
{
public:
	GraphType classtype;

	virtual void CleanUp()=0;
};
//End Graphic Object Class

class FontWrapper: public GraphicWrapper
{
public:
	FontWrapper(int, int, int, int, LPCWSTR);
	FontWrapper(const FontWrapper&);
	~FontWrapper();

	void CleanUp();
	void MoveRectBy(int, int);

	RECT* pRect;
	LPCWSTR text_str;
};

//Globals

#endif

