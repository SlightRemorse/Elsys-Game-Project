//Test Stage for Sys Frame header
#ifndef _TEST_STAGE_H_
#define _TEST_STAGE_H_

//Test Stage Class
#include "objectwrapper.h"
#include "graphicsclass.h"
#include "typeconv.h"
#include "inputclass.h"

class TestStage
{
	GraphicsClass* pMainGraphics;
	InputClass* pMainInput;

	GraphicWrapper* test;
	GraphicWrapper* keys;
	
public:
	TestStage(GraphicsClass*, InputClass*);
	TestStage(const TestStage&);
	~TestStage();

	bool Run();
};
//End Test Stage Class


#endif