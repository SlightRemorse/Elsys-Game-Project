//Structs for the XModels
#ifndef _MODEL_STRUCTS_H_
#define _MODEL_STRUCTS_H_

//Includes
#include <d3dx9.h>
#include <d3d9.h>

typedef struct D3DXMESHCONTAINER_EX: public D3DXMESHCONTAINER
{
	IDirect3DTexture9** ppTexture;
	D3DMATERIAL9* pMaterials;

	ID3DXMesh* pSkinMesh;
	D3DXMATRIX* pBoneOffsets;
	D3DXMATRIX** ppFrameMatrices;

	D3DXATTRIBUTERANGE* pAttributeTable;
    DWORD NumAttributeGroups;
};

typedef struct D3DXFRAME_EX: public D3DXFRAME
{
	D3DXMATRIX matCombined;
};

#endif