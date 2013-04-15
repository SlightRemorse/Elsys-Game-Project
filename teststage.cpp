//Test Stage for Sys Frame Class
#include "teststage.h"

//Constructor
TestStage::TestStage(GraphicsClass* pGraphics, InputClass* pInput, int* screenwidth, int* screenheight)
{
	srand(time(0));

	pMainGraphics=pGraphics; // getting the current Graphics Class we're using
	pMainInput=pInput; // getting the current Input Class we're using

	//Setting the pointers to the window size integers
	pScreenX=screenwidth;
	pScreenY=screenheight;

	//Nulling the Object pointers
	options = 0;
	exit = 0;
	play = 0;
	above_message = 0;
	player=0;
	pts=0;


	score=0;

	gamestate=0; // Not started the game

	stage = 0; // 0 Menu, 1 Run

	refire=0; // my weapon is ready
	spawnspeed=750; // speed of spawning
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
	if(!play) 
	{
	if(gamestate==1) play = new FontObject(*pScreenX/2-30, *pScreenY/2-40, *pScreenX/2+30, *pScreenY/2-20, SafeWSTR(L"Resume"));
	else if(gamestate==2) play = new FontObject(*pScreenX/2-40, *pScreenY/2-40, *pScreenX/2+40, *pScreenY/2-20, SafeWSTR(L"New Game"));
	else play = new FontObject(*pScreenX/2-18, *pScreenY/2-40, *pScreenX/2+18, *pScreenY/2-20, SafeWSTR(L"Play"));
	}
	GameObjectRelease(options);
	if(!options) options = new FontObject(*pScreenX/2-25, *pScreenY/2-20, *pScreenX/2+25, *pScreenY/2, SafeWSTR(L"Options"));
	GameObjectRelease(exit);
	if(!exit) exit = new FontObject(*pScreenX/2-18, *pScreenY/2, *pScreenX/2+18, *pScreenY/2+20, SafeWSTR(L"Exit"));
	if(above_message) GameObjectRelease(above_message);
	if(gamestate==1) 
	{
		above_message = new FontObject(*pScreenX/2-30, *pScreenY/2-70, *pScreenX/2+30, *pScreenY/2-50, SafeWSTR(L"Paused"));
		above_message->Hide();
	}
	if(gamestate==2)
	{
		above_message = new FontObject(*pScreenX/2-40, *pScreenY/2-70, *pScreenX/2+40, *pScreenY/2-50, SafeWSTR(L"Game Over!"));
	}
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
	if(above_message) above_message->Display();

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
			playerhealth=2;
			//Hidding all the objects, but keeping their information
			play->Hide();
			options->Hide();
			exit->Hide();
			
			xspeed=0;
			yspeed=0;

			if(pts) pts->Display();

			if(above_message) above_message->Hide();

			if(gamestate!=1)
			{
			gamestate=1;

			if(above_message) GameObjectRelease(above_message);
			above_message = new FontObject(*pScreenX/2-30, *pScreenY/2-70, *pScreenX/2+30, *pScreenY/2-50, SafeWSTR(L"Paused"));
			above_message->Hide();

			delete play->text_str;
			play->text_str=SafeWSTR(L"Resume");

			play->pRect->left=*pScreenX/2-30;
			play->pRect->right=*pScreenX/2+30;
			}

			return true;
	}

	if(exit->MouseOver()) exit->text_color=0xAAFF0000;
	else exit->text_color=0xFFFFFFFF;

	return true;
}


