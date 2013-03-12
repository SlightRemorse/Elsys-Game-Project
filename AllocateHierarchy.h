//Allocate Hierarchy header (Implements ID3DXAllocateHierarchy)
#ifndef _ALLOCATE_HIERARCHY_H_
#define _ALLOCATE_HIERARCHY_H_

//Includes
#include <d3dx9.h>

#pragma comment (lib, "d3dx9.lib")

//Allocate Hierarchy Class
class AllocateHierarchy: public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, D3DXFRAME**);

	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR,CONST D3DXMESHDATA*,CONST D3DXMATERIAL*,CONST D3DXEFFECTINSTANCE*, 
									DWORD,CONST DWORD*, ID3DXSkinInfo*, D3DXMESHCONTAINER**);

	STDMETHOD(DestroyFrame)(THIS_ D3DXFRAME*);
    
	STDMETHOD(DestroyMeshContainer)(THIS_ D3DXMESHCONTAINER*);
};
//End Allocate Hierarchy Class

#endif