//Object Wrapper Class
#include "objectwrapper.h"


GraphicsClass* GameObject::pMainGraph;
InputClass* GameObject::pMainInput;

//Constructor
FontObject::FontObject(int left, int top, int right, int bottom, LPWSTR text, D3DCOLOR color)
{
	pGraphWrapper = pMainGraph->AddObject(new FontWrapper(left, top, right, bottom, text, color));
}
//Copy Constructor
FontObject::FontObject(const FontObject&)
{
}
//Destructor
FontObject::~FontObject()
{
}

bool FontObject::MouseOver() // Needs More Work, Implement access to DirectFont's font size
{
	if((pMainInput->MGetX() >= ((FontWrapper*)pGraphWrapper)->pRect->left) &&
		(pMainInput->MGetX() <= ((FontWrapper*)pGraphWrapper)->pRect->left
								+wcslen(((FontWrapper*)pGraphWrapper)->text_str)*9) &&
		(pMainInput->MGetY() >= ((FontWrapper*)pGraphWrapper)->pRect->top) &&
		(pMainInput->MGetY() <= ((FontWrapper*)pGraphWrapper)->pRect->bottom)) return true;

	return false;
}

bool FontObject::Click()
{
	if(MouseOver() && pMainInput->IsMKeyDown(1)) return true;
	return false;
}

void FontObject::CleanUp()
{
	pMainGraph->RemoveObject(pGraphWrapper);
}
