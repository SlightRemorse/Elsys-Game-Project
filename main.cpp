// Main Entry Point
#define CATCH_CONFIG_MAIN  // This tell CATCH to provide a main() - only do this in one cpp file
#include "systemclass.h"
#include "catch.hpp"

//---------systemclass Files
TEST_CASE("SystemClass creation", "Notes")
{
	SystemClass* testobj = new SystemClass();

	REQUIRE(testobj);
	REQUIRE(testobj->main_Graphics==0);
	REQUIRE(testobj->main_Input==0);

	delete testobj;
}

//---------graphicsclass Files
TEST_CASE("GraphicsClass creation", "Notes")
{
	GraphicsClass* testobj = new GraphicsClass();
	REQUIRE(testobj);
	REQUIRE(testobj->pGraph_DX9==0);
	REQUIRE(testobj->pDX9_device==0);

	delete testobj;
}


TEST_CASE("GraphicClass AddObject/RemoveObject test", "Notes")
{
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;

	RECT* REC = new RECT();
	LPWSTR Text = SafeWSTR(L"String");
	D3DCOLOR Color = 0xFFFFFFFF;
	DWORD Align = DT_CENTER;
	FontWrapper* testobj = new FontWrapper(&REC, &Text, &Color, &Align);

	REQUIRE(pGC->vec_pGObj.size()==0);
	REQUIRE(pGC->AddObject(testobj)==testobj);
	REQUIRE(pGC->vec_pGObj.size()==1);

	REQUIRE(pGC->RemoveObject(testobj)==true);
	REQUIRE(pGC->vec_pGObj.size()==0);
	REQUIRE(pGC->RemoveObject(testobj)==false);
	
	testobj = new FontWrapper(&REC, &Text, &Color, &Align);
	pGC->AddObject(testobj);
	testobj = new FontWrapper(&REC, &Text, &Color, &Align);
	pGC->AddObject(testobj);

	REQUIRE(pGC->vec_pGObj.size()==2);
	
	delete REC;
	delete Text;
	delete testobj;
}

//---------inputclass Files
TEST_CASE("InputClass Initialization test", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();
	REQUIRE(testobj->pressed_keys==0);
	
	bool failed=false;
	for(int i=0; i<256; i++)
	{
		if(testobj->main_keys[i]) failed=true;
	}
	for(int i=0; i<3; i++)
	{
		if(testobj->mouse_click[i] || testobj->mouse_keys[i]) failed=true;
	}
	REQUIRE(!failed);

	delete testobj;
}

TEST_CASE("InputClass KeyDown/KeyUp", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	testobj->KeyDown(5);

	REQUIRE(testobj->main_keys[5]==1);
	REQUIRE(testobj->pressed_keys==1);

	testobj->KeyDown(6);

	REQUIRE(testobj->main_keys[6]==1);
	REQUIRE(testobj->pressed_keys==2);

	testobj->KeyUp(5);
	REQUIRE(testobj->main_keys[5]==0);
	REQUIRE(testobj->pressed_keys==1);

	delete testobj;
}

TEST_CASE("InputClass Mouse: MKeyDown/MKeyUp", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	testobj->MKeyDown(2);
	REQUIRE(testobj->mouse_keys[2]==1);

	testobj->MKeyUp(2);
	REQUIRE(testobj->mouse_keys[2]==0);

	delete testobj;

}

TEST_CASE("Mouse Coord setting/getting", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	testobj->MCoord(5,5);
	REQUIRE(testobj->MGetX()==5);
	REQUIRE(testobj->MGetY()==5);

	testobj->MCoord(2,7);
	REQUIRE(testobj->MGetX()==2);
	REQUIRE(testobj->MGetY()==7);

	delete testobj;
}

TEST_CASE("IsKeyDown / IsMKeyDown test", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	REQUIRE(testobj->IsKeyDown(2)==testobj->main_keys[2]);
	REQUIRE(testobj->IsMKeyDown(2)==testobj->mouse_keys[2]);

	delete testobj;
}

TEST_CASE("SetMouseClicks test", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	testobj->SetMouseClicks();

	REQUIRE(testobj->IsMKeyClick(2)==0);
	REQUIRE(testobj->IsMKeyDown(2)==0);

	testobj->MKeyDown(2);

	testobj->SetMouseClicks();

	REQUIRE(testobj->IsMKeyDownHold(2)==1);
	REQUIRE(testobj->IsMKeyDown(2)==1);

	testobj->MKeyUp(2);
	testobj->SetMouseClicks();

	REQUIRE(testobj->IsMKeyClick(2)==0);
	REQUIRE(testobj->IsMKeyDown(2)==0);

	delete testobj;
}

