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
	
public:

	TestStage(GraphicsClass*, InputClass*, int*, int*);
	TestStage(const TestStage&);
	~TestStage();

	int* pScreenX;
	int* pScreenY;

	int stage;

	void OnResize();
	bool Run();
	bool Menu();
};
//End Test Stage Class


#endif