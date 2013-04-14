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
FontObject* bullet;

FontObject* pts = 0;
int score=0;
int xspeed=0;
int yspeed=0;
double yratio=0;
double xratio=0;
int xbuffer = 0;
int xmove = 0;
int ybuffer = 0;
int ymove = 0;
int wspeed=5;

bool TestStage::Run()
{
	if(pMainInput->IsKeyDown(VK_ESCAPE)) 
	{
			stage = 0;
			player->Hide();
			for(int i=0; i<os.size(); i++) os[i]->Hide();
			if(bullet)bullet->Hide();
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
	if(pMainInput->IsMKeyClick(2)) 
	{
		GameObjectRelease(bullet);
		}

	if(pMainInput->IsMKeyClick(1))
	{
		if(pMainInput->MGetX()<player->pRect->left && pMainInput->MGetY()>player->pRect->bottom)
		{
			int a=player->pRect->left-pMainInput->MGetX();
			int b=pMainInput->MGetY()-player->pRect->bottom;
			double c=sqrt((double)((a*a)+(b*b)));
			
			xratio=wspeed*(a/c);
			yratio=wspeed*(b/c);
			if(!bullet)bullet=new FontObject(player->pRect->left, player->pRect->bottom,player->pRect->left-3, player->pRect->bottom+3, SafeWSTR(L"."));
		
		}
		else if(pMainInput->MGetX()>player->pRect->left && pMainInput->MGetY()>player->pRect->bottom)
		{
			int a=pMainInput->MGetX()-player->pRect->left;
			int b=pMainInput->MGetY()-player->pRect->bottom;
			double c=sqrt((double)((a*a)+(b*b)));

			xratio=wspeed*(a/c);
			yratio=wspeed*(b/c);
			if(!bullet)bullet=new FontObject(player->pRect->right, player->pRect->bottom, player->pRect->right+3, player->pRect->bottom+3, SafeWSTR(L"."));

		}
		else if(pMainInput->MGetX()<player->pRect->left && pMainInput->MGetY()<player->pRect->top)
		{
			int a=player->pRect->left-pMainInput->MGetX();
			int b=player->pRect->top-pMainInput->MGetY();
			double c=sqrt((double)((a*a)+(b*b)));

			xratio=wspeed*(a/c);
			yratio=wspeed*(b/c);
			if(!bullet) bullet = new FontObject(player->pRect->left, player->pRect->top, player->pRect->left-3, player->pRect->top-3, SafeWSTR(L"."));
			
		}
		else if(pMainInput->MGetX()>player->pRect->left && pMainInput->MGetY()<player->pRect->top)
		{
			int a=pMainInput->MGetX()-player->pRect->right;
			int b=player->pRect->top-pMainInput->MGetY();
			double c=sqrt((double)((a*a)+(b*b)));

			xratio=wspeed*(a/c);
			yratio=wspeed*(b/c);
			if(!bullet)bullet= new FontObject(player->pRect->right, player->pRect->top, player->pRect->right+3, player->pRect->top-3, SafeWSTR(L"."));
			
		}
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
	
	while(bullet)
	{
		xmove = 0;
		xbuffer+=xratio;
		ymove = 0;
		ybuffer += yratio;
		if(xbuffer>0)
		{
			while(xbuffer>=1)
			{
				xbuffer-=1;
				xmove+=1;
			}
			bullet->MoveX(xmove);
		}
		else
		{
			while(xbuffer<=-1)
			{
				xbuffer+=1;
				xmove-=1;
			}
			bullet->MoveX(xmove);
		}
		if(yratio>0)
		{
			while(ybuffer>=1)
			{
				ybuffer-=1;
				ymove+=1;
			}
			bullet->MoveY(ymove);
		}
		else
		{
			while(ybuffer<=-1)
			{
				ybuffer+=1;
				ymove-=1;
			}
			bullet->MoveY(ymove);
		}

	}
	//delete bullet
	if(bullet->pRect->top<0)
	{	
		GameObjectRelease(bullet);
	}
	else if(bullet->pRect->bottom > *pScreenX)
	{	
		GameObjectRelease(bullet);
	}
	else if(bullet->pRect->left < 0)
	{	
		GameObjectRelease(bullet);
	}
	else if(bullet->pRect->right > *pScreenY)
	{	
		GameObjectRelease(bullet);
	}

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
	if(bullet) bullet->Display();
	//end test code
	
	return true;
}