//Graphics Class header
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//Graphics Class
#include "graphicwrapper.h"
#include "directfont.h"

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

	D3DCOLOR BGCOLOR;
	DXFonts* pDX_Fonts;

	std::vector<GraphicWrapper*> vec_pGObj;
	GraphicWrapper* AddObject(GraphicWrapper*);
	bool RemoveObject(GraphicWrapper*);



public:
	bool Render();
	bool ToggleFullscreen(bool, int, int);

	IDirect3D9* pGraph_DX9;
	IDirect3DDevice9* pDX9_device;
	D3DPRESENT_PARAMETERS DX9pp;
	HWND hwnd;
};
//End Graphics Class

//Global
static bool FULLSCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#endif