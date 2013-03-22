//.x Model
#include "graphicsclass.h"
#include "xmodel.h"
#include "AllocateHierarchy.h"

//Constructor (Get the D3DX device we'll be working with)
XModel::XModel(IDirect3DDevice9* device) 
{
	pDevice=device;
}

//Copy Constructor
XModel::XModel(const XModel&)
{
}

//Deconstructor
XModel::~XModel()
{
}

bool XModel::LoadModel(LPCWSTR filename) 
{
	HRESULT hresult;

	AllocateHierarchy HAlloc;

	hresult=D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED,
										pDevice, &HAlloc, 0,
										&pFrameRoot, &pAnimController);
	if(FAILED(hresult)) // couldn't load.
	{
		return false;
	}

	if(pAnimController) //Getting all the animation sets.
	{
		pAnimController->GetMaxNumAnimationSets();
	}



	return true;
}