TEST_CASE("Mouse Click vs Mouse Down test", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	

	testobj->MKeyDown(1);

	REQUIRE(testobj->IsMKeyDownHold(1)==0);
	REQUIRE(testobj->IsMKeyClick(1)==1);

	testobj->SetMouseClicks();

	REQUIRE(testobj->IsMKeyDownHold(1)==1);
	REQUIRE(testobj->IsMKeyClick(1)==0);

	testobj->MKeyUp(1);

	testobj->SetMouseClicks();

	REQUIRE(testobj->IsMKeyDownHold(1)==0);
	REQUIRE(testobj->IsMKeyClick(1)==0);

	delete testobj;
}

TEST_CASE("Pressed keys", "Notes")
{
	InputClass* testobj = new InputClass();
	testobj->Initialize();

	testobj->KeyDown(5);
	REQUIRE(testobj->KeysDown()==testobj->pressed_keys);

	delete testobj;
}

//---------typeconv Files
TEST_CASE("SafeWSTR test", "Notes")
{
	LPWSTR text = SafeWSTR(L"text");
	REQUIRE(!wcscmp(text, L"text"));
	REQUIRE((sizeof(text)/sizeof(WCHAR)), 5);
	REQUIRE(wcscmp(text, L"nottext"));

	delete text;

	REQUIRE(wcscmp(text, L"text"));
}

TEST_CASE("IntToWSTR test", "Notes")
{
	LPWSTR text = IntToWSTR(20);
	REQUIRE((sizeof(text)/sizeof(WCHAR)), 10);
	REQUIRE(!wcscmp(text, L"20"));
	
	delete text;

	REQUIRE(wcscmp(text, L"20"));
}

TEST_CASE("CharSTRToWSTR test", "Notes")
{
	LPWSTR text = CharSTRToLPWSTR("Test");
	REQUIRE((sizeof(text)/sizeof(WCHAR)), 5);
	REQUIRE(!wcscmp(text, L"Test"));

	delete text;
}

TEST_CASE("JoinWSTR 2 args", "Somethingyoudon'tseebutisneeded")
{
	LPWSTR str1 = SafeWSTR(L"str1");
	LPWSTR str2 = SafeWSTR(L"str2");

	LPWSTR result = JoinWSTR(false, str1, str2);

	REQUIRE(!wcscmp(result, L"str1str2"));
	REQUIRE(!wcscmp(str1, L"str1"));
	REQUIRE(!wcscmp(str2, L"str2"));

	result = JoinWSTR(true, str1, str2);

	REQUIRE(!wcscmp(result, L"str1str2"));
	REQUIRE(wcscmp(str1, L"str1"));
	REQUIRE(wcscmp(str2, L"str2"));
}

TEST_CASE("JoinWSTR 3 args", "Somethingyoudon'tseebutisneeded")
{
	LPWSTR str1 = SafeWSTR(L"str1");
	LPWSTR str2 = SafeWSTR(L"str2");
	LPWSTR str3 = SafeWSTR(L"str3");

	LPWSTR result = JoinWSTR(false, str1, str2, str3);

	REQUIRE(!wcscmp(result, L"str1str2str3"));
	REQUIRE(!wcscmp(str1, L"str1"));
	REQUIRE(!wcscmp(str2, L"str2"));
	REQUIRE(!wcscmp(str3, L"str3"));

	result = JoinWSTR(true, str1, str2, str3);

	REQUIRE(!wcscmp(result, L"str1str2str3"));
	REQUIRE(wcscmp(str1, L"str1"));
	REQUIRE(wcscmp(str2, L"str2"));
	REQUIRE(wcscmp(str3, L"str3"));
}

TEST_CASE("JoinWSTR 4 args", "Somethingyoudon'tseebutisneeded")
{
	LPWSTR str1 = SafeWSTR(L"str1");
	LPWSTR str2 = SafeWSTR(L"str2");
	LPWSTR str3 = SafeWSTR(L"str3");
	LPWSTR str4 = SafeWSTR(L"str4");

	LPWSTR result = JoinWSTR(false, str1, str2, str3, str4);

	REQUIRE(!wcscmp(result, L"str1str2str3str4"));
	REQUIRE(!wcscmp(str1, L"str1"));
	REQUIRE(!wcscmp(str2, L"str2"));
	REQUIRE(!wcscmp(str3, L"str3"));
	REQUIRE(!wcscmp(str4, L"str4"));

	result = JoinWSTR(true, str1, str2, str3, str4);

	REQUIRE(!wcscmp(result, L"str1str2str3str4"));
	REQUIRE(wcscmp(str1, L"str1"));
	REQUIRE(wcscmp(str2, L"str2"));
	REQUIRE(wcscmp(str3, L"str3"));
	REQUIRE(wcscmp(str4, L"str4"));
}

