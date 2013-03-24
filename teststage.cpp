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

bool TestStage::Run()
{
	
	pMainGraphics->RemoveObject(keys);

	LPWSTR string = SafeWSTR(L"Keys pressed:");
	for(int i=0; i<256; i++)
	{
		if(pMainInput->IsKeyDown(i)) string=JoinWSTR(string, IntToWSTR(i), true, true);
	}
	keys=pMainGraphics->AddObject(new FontWrapper(0,20,50,70, string));


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
												pMainInput->MGetX()+200, pMainInput->MGetY()+200,
												SafeWSTR(L"X")));
		else
		{
			pMainGraphics->RemoveObject(test);
			test=pMainGraphics->AddObject(new FontWrapper(pMainInput->MGetX(), pMainInput->MGetY(), 
												pMainInput->MGetX()+200, pMainInput->MGetY()+200,
												SafeWSTR(L"X")));
		}
	}
	return true;
	
}