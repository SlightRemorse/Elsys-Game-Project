//Object Wrapper class for Sys Frame
#ifndef _OBJECT_WRAPPER_H_
#define _OBJECT_WRAPPER_H_

//Includes
#include "graphicwrapper.h"
#include "graphicsclass.h"
#include "inputclass.h"

class GameObject
{
public:
	static GraphicsClass* pMainGraph;
	static InputClass* pMainInput;

	GraphicWrapper* pGraphWrapper;

	virtual bool MouseOver()=0;
	virtual bool Click()=0;
};

class FontObject: public GameObject
{
public:
	FontObject(int, int, int, int, LPWSTR, D3DCOLOR=0xFFFFFFFF);
	FontObject(const FontObject&);
	~FontObject();

	void CleanUp();

	bool MouseOver();
	bool Click();
};

//Globals

#endif