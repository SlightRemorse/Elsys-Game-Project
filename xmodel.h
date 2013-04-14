// .x Model header
#ifndef _XMODEL_H_
#define _XMODEL_H_

//Includes
#include <d3dx9.h>

#pragma comment (lib, "d3dx9.lib")

//.x Model Class
#include "graphicsclass.h"
#include "AllocateHierarchy.h"

class XModel 
{

public:
	XModel(IDirect3DDevice9*);
	XModel(const XModel&);
	~XModel();

	//Model
	D3DXVECTOR3 vecCenter; // Center of bounding sphere of object
    float fRadius; // Radius of bounding sphere of object

	//Animation
	DWORD dwCurrentAnimation; // The current animation

	//Functions
	bool LoadModel(LPCWSTR);
	void SetCurrentAnimation(DWORD);
	void Draw();
	void Update(double);

private:
	IDirect3DDevice9* pD3DXDevice; //The D3DX device to use
	
	//Model
	D3DXMESHCONTAINER_EX* pFirstMesh; // The first mesh in the hierarchy
	D3DXFRAME* pFrameRoot; // Frame hierarchy of the model
	D3DXMATRIX* pBoneMatrices; // Used when calculating the bone position
	UINT uMaxBones; // The Max number of bones for the model
	
	//Animation
	DWORD dwAnimationSetCount; // Number of animation sets
	ID3DXAnimationController*   pAnimController; // Controller for the animations

	//Functions
	void SetupBoneMatrices(D3DXFRAME_EX*, D3DXMATRIX*);
	void DrawFrame(D3DXFRAME_EX*);
	void UpdateFrameMatrices(D3DXFRAME_EX*, D3DXMATRIX*);
};

//End .x Model Class

//Globals

#endif