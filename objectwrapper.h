//Object Wrapper class for Sys Frame
#ifndef _OBJECT_WRAPPER_H_
#define _OBJECT_WRAPPER_H_

//Includes
#include "graphicwrapper.h"
#include "graphicsclass.h"
#include "inputclass.h"

//Object release macro
#define GameObjectRelease(p) { if(p) {(p)->CleanUp(); delete (p); (p)=0;} }

class GameObject
{
public:
	static GraphicsClass* pMainGraph;
	static InputClass* pMainInput;

	GraphicWrapper* pGraphWrapper;

	virtual bool Hide()=0;
	virtual bool Display()=0;

	virtual void CleanUp()=0;
	virtual bool MouseOver()=0;
	virtual bool Click()=0;
};

class FontObject: public GameObject
{
public:
	FontObject(int, int, int, int, LPWSTR, D3DCOLOR=0xFFFFFFFF, DWORD=DT_CENTER);
	FontObject(const FontObject&);
	~FontObject();

	bool Hide();
	bool Display();

	void CleanUp();

	bool MouseOver();
	bool Click();

	DWORD align;
	D3DCOLOR text_color;
	RECT* pRect;
	LPWSTR text_str;
};

//Globals

#endif