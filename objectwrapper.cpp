//Object Wrapper Class
#include "objectwrapper.h"


GraphicsClass* GameObject::pMainGraph;
InputClass* GameObject::pMainInput;

//Constructor
FontObject::FontObject(int left, int top, int right, int bottom, LPWSTR text, D3DCOLOR color, DWORD placement)
{
	pRect = new RECT();
	SetRect(pRect, left, top, right, bottom);
	text_str=text;
	text_color=color;
	align=placement;

	pGraphWrapper = pMainGraph->AddObject(new FontWrapper(&pRect, &text_str, &text_color, &align));
}
//Copy Constructor
FontObject::FontObject(const FontObject&)
{
}
//Destructor
FontObject::~FontObject()
{
}


bool FontObject::Display()
{
	if(pGraphWrapper==0)
	{
		pGraphWrapper = pMainGraph->AddObject(new FontWrapper(&pRect, &text_str, &text_color, &align));
		return true;
	}
	return false; // pGraphWrapper is already displaying
}

bool FontObject::Hide()
{
	if(pGraphWrapper)
	{
		pMainGraph->RemoveObject(pGraphWrapper);
		pGraphWrapper=0;
		return true;
	}
	return false; // Object is already hidden/nonexistant
}

bool FontObject::MouseOver() // Needs More Work, Implement access to DirectFont's font size
{							//Alternatively we can ask the user to actually be mindful of the RECT* sizes  he gives...
	if((pMainInput->MGetX() >= pRect->left) &&
		(pMainInput->MGetX() <= pRect->right) &&
		(pMainInput->MGetY() >= pRect->top) &&
		(pMainInput->MGetY() <= pRect->bottom)) return true;

	return false;
}

bool FontObject::Click()
{
	if(MouseOver() && pMainInput->IsMKeyClick(1)) return true;
	return false;
}

void FontObject::CleanUp()
{
	delete pRect;
	delete text_str;
	pMainGraph->RemoveObject(pGraphWrapper);
}
