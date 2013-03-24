//Test Stage for Sys Frame Class
#include "teststage.h"

//Constructor
TestStage::TestStage(GraphicsClass* pGraphics, InputClass* pInput)
{
	pMainGraphics=pGraphics; // getting the current Graphics Class we're using
	pMainInput=pInput; // getting the current Input Class we're using
	test=0;
}
//Copy Constructor
TestStage::TestStage(const TestStage&)
{
}
//Deconstructor
TestStage::~TestStage()
{
}

//Temporary
FontObject* mouse=0;
FontObject* obj=0;
bool TestStage::Run()
{
	
	pMainGraphics->RemoveObject(keys);
	if(mouse)
	{
		mouse->CleanUp();
		delete mouse;
	}

	if(obj)
	{
		obj->CleanUp();
		delete obj;
	}
	obj = new FontObject(250, 250, 340, 270, SafeWSTR(L"Click To Exit"));
	if(obj->MouseOver()) ((FontWrapper*)obj->pGraphWrapper)->text_color=0xFFFF0000;
	if(obj->Click()) return false;

	LPWSTR string = SafeWSTR(L"Keys pressed:");
	for(int i=0; i<256; i++)
	{
		if(pMainInput->IsKeyDown(i)) string=JoinWSTR(true, string, SafeWSTR(L" "), IntToWSTR(i));
	}
	keys=pMainGraphics->AddObject(new FontWrapper(0,20,50,40, string));

	LPWSTR string2 = SafeWSTR(L"Mouse pressed:");
	for(int i=0; i<50; i++)
	{
		if(pMainInput->IsMKeyDown(i)) string2=JoinWSTR(true, string2, SafeWSTR(L" "), IntToWSTR(i));
	}
	mouse = new FontObject(0, 80, 50, 100, string2); 

	if(pMainInput->IsKeyDown(VK_LEFT))
	{
		if(test) ((FontWrapper*)test)->MoveRectBy(-2,0);
	}
	if(pMainInput->IsKeyDown(VK_RIGHT))
	{
		if(test) ((FontWrapper*)test)->MoveRectBy(2,0);
	}
	if(pMainInput->IsKeyDown(VK_UP))
	{
		if(test) ((FontWrapper*)test)->MoveRectBy(0,-2);
	}
	if(pMainInput->IsKeyDown(VK_DOWN))
	{
		if(test) ((FontWrapper*)test)->MoveRectBy(0,2);
	}

	//Blue
	if(pMainInput->IsKeyDown(69))
	{
		if(pMainGraphics->BGCOLOR%0x100<0xF0) 
		{
			pMainGraphics->BGCOLOR+=0x10;
		}
	}
	if(pMainInput->IsKeyDown(68))
	{
		if(pMainGraphics->BGCOLOR%0x100>=0x10) 
		{
			pMainGraphics->BGCOLOR-=0x10;
		}
	}

	//Green
	if(pMainInput->IsKeyDown(87))
	{
		if(pMainGraphics->BGCOLOR%0x10000<0xF000) 
		{
			pMainGraphics->BGCOLOR+=0x1000;
		}
	}
	if(pMainInput->IsKeyDown(83))
	{
		if(pMainGraphics->BGCOLOR%0x10000>0x1000) 
		{
			pMainGraphics->BGCOLOR-=0x1000;
		}
	}

	//Red
	if(pMainInput->IsKeyDown(81))
	{
		if(pMainGraphics->BGCOLOR%0x1000000<0xF00000) 
		{
			pMainGraphics->BGCOLOR+=0x100000;
		}
	}
	if(pMainInput->IsKeyDown(65))
	{
		if(pMainGraphics->BGCOLOR%0x1000000>0x100000) 
		{
			pMainGraphics->BGCOLOR-=0x100000;
		}
	}

	if(pMainInput->IsMKeyDown(1)){
		pMainGraphics->BGCOLOR = pMainInput->MGetX() + pMainInput->MGetY()*0xFFF;
	}
	//Awesome, isn't it?))))
	if(pMainInput->IsMKeyDown(2)){
		if(test==0)	test=pMainGraphics->AddObject(new FontWrapper(pMainInput->MGetX(), pMainInput->MGetY(), 
												pMainInput->MGetX()+10, pMainInput->MGetY()+20,
												SafeWSTR(L"X"), 0xFFFF0000));
		else
		{
			pMainGraphics->RemoveObject(test);
			test=pMainGraphics->AddObject(new FontWrapper(pMainInput->MGetX(), pMainInput->MGetY(), 
												pMainInput->MGetX()+10, pMainInput->MGetY()+20,
												SafeWSTR(L"X"), 0xFFFF0000));
		}
	}
	//I love this
	if((pMainInput->IsKeyDown(VK_CONTROL)) && (pMainInput->IsKeyDown(88))) 
	{
		pMainGraphics->RemoveObject(test);
		test=0;
	}
	return true;
	
}