bool TestStage::Run()
{
	if(pMainInput->IsKeyDown(VK_ESCAPE)) 
	{
			stage = 0;
			player->Hide();
			for(int i=0; i<enemies.size(); i++) enemies[i]->pFontObject->Hide();
			for(int i=0; i<bullets.size(); i++) bullets[i]->pFontObject->Hide();
			for(int i=0; i<explosion.size(); i++) explosion[i]->pFontObject->Hide();
			if(pts) pts->Hide();
			return true;
	}
	//test code
	
	if(!player) player = new FontObject(*pScreenX/2-5, *pScreenY/2-5, *pScreenX/2+5, *pScreenY/2+9, SafeWSTR(L"O"), 0xFF00FF00);

	if(!pts) pts = new FontObject(0,0,40,9, SafeWSTR(L"Score: "), 0xFFFFFFFF, DT_LEFT);
	
	delete pts->text_str;
	pts->text_str = JoinWSTR(true, SafeWSTR(L"Score: "), IntToWSTR(score));

	if(pMainInput->IsKeyDown(VK_UP)) yspeed-=1;
	if(pMainInput->IsKeyDown(VK_DOWN)) yspeed+=1;
	if(pMainInput->IsKeyDown(VK_LEFT)) xspeed-=1;
	if(pMainInput->IsKeyDown(VK_RIGHT)) xspeed+=1;

	
	player->MoveX(xspeed);
	player->MoveY(yspeed);
	
	
	xspeed=0;
	yspeed=0;
	

	if(player->pRect->left<0) player->MoveX(1);
	if(player->pRect->right>*pScreenX) player->MoveX(-1);
	if(player->pRect->top<0) player->MoveY(1);
	if(player->pRect->bottom>*pScreenY+1) player->MoveY(-1);

	//test move bullet
	
	if(pMainInput->IsMKeyDownHold(1)) 
	{
		if(refire<=0) 
		{
				bulletSetup(8);
				refire=125;
		}
	}
	refire-=elapsed;

	if(spawnspeed<=0)
	{
		enemySetup(3);
		spawnspeed+=750;
	}
	spawnspeed-=elapsed;

	bulletFrame(); // Run the bullet Frame
	enemyFrame(); // Run the enemy frame
	explosionFrame(); // Run the gore/explosion frame

	if(playerhealth==0)
	{
		stage = 0;
		gamestate=2;
		if(above_message) GameObjectRelease(above_message);
		above_message = new FontObject(*pScreenX/2-40, *pScreenY/2-70, *pScreenX/2+40, *pScreenY/2-50, SafeWSTR(L"Game Over!"));
				
		above_message->Display();

		delete play->text_str;
		play->text_str=SafeWSTR(L"New Game");

		play->pRect->left=*pScreenX/2-40;
		play->pRect->right=*pScreenX/2+40;

		GameObjectRelease(player);
		for(int i=0 ; i<bullets.size(); i++)
		{
			GameObjectRelease(bullets[i]->pFontObject);
		}
		bullets.clear();
		for (int i=0; i<enemies.size() ; i++)
		{
			GameObjectRelease(enemies[i]->pFontObject);
		}
		enemies.clear();
		score=0;

		return true;
	}

	//Bullet hit detection
	for(int k = 0 ; k<bullets.size(); k++)
	{
		for(int i = 0; i<enemies.size(); i++)
		{
			if(bullets[k]->pFontObject->pRect->left<enemies[i]->pFontObject->pRect->right
			&& bullets[k]->pFontObject->pRect->left>enemies[i]->pFontObject->pRect->left
			&& bullets[k]->pFontObject->pRect->top<enemies[i]->pFontObject->pRect->bottom
			&& bullets[k]->pFontObject->pRect->top>enemies[i]->pFontObject->pRect->top)
			{
				enemies[i]->health--;
				enemies[i]->pFontObject->text_color-=0xFFFF/2;
				if(enemies[i]->health==0)
				{
				explosionSetup(enemies[i]->pFontObject->pRect->left, enemies[i]->pFontObject->pRect->top, 2);
				GameObjectRelease(enemies[i]->pFontObject);
				enemies.erase(enemies.begin()+i);
				score++;
				i--;
				}
				GameObjectRelease(bullets[k]->pFontObject);
				bullets.erase(bullets.begin()+k);
				k--;
				break;
			}
			else if(bullets[k]->pFontObject->pRect->right>enemies[i]->pFontObject->pRect->left
			&& bullets[k]->pFontObject->pRect->right<enemies[i]->pFontObject->pRect->right
			&& bullets[k]->pFontObject->pRect->top<enemies[i]->pFontObject->pRect->bottom
			&& bullets[k]->pFontObject->pRect->top>enemies[i]->pFontObject->pRect->top) 
			{
				enemies[i]->health--;
				enemies[i]->pFontObject->text_color-=0xFFFF/2;
				if(enemies[i]->health==0)
				{
				explosionSetup(enemies[i]->pFontObject->pRect->left, enemies[i]->pFontObject->pRect->top, 2);
				GameObjectRelease(enemies[i]->pFontObject);
				enemies.erase(enemies.begin()+i);
				score++;
				i--;
				}
				GameObjectRelease(bullets[k]->pFontObject);
				bullets.erase(bullets.begin()+k);
				k--;
				break;
			}
			else if(bullets[k]->pFontObject->pRect->left<enemies[i]->pFontObject->pRect->right
				&& bullets[k]->pFontObject->pRect->left>enemies[i]->pFontObject->pRect->left
				&& bullets[k]->pFontObject->pRect->bottom>enemies[i]->pFontObject->pRect->top
				&& bullets[k]->pFontObject->pRect->bottom<enemies[i]->pFontObject->pRect->bottom) 
			{
				enemies[i]->health--;
				enemies[i]->pFontObject->text_color-=0xFFFF/2;
				if(enemies[i]->health==0)
				{
				explosionSetup(enemies[i]->pFontObject->pRect->left, enemies[i]->pFontObject->pRect->top, 2);
				GameObjectRelease(enemies[i]->pFontObject);
				enemies.erase(enemies.begin()+i);
				score++;
				i--;
				}
				GameObjectRelease(bullets[k]->pFontObject);
				bullets.erase(bullets.begin()+k);
				k--;
				break;
			}
			else if(bullets[k]->pFontObject->pRect->right>enemies[i]->pFontObject->pRect->left
				&& bullets[k]->pFontObject->pRect->right<enemies[i]->pFontObject->pRect->right
				&& bullets[k]->pFontObject->pRect->bottom>enemies[i]->pFontObject->pRect->top
				&& bullets[k]->pFontObject->pRect->bottom<enemies[i]->pFontObject->pRect->bottom) 
			{
				enemies[i]->health--;
				enemies[i]->pFontObject->text_color-=0xFFFF/2;
				if(enemies[i]->health==0)
				{
				explosionSetup(enemies[i]->pFontObject->pRect->left, enemies[i]->pFontObject->pRect->top, 2);
				GameObjectRelease(enemies[i]->pFontObject);
				enemies.erase(enemies.begin()+i);
				score++;
				i--;
				}
				GameObjectRelease(bullets[k]->pFontObject);
				bullets.erase(bullets.begin()+k);
				k--;
				break;
			}
		}
	}



	for(int i=0; i<enemies.size(); i++) enemies[i]->pFontObject->Display();
	for(int i=0; i<bullets.size(); i++) bullets[i]->pFontObject->Display();
	for(int i=0; i<explosion.size(); i++) explosion[i]->pFontObject->Display();
	player->Display();
	//end test code
	
	return true;
}

void TestStage::SetElapsedTime(int time)
{
	elapsed=time;
}



//Enemy Stuff

void TestStage::enemySetup(int health)
{
	enemy* pNewEnemy = new enemy();
	pNewEnemy->health=health;

	pNewEnemy->xbuffer=0;
	pNewEnemy->ybuffer=0;

	pNewEnemy->speed=1.2;

	int side = rand()%4;

	int x;
	int y;

	switch (side)
	{
	case 0:
		x=0;
		y=rand()%(*pScreenY-10)+5;
		break;
	case 1:
		x=*pScreenX;
		y=rand()%(*pScreenY-10)+5;
		break;
	case 2:
		x=rand()%(*pScreenX-10)+5;
		y=0;
		break;
	case 3:
		x=rand()%(*pScreenX-10)+5;
		y=*pScreenY;
		break;
	}

	pNewEnemy->pFontObject = new FontObject(x-5, y-5, x+5, y+9, SafeWSTR(L"O"));
	enemies.push_back(pNewEnemy);
}

bool TestStage::enemyRelease(enemy* pEnemy)
{
			GameObjectRelease(pEnemy->pFontObject);
			delete pEnemy;
			return true;
};

void TestStage::enemyFrame()
{
	int centplayerX = (player->pRect->left+player->pRect->right)/2;
	int centplayerY = (player->pRect->top+player->pRect->bottom)/2;

	for(int i=0; i<enemies.size(); i++)
	{
		int centenemyX = (enemies[i]->pFontObject->pRect->left+player->pRect->right)/2;
		int centenemyY = (enemies[i]->pFontObject->pRect->top+player->pRect->bottom)/2;

		int xline=centplayerX-centenemyX;
		int yline=centplayerY-centenemyY;

		if((abs(xline)<5) && (abs(yline)<5))
		{
			playerhealth--;
			player->text_color+=0xAA0000;
			player->text_color-=0x00AA00;

			enemyRelease(enemies[i]);
			enemies.erase(enemies.begin()+i);
			continue;
		}

		double sline=sqrt((double)((xline*xline)+(yline*yline)));
			
		enemies[i]->xratio=enemies[i]->speed*(xline/sline);
		enemies[i]->yratio=enemies[i]->speed*(yline/sline);

		//Enemy Movement
		int xmove=0;
		int ymove=0;

		enemies[i]->xbuffer+=enemies[i]->speed*enemies[i]->xratio;
		enemies[i]->ybuffer+=enemies[i]->speed*enemies[i]->yratio;

		if(enemies[i]->xbuffer>0)
		{
			while(enemies[i]->xbuffer>=1)
			{
				enemies[i]->xbuffer-=1;
				xmove+=1;
			}
			enemies[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}
		else
		{
			while(enemies[i]->xbuffer<=-1)
			{
				enemies[i]->xbuffer+=1;
				xmove-=1;
			}
			enemies[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}

		if(enemies[i]->yratio>0)
		{
			while(enemies[i]->ybuffer>=1)
			{
				enemies[i]->ybuffer-=1;
				ymove+=1;
			}
			enemies[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}
		else
		{
			while(enemies[i]->ybuffer<=-1)
			{
				enemies[i]->ybuffer+=1;
				ymove-=1;
			}
			enemies[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}
	}
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

	pNewBullet->pFontObject = new FontObject(centplayerx-1, centplayery-8, centplayerx+1, centplayery+5, SafeWSTR(L"."));

	bullets.push_back(pNewBullet);
};

bool TestStage::bulletRelease(bullet* pbullet)
{
			GameObjectRelease(pbullet->pFontObject);
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
			bullets[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}
		else
		{
			while(bullets[i]->xbuffer<=-1)
			{
				bullets[i]->xbuffer+=1;
				xmove-=1;
			}
			bullets[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}

		if(bullets[i]->yratio>0)
		{
			while(bullets[i]->ybuffer>=1)
			{
				bullets[i]->ybuffer-=1;
				ymove+=1;
			}
			bullets[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}
		else
		{
			while(bullets[i]->ybuffer<=-1)
			{
				bullets[i]->ybuffer+=1;
				ymove-=1;
			}
			bullets[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}

		//Check if out of bounds and release

		if(bullets[i]->pFontObject->pRect->top<0)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pFontObject->pRect->bottom > *pScreenY)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pFontObject->pRect->left < 0)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}
		else if(bullets[i]->pFontObject->pRect->right > *pScreenX)
		{	
			bulletRelease(bullets[i]);
			bullets.erase(bullets.begin()+i);
		}

	}
}

void TestStage::explosionSetup(int xcoord, int ycoord, int speed)
{
	double xperc=1.0;
	double yperc=0.0;
	int xdirection = -1;
	int ydirection = 1;

	for(int i=0; i<12; i++)
	{
		for(int k=1; k<=2; k++)
		{
		gore* pNewGore = new gore();
		pNewGore->lifetime=20;

		pNewGore->xbuffer=0;
		pNewGore->ybuffer=0;

		pNewGore->xratio=speed/k*(xperc/1);
		pNewGore->yratio=speed/k*(yperc/1);

		pNewGore->pFontObject = new FontObject(xcoord-1, ycoord-8, xcoord+1, ycoord+5, SafeWSTR(L"."), 0xFFFF0000);

		explosion.push_back(pNewGore);
		}

		if(i%6==3 && i!=0) ydirection*=(-1); // switch side
		if(i%6==0 && i!=0) xdirection*=(-1); // switch side
		xperc+=1.0/3.0*xdirection;
		yperc+=1.0/3.0*ydirection;
	}
}

bool TestStage::explosionRelease(gore* pGore)
{
	GameObjectRelease(pGore->pFontObject);
	delete pGore;
	return true;
}

void TestStage::explosionFrame()
{
	for(int i=0; i<explosion.size(); i++)
	{
		if(explosion[i]->lifetime==0)
		{
			explosionRelease(explosion[i]);
			explosion.erase(explosion.begin()+i);
			i--;
			continue;
		}
		explosion[i]->lifetime--;
		
		explosion[i]->xbuffer+=explosion[i]->xratio;
		explosion[i]->ybuffer+=explosion[i]->yratio;
		
		int xmove=0;
		int ymove=0;

		if(explosion[i]->xbuffer>0)
		{
			while(explosion[i]->xbuffer>=1)
			{
				explosion[i]->xbuffer-=1;
				xmove+=1;
			}
			explosion[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}
		else
		{
			while(explosion[i]->xbuffer<=-1)
			{
				explosion[i]->xbuffer+=1;
				xmove-=1;
			}
			explosion[i]->pFontObject->MoveX(xmove);
			xmove=0;
		}

		if(explosion[i]->yratio>0)
		{
			while(explosion[i]->ybuffer>=1)
			{
				explosion[i]->ybuffer-=1;
				ymove+=1;
			}
			explosion[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}
		else
		{
			while(explosion[i]->ybuffer<=-1)
			{
				explosion[i]->ybuffer+=1;
				ymove-=1;
			}
			explosion[i]->pFontObject->MoveY(ymove);
			ymove=0;
		}
	}
}