// .x Model header
#ifndef _XMODEL_H_
#define _XMODEL_H_

//Includes
#include <d3dx9.h>

#pragma comment (lib, "d3dx9.lib")

//.x Model Class
class XModel 
{

public:
	XModel(IDirect3DDevice9*);
	XModel(const XModel&);
	~XModel();

	bool LoadModel(LPCWSTR);
private:
	IDirect3DDevice9* device;
	D3DXFRAME* pFrameRoot;
	ID3DXAnimationController* pAnimController;
};

//End .x Model Class

//Global

#endif