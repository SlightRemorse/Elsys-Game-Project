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
};
//End Graphic Object Class

class FontWrapper: public GraphicWrapper
{
public:
	FontWrapper(RECT**, LPWSTR*, D3DCOLOR*, DWORD*);
	FontWrapper(const FontWrapper&);
	~FontWrapper();

	DWORD* pAlign;
	D3DCOLOR* ptext_color;
	RECT** ppRect;
	LPWSTR* ptext_str;
};

//Globals

#endif

