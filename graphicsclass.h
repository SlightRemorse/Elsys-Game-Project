//Graphics Class header
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//Includes
#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")

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
	bool ResetDevice(bool, int, int);

private:
	bool Render();
	bool ToggleFullscreen(bool, int, int);

	IDirect3D9* graph_DX9;
	IDirect3DDevice9* DX9_device;
	D3DPRESENT_PARAMETERS DX9pp;
};
//End Graphics Class

//Global
static bool FULLSCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#endif