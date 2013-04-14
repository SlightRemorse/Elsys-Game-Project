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

	refire=0; // my weapon is ready
}
//Copy Constructor
TestStage::TestStage(const TestStage&)
{
}
//Deconstructor
TestStage::~TestStage()
{
}

void TestStage::OnResize()
{
	GameObjectRelease(play);
	if(!play) play = new FontObject(*pScreenX/2-18, *pScreenY/2-40, *pScreenX/2+18, *pScreenY/2-20, SafeWSTR(L"Play"));
	GameObjectRelease(options);
	if(!options) options = new FontObject(*pScreenX/2-25, *pScreenY/2-20, *pScreenX/2+25, *pScreenY/2, SafeWSTR(L"Options"));
	GameObjectRelease(exit);
	if(!exit) exit = new FontObject(*pScreenX/2-18, *pScreenY/2, *pScreenX/2+18, *pScreenY/2+20, SafeWSTR(L"Exit"));

	if(stage!=0)
	{
		play->Hide();
		options->Hide();
		exit->Hide();
	}
};

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

int xspeed;
int yspeed;

FontObject* pts = 0;
int score=0;

bool TestStage::Run()
{
	if(pMainInput->IsKeyDown(VK_ESCAPE)) 
	{
			stage = 0;
			player->Hide();
			for(int i=0; i<os.size(); i++) os[i]->Hide();
			for(int i=0; i<bullets.size(); i++) bullets[i]->pBulletFont->Hide();
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

	if(pMainInput->IsKeyDown(VK_UP)) yspeed-=3;
	if(pMainInput->IsKeyDown(VK_DOWN)) yspeed+=3;
	if(pMainInput->IsKeyDown(VK_LEFT)) xspeed-=3;
	if(pMainInput->IsKeyDown(VK_RIGHT)) xspeed+=3;

	
	player->MoveX(xspeed);
	player->MoveY(yspeed);
	
	
	xspeed=0;
	yspeed=0;
	

	if(player->pRect->left<0) player->MoveX(*pScreenX-player->pRect->right);
	if(player->pRect->right>*pScreenX) player->MoveX(-(player->pRect->left));
	if(player->pRect->top<0) player->MoveY(*pScreenY-player->pRect->bottom);
	if(player->pRect->bottom>*pScreenY+1) player->MoveY(-(player->pRect->top));

	//test move bullet
	
	if(pMainInput->IsMKeyDownHold(1)) 
	{
		if(refire<=0) 
		{
				bulletSetup(5);
				refire=125;
		}
	}
	refire-=elapsed;


	bulletFrame(); // Run the bullet Frame


	//End bullet

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
	for(int i=0; i<bullets.size(); i++) bullets[i]->pBulletFont->Display();
	player->Display();
	//end test code
	
	return true;
}

void TestStage::SetElapsedTime(int time)
{
	elapsed=time;
}

//Bullet Stuff
void TestStage::bulletSetup(int speed)
{
	bullet* pNewBullet = new bullet();
	pNewBullet->wspeed=speed;

	int xline=pMainInput->MGetX()-player->pRect->left;
	int yline=pMainInput->MGetY()-player->pRect->bottom;
	double sline=sqrt((double)((xline*xline)+(yline*yline)));
			
	pNewBullet->xratio=pNewBullet->wspeed*(xline/sline);
	pNewBullet->yratio=pNewBullet->wspeed*(yline/sline);

	pNewBullet->xbuffer=0;
	pNewBullet->ybuffer=0;

	int centplayerx = (player->pRect->left+player->pRect->right)/2;
	int centplayery = (player->pRect->top+player->pRect->bottom)/2;

	pNewBullet->pBulletFont = new FontObject(centplayerx-1, centplayery-8, centplayerx+1, centplayery+5, SafeWSTR(L"."));

	bullets.push_back(pNewBullet);
};

bool TestStage::bulletRelease(bullet* pbullet)
{
			GameObjectRelease(pbullet->pBulletFont);
			delete pbullet;
			return true;
};


void TestStage::bulletFrame()
{
	for(int i=0; i<bullets.size(); i++)
	{
		//  Move the bullets

		int xmove = 0;
		int ymove = 0;

		bullets[i]->xbuffer+=bullets[i]->xratio;
		bullets[i]->ybuffer+=bullets[i]->yratio;

		if(bullets[i]->xbuffer>0)
		{
			while(bullets[i]->xbuffer>=1)
			{
				bullets[i]->xbuffer-=1;
				xmove+=1;
			}
			bullets[i]->pBulletFont->MoveX(xmove);
			xmove=0;
		}
		else
		{
			while(bullets[i]->xbuffer<=-1)
			{
				bullets[i]->xbuffer+=1;
				xmove-=1;
			}
			bullets[i]->pBulletFont->MoveX(xmove);
			xmove=0;
		}

		if(bullets[i]->yratio>0)
		{
			while(bullets[i]->ybuffer>=1)
			{
				bullets[i]->ybuffer-=1;
				ymove+=1;
			}
			bullets[i]->pBulletFont->MoveY(ymove);
			ymove=0;
		}
		else
		{
			while(bullets[i]->ybuffer<=-1)
			{
				bullets[i]->ybuffer+=1;
				ymove-=1;
			}
			bullets[i]->pBulletFont->MoveY(ymove);
			ymove=0;
		}

		//Check if out of bounds and release

		if(bullets[i]->pBulletFont->pRect->top<0)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pBulletFont->pRect->bottom > *pScreenY)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pBulletFont->pRect->left < 0)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pBulletFont->pRect->right > *pScreenX)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}

	}
}