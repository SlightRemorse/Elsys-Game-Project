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
	FontWrapper(int, int, int, int, LPWSTR, D3DCOLOR=0xFFFFFFFF);
	FontWrapper(const FontWrapper&);
	~FontWrapper();

	void CleanUp();
	void MoveRectBy(int, int);

	D3DCOLOR text_color;
	RECT* pRect;
	LPWSTR text_str;
};

//Globals

#endif

