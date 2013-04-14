//Test Stage for Sys Frame header
#ifndef _TEST_STAGE_H_
#define _TEST_STAGE_H_

//Includes
#include <vector>

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

	std::vector<struct bullet*> bullets;
	std::vector<struct enemy*> enemies;

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

//Enemy struct
struct enemy
{
	FontObject* pEnemyFont;

	double yratio;
	double xratio;

	double xbuffer;
	double ybuffer;

	int health;
	int speed;
};
//End Enemy struct

//Test Bullet struct
struct bullet
{
	FontObject* pBulletFont;

	double yratio;
	double xratio;

	double xbuffer;
	double ybuffer;

	int wspeed;
};
//End Test struct


#endif