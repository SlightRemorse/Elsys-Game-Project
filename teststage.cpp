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
bool up=false;
bool TestStage::Menu()
{
	//Initialize the stage's objects
	if(!play) play = new FontObject(*pScreenX/2-18, *pScreenY/2-40, *pScreenX/2+18, *pScreenY/2-20, SafeWSTR(L"Play"));
	if(!options) options = new FontObject(*pScreenX/2-25, *pScreenY/2-20, *pScreenX/2+25, *pScreenY/2, SafeWSTR(L"Options"));
	if(!exit) exit = new FontObject(*pScreenX/2-18, *pScreenY/2, *pScreenX/2+18, *pScreenY/2+20, SafeWSTR(L"Exit"));
	
	//Make sure they're displayed in case they were Hidden before
	play->Display();
	options->Display();
	exit->Display();

	if(exit->Click()) return false;

	if(options->MouseOver()) 
	{
		delete  options->text_str; // Remember to clean up your string pointers
				options->text_str=SafeWSTR(L"Not yet implemented");
				if(options->text_color==0xFFFFFFFF) options->text_color=0xFFFF0000;
				if((!up) && (options->text_color%0xFFFFFFFF>0x00FFFFFF)) options->text_color-=0x05000000;
				else up=true;
				if((up) && (options->text_color%0xFFFFFFFF<0xFF000000)) options->text_color+=0x05000000;
				else up=false;
	}
	else if(options->text_color!=0xFFFFFFFF)
	{
		delete  options->text_str; // Remember to clean up your string pointers
				options->text_str=SafeWSTR(L"Options");
				options->text_color=0xFFFFFFFF;
	}

	if(play->MouseOver()) play->text_color=0xAAFF0000;
	else play->text_color=0xFFFFFFFF;
	
	if(play->Click()) 
	{
			
			stage = 1;
			//Hidding all the objects, but keeping their information
			play->Hide();
			options->Hide();
			exit->Hide();
			return true;
	}

	if(exit->MouseOver()) exit->text_color=0xAAFF0000;
	else exit->text_color=0xFFFFFFFF;

	return true;
}


//test ptrs
FontObject* player = 0;
std::vector <FontObject*> os;

FontObject* pts = 0;
int score=0;
int xspeed=0;
int yspeed=0;
bool TestStage::Run()
{
	if(pMainInput->IsKeyDown(VK_ESCAPE)) 
	{
			stage = 0;
			player->Hide();
			for(int i=0; i<os.size(); i++) os[i]->Hide();
			return true;
	}
	//test code
	if(!player) player = new FontObject(*pScreenX/2-5, *pScreenY/2-5, *pScreenX/2+5, *pScreenY/2+9, SafeWSTR(L"X"));
	if(os.size()<3) 
	{
			int x=rand()%(*pScreenX-10)+5;
			int y=rand()%(*pScreenY-10)+5;
			os.push_back(new FontObject(x-5, y-5, x+5, y+9, SafeWSTR(L"O")));
	}

	if(!pts) pts = new FontObject(0,0,40,9, SafeWSTR(L"Score: "), 0xFFFFFFFF, DT_LEFT);
	
	delete pts->text_str;
	pts->text_str = JoinWSTR(true, SafeWSTR(L"Score: "), IntToWSTR(score));

	if(pMainInput->IsKeyDown(VK_UP)) yspeed-=1;
	if(pMainInput->IsKeyDown(VK_DOWN)) yspeed+=1;
	if(pMainInput->IsKeyDown(VK_LEFT)) xspeed-=1;
	if(pMainInput->IsKeyDown(VK_RIGHT)) xspeed+=1;

	player->MoveX(xspeed);
	player->MoveY(yspeed);
	
	if(player->pRect->left<=0) xspeed*=-1;
	if(player->pRect->top<=0) yspeed*=-1;

	if(player->pRect->right>=*pScreenX) xspeed*=-1;
	if(player->pRect->bottom>=*pScreenY) xspeed*=-1;

	if(player->pRect->left<0) player->MoveX(player->pRect->left*(-1));
	if(player->pRect->right>*pScreenX) player->MoveX(*pScreenX-player->pRect->right);
	if(player->pRect->top<0) player->MoveY(player->pRect->top*(-1));
	if(player->pRect->bottom>*pScreenY+1) player->MoveY(*pScreenY-player->pRect->bottom);

	//Test "hitbox"
	if(player->MouseOver()) player->text_color=0xFFFF0000;
	else player->text_color=0xFFFFFFFF;
	
	for(int i=0; i<os.size(); i++)
	{
		if(player->pRect->left<os[i]->pRect->right
			&& player->pRect->left>os[i]->pRect->left
			&& player->pRect->top<os[i]->pRect->bottom
			&& player->pRect->top>os[i]->pRect->top) 
		{
			GameObjectRelease(os[i]);
			os.erase(os.begin()+i);
			i--;
			score++;
		}
		else if(player->pRect->right>os[i]->pRect->left
			&& player->pRect->right<os[i]->pRect->right
			&& player->pRect->top<os[i]->pRect->bottom
			&& player->pRect->top>os[i]->pRect->top) 
		{
			GameObjectRelease(os[i]);
			os.erase(os.begin()+i);
			score++;
			i--;
		}
		else if(player->pRect->left<os[i]->pRect->right
			&& player->pRect->left>os[i]->pRect->left
			&& player->pRect->bottom>os[i]->pRect->top
			&& player->pRect->bottom<os[i]->pRect->bottom) 
		{
			GameObjectRelease(os[i]);
			os.erase(os.begin()+i);
			score++;
			i--;
		}
		else if(player->pRect->right>os[i]->pRect->left
			&& player->pRect->right<os[i]->pRect->right
			&& player->pRect->bottom>os[i]->pRect->top
			&& player->pRect->bottom<os[i]->pRect->bottom) 
		{
			GameObjectRelease(os[i]);
			os.erase(os.begin()+i);
			score++;
			i--;
		}
	}

	for(int i=0; i<os.size(); i++) os[i]->Display();
	player->Display();
	//end test code
	return true;
}