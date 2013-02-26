//Graphics Class header
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//Includes
#include <windows.h>

//Graphics Class
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:

};
//End Graphics Class

//Global
static bool FULLSCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#endif