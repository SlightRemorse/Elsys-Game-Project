//Test Stage for Sys Frame header
#ifndef _TEST_STAGE_H_
#define _TEST_STAGE_H_

//Includes
#include <vector>
#include <time.h>

#include "objectwrapper.h"
#include "graphicsclass.h"
#include "typeconv.h"
#include "inputclass.h"

//Structs

//Base Font Object struct
struct basefont
{
	FontObject* pFontObject;

	double yratio;
	double xratio;

	double xbuffer;
	double ybuffer;
};

// bonus struct
struct bonus
{
	int xcoord;
	int ycoord;
	int type;
	FontObject* pFontObject;
};
//bonus end


//"Gore" struct
struct gore: basefont
{
	int lifetime;
};

//Enemy struct
struct enemy: basefont
{
	int health;
	double speed;
};
//End Enemy struct

//Test Bullet struct
struct bullet: basefont
{
	int wspeed;
};
//End Test struct

//Test Stage Class
class TestStage
{
	GraphicsClass* pMainGraphics;
	InputClass* pMainInput;

	FontObject* exit;
	FontObject* play;
	FontObject* options;
	FontObject* above_message;

	FontObject* pts;
	FontObject* player;

	int gamestate;
	int elapsed;
	
	int speed;
	int xspeed;
	int yspeed;

public:

	TestStage(GraphicsClass*, InputClass*, int*, int*);
	TestStage(const TestStage&);
	~TestStage();

	int* pScreenX;
	int* pScreenY;

	int stage;

	void SetElapsedTime(int);
	void OnResize();
	bool Run();
	bool Menu();

private:

	std::vector<struct bullet*> bullets;
	std::vector<struct enemy*> enemies;
	std::vector<struct gore*> explosion;
	bonus* powerup;

	void explosionSetup(int, int, int);
	bool explosionRelease(struct gore*);
	void explosionFrame();

	void enemySetup(int);
	bool enemyRelease(struct enemy*);
	void enemyFrame();

	void bulletSetup(int);
	bool bulletRelease(struct bullet*);
	void bulletFrame();

	void bonusSetup();
	bool bonusRelease(struct bonus*);
	void bonusFrame();

	int score;
	int playerhealth; // Implement later
	int refire;
	int spawnspeed;
};
//End Test Stage Class

#endif