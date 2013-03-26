//Test Stage for Sys Frame Class
#include "teststage.h"

//Constructor
TestStage::TestStage(GraphicsClass* pGraphics, InputClass* pInput, int* screenwidth, int* screenheight)
{
	pMainGraphics=pGraphics; // getting the current Graphics Class we're using
	pMainInput=pInput; // getting the current Input Class we're using

	//Setting the pointers to the window size integers
	pScreenX=screenwidth;
	pScreenY=screenheight;

	//Nulling the Object pointers
	options = 0;
	exit = 0;
	play = 0;

	stage = 0; // 0 Menu, 1 Run
}
//Copy Constructor
TestStage::TestStage(const TestStage&)
{
}
//Deconstructor
TestStage::~TestStage()
{
}

//Example Menu
bool TestStage::Menu()
{
	//Releasing the objects and all their memory
	GameObjectRelease(play);
	GameObjectRelease(options);
	GameObjectRelease(exit);

	play = new FontObject(*pScreenX/2-16, *pScreenY/2-50, *pScreenX/2+16, *pScreenY/2-32, SafeWSTR(L"Play"));
	options = new FontObject(*pScreenX/2-28, *pScreenY/2-25, *pScreenX/2+28, *pScreenY/2-6, SafeWSTR(L"Options"));
	exit = new FontObject(*pScreenX/2-14, *pScreenY/2, *pScreenX/2+16, *pScreenY/2+16, SafeWSTR(L"Exit"));
	
	if(exit->Click()) return false;

	if(options->MouseOver()) 
	{
		delete ((FontWrapper*)options->pGraphWrapper)->text_str; // Remember to clean up your string pointers
		((FontWrapper*)options->pGraphWrapper)->text_color=0xFFFF0000;
		((FontWrapper*)options->pGraphWrapper)->text_str=SafeWSTR(L"Not yet implemented");
		((FontWrapper*)options->pGraphWrapper)->pRect->left-=47;
	}

	if(play->MouseOver()) ((FontWrapper*)play->pGraphWrapper)->text_color=0x99FFFFFF;
	
	if(play->Click()) 
	{
			stage = 1;
			//Releasing the objects and all their memory
			GameObjectRelease(play);
			GameObjectRelease(options);
			GameObjectRelease(exit);
			return true;
	}

	if(exit->MouseOver()) ((FontWrapper*)exit->pGraphWrapper)->text_color=0x99FFFFFF;
	
	return true;
}

bool TestStage::Run()
{
	if(pMainInput->IsKeyDown(VK_ESCAPE)) stage = 0;
	
	return true;
}