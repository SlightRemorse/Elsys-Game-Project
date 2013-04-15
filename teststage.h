//Test Stage for Sys Frame header
#ifndef _TEST_STAGE_H_
#define _TEST_STAGE_H_

//Includes
#include <vector>
#include <time.h>

//Test Stage Class
#include "objectwrapper.h"
#include "graphicsclass.h"
#include "typeconv.h"
#include "inputclass.h"

class TestStage
{
	GraphicsClass* pMainGraphics;
	InputClass* pMainInput;

	FontObject* exit;
	FontObject* play;
	FontObject* options;
	FontObject* above_message;

	int gamestate;
	int elapsed;
	
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

	void explosionSetup(int, int, int);
	bool explosionRelease(struct gore*);
	void explosionFrame();

	void enemySetup(int);
	bool enemyRelease(struct enemy*);
	void enemyFrame();

	void bulletSetup(int);
	bool bulletRelease(struct bullet*);
	void bulletFrame();

	int playerhealth; // Implement later
	int refire;
	int spawnspeed;
};
//End Test Stage Class

//Base Font Object struct
struct basefont
{
	FontObject* pFontObject;

	double yratio;
	double xratio;

	double xbuffer;
	double ybuffer;
};

//"Gore" struct
struct gore: basefont
{
	int lifetime;
};

//Enemy struct
struct enemy: basefont
{
	int health;
	int speed;
};
//End Enemy struct

//Test Bullet struct
struct bullet: basefont
{
	int wspeed;
};
//End Test struct


#endif