TEST_CASE("JoinWSTR 5 args", "Somethingyoudon'tseebutisneeded")
{
	LPWSTR str1 = SafeWSTR(L"str1");
	LPWSTR str2 = SafeWSTR(L"str2");
	LPWSTR str3 = SafeWSTR(L"str3");
	LPWSTR str4 = SafeWSTR(L"str4");
	LPWSTR str5 = SafeWSTR(L"str5");

	LPWSTR result = JoinWSTR(false, str1, str2, str3, str4, str5);

	REQUIRE(!wcscmp(result, L"str1str2str3str4str5"));
	REQUIRE(!wcscmp(str1, L"str1"));
	REQUIRE(!wcscmp(str2, L"str2"));
	REQUIRE(!wcscmp(str3, L"str3"));
	REQUIRE(!wcscmp(str4, L"str4"));
	REQUIRE(!wcscmp(str5, L"str5"));

	result = JoinWSTR(true, str1, str2, str3, str4, str5);

	REQUIRE(!wcscmp(result, L"str1str2str3str4str5"));
	REQUIRE(wcscmp(str1, L"str1"));
	REQUIRE(wcscmp(str2, L"str2"));
	REQUIRE(wcscmp(str3, L"str3"));
	REQUIRE(wcscmp(str4, L"str4"));
	REQUIRE(wcscmp(str5, L"str5"));
}

//---------objectwrapper Files
TEST_CASE("Font Wrapper creation", "Notes")
{
	RECT* REC = new RECT();
	LPWSTR Text = SafeWSTR(L"String");
	D3DCOLOR Color = 0xFFFFFFFF;
	DWORD Align = DT_CENTER;
	FontWrapper* testobj = new FontWrapper(&REC, &Text, &Color, &Align);
	REQUIRE(testobj->classtype==FONT);
	REQUIRE(testobj->ppRect==&REC);
	REQUIRE(testobj->ptext_str==&Text);
	REQUIRE(testobj->ptext_color==&Color);
	REQUIRE(testobj->pAlign==&Align);

	delete REC;
	delete Text;
	delete testobj;
}

//---------fontobject Files
TEST_CASE("FontObject Creation", "Notes")
{
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	LPWSTR text = SafeWSTR(L"string");
	FontObject* testobj = new FontObject(0, 0, 10, 10, text, 0xFFFFFFF1, DT_LEFT);
	
	//Test the Rectangle
	REQUIRE(testobj->pRect->left==0);
	REQUIRE(testobj->pRect->top==0);
	REQUIRE(testobj->pRect->right==10);
	REQUIRE(testobj->pRect->bottom==10);

	//Test the string
	REQUIRE(testobj->text_str==text);

	//Test the color
	REQUIRE(testobj->text_color==0xFFFFFFF1);

	//Test the alignment
	REQUIRE(testobj->align==DT_LEFT);

	delete testobj;
	delete pGC;
}

TEST_CASE("FontObject Creation 2", "Notes")
{
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	LPWSTR text = SafeWSTR(L"string");
	FontObject* testobj = new FontObject(0, 0, 10, 10, text);
	
	//Test the Rectangle
	REQUIRE(testobj->pRect->left==0);
	REQUIRE(testobj->pRect->top==0);
	REQUIRE(testobj->pRect->right==10);
	REQUIRE(testobj->pRect->bottom==10);

	//Test the string
	REQUIRE(testobj->text_str==text);

	//Test the color
	REQUIRE(testobj->text_color==0xFFFFFFFF);

	//Test the alignment
	REQUIRE(testobj->align==DT_CENTER);

	delete testobj;
	delete pGC;
}

TEST_CASE("FontObject Wrapper manipulation", "Notes")
{
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	REQUIRE(pGC->vec_pGObj.size()==0);

	LPWSTR text = SafeWSTR(L"string");
	FontObject* testobj = new FontObject(0, 0, 10, 10, text, 0xFFFFFFF1, DT_LEFT);
	
	REQUIRE(pGC->vec_pGObj.size()==1);

	REQUIRE(testobj->Display()==false);
	REQUIRE(pGC->vec_pGObj.size()==1);

	REQUIRE(testobj->Hide()==true);
	REQUIRE(testobj->pGraphWrapper==0);
	REQUIRE(pGC->vec_pGObj.size()==0);
	REQUIRE(testobj->Hide()==false);
	REQUIRE(pGC->vec_pGObj.size()==0);

	REQUIRE(testobj->Display()==true);
	REQUIRE(testobj->pGraphWrapper!=0);
	REQUIRE(pGC->vec_pGObj.size()==1);

	delete text;
	delete testobj;
	delete pGC;
}

TEST_CASE("GameObjectRelease macro", "Notes")
{
	InputClass* input = new InputClass();
	input->Initialize();
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	GameObject::pMainInput = input;
	LPWSTR text = SafeWSTR(L"Text");

	FontObject* testobj = new FontObject(0,0,10,10,text);

	GameObjectRelease(testobj);
	
	REQUIRE(wcscmp(text, L"Text"));
	REQUIRE(pGC->vec_pGObj.size()==0);
}

TEST_CASE("Font Object Mouse Over", "Notes")
{
	InputClass* input = new InputClass();
	input->Initialize();
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	GameObject::pMainInput = input;

	FontObject* testobj = new FontObject(0,0,10,10,SafeWSTR(L"Text"));

	input->MCoord(5,5);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(5,10);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(5,0);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(10,5);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(0,5);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(10,10);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(0,0);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(10,5);
	REQUIRE(testobj->MouseOver()==true);

	input->MCoord(11,5);
	REQUIRE(testobj->MouseOver()==false);
	
	input->MCoord(-1,5);
	REQUIRE(testobj->MouseOver()==false);
	
	input->MCoord(5,18);
	REQUIRE(testobj->MouseOver()==false);

	input->MCoord(5,-2);
	REQUIRE(testobj->MouseOver()==false);
	
	input->MCoord(-1,11);
	REQUIRE(testobj->MouseOver()==false);
	
	
	GameObjectRelease(testobj);
	delete pGC;
	delete input;
}

TEST_CASE("Font Object Mouse Click", "Notes")
{
	InputClass* input = new InputClass();
	input->Initialize();
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;
	GameObject::pMainInput = input;

	FontObject* testobj = new FontObject(0,0,10,10,SafeWSTR(L"Text"));

	input->MCoord(5,5);

	input->MKeyDown(1);

	REQUIRE(testobj->Click()==true);

	input->SetMouseClicks();

	REQUIRE(testobj->Click()==false);
	
	
	GameObjectRelease(testobj);
	delete pGC;
	delete input;
}

TEST_CASE("Move X / Move Y", "Notes")
{
	GraphicsClass* pGC = new GraphicsClass();
	GameObject::pMainGraph = pGC;

	FontObject* testobj = new FontObject(0,0,10,10,SafeWSTR(L"Text"));

	REQUIRE(((testobj->pRect->left==0) && (testobj->pRect->right==10)));
	testobj->MoveX(5);
	REQUIRE(((testobj->pRect->left==5) && (testobj->pRect->right==15)));
	testobj->MoveX(-10);
	REQUIRE(((testobj->pRect->left==-5) && (testobj->pRect->right==5)));

	REQUIRE(((testobj->pRect->top==0) && (testobj->pRect->bottom==10)));
	testobj->MoveY(5);
	REQUIRE(((testobj->pRect->top==5) && (testobj->pRect->bottom==15)));
	testobj->MoveY(-5);
	REQUIRE(((testobj->pRect->top==0) && (testobj->pRect->bottom==10)));



	GameObjectRelease(testobj);
	delete pGC;
}

//---------teststage Files
TEST_CASE("Test Stage creation", "Notes")
{
	InputClass* input = new InputClass();
	GraphicsClass* graph = new GraphicsClass();

	int x = 1024;
	int y = 768;

	TestStage* testobj = new TestStage(graph, input, &x, &y);


	REQUIRE(testobj->pMainGraphics==graph);
	REQUIRE(testobj->pMainInput==input);
	
	REQUIRE(testobj->pScreenX==&x);
	REQUIRE(testobj->pScreenY==&y);

	REQUIRE(testobj->options == 0);
	REQUIRE(testobj->exit == 0);
	REQUIRE(testobj->play == 0);
	REQUIRE(testobj->above_message == 0);
	REQUIRE(testobj->player == 0);
	REQUIRE(testobj->pts == 0);
	REQUIRE(testobj->powerup == 0);

	REQUIRE(testobj->playerhealth==2);

	REQUIRE(testobj->speed==1);
	REQUIRE(testobj->boost==0);

	REQUIRE(testobj->score==0);

	REQUIRE(testobj->gamestate==0); 
	REQUIRE(testobj->stage == 0); 

	REQUIRE(testobj->refire==0);
	REQUIRE(testobj->spawnspeed==750);

}
/* broken
TEST_CASE("TestStage Menu", "Notes")
{
	InputClass* input = new InputClass();
	GraphicsClass* graph = new GraphicsClass();

	int x = 1024;
	int y = 768;

	TestStage* testobj = new TestStage(graph, input, &x, &y);

	REQUIRE(testobj->play==0);
	REQUIRE(testobj->options==0);
	REQUIRE(testobj->exit==0);

	testobj->Menu();

	REQUIRE(testobj->play!=0);
	REQUIRE(testobj->options!=0);
	REQUIRE(testobj->exit!=0);

	REQUIRE(!wcscmp(testobj->options->text_str,L"Options"));

	input->MCoord(x/2, y/2-15);

	REQUIRE(testobj->options->MouseOver()==true);
	REQUIRE(!wcscmp(testobj->options->text_str,L"Options"));




}*/