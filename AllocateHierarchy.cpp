//Allocate Hierarchy (Implements ID3DXAllocateHierarchy)
#include "AllocateHierarchy.h"

HRESULT AllocateHierarchy::CreateFrame(LPCSTR Name, D3DXFRAME** ppNewFrame)
{
	//Creating a Frame and Zeroing the memory
	D3DXFRAME* Frame = new D3DXFRAME; //Could later create an Extended version
	ZeroMemory(Frame, sizeof(D3DXFRAME));

	//Zeroing the New Frame (output value)
	*ppNewFrame = 0;

	//Initializing Frame Name
	if(Name)
	{
		int NameSize = strlen(Name)+1; //Gets Name lenght
		Frame->Name = new char[NameSize];
		memcpy(Frame->Name, Name, NameSize*sizeof(char)); //Copies Name to Frame->Name
	}
	else
	{
		Frame->Name = 0;
	}

	//NULL-ing pointers
	Frame->pFrameFirstChild = 0;
	Frame->pFrameSibling = 0;
	Frame->pMeshContainer = 0;
	D3DXMatrixIdentity(&Frame->TransformationMatrix);

	//Copy the created frame to the new frame.
	*ppNewFrame = Frame;
	Frame=0;

	return D3D_OK;
};

HRESULT AllocateHierarchy::CreateMeshContainer(LPCSTR Name,CONST D3DXMESHDATA* pMeshData,CONST D3DXMATERIAL* pMaterials, 
									CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials,CONST DWORD* pAdjacency, 
									ID3DXSkinInfo* pSkinInfo, D3DXMESHCONTAINER** ppNewMeshContainer)
{
	//Create a Mesh Container and Zero it's memory
	D3DXMESHCONTAINER* pMeshContainer = new D3DXMESHCONTAINER; //Could later create Extended Version
	ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER));

	//Zero the New Mesh Container (output value)
	*ppNewMeshContainer=0;

	//Initializing Mesh Name
	if(Name)
	{
		int NameSize = strlen(Name)+1; //Gets Name lenght
		pMeshContainer->Name = new char[NameSize];
		memcpy(pMeshContainer->Name, pMeshContainer, NameSize*sizeof(char)); //Copies Name to Frame->Name
	}
	else
	{
		pMeshContainer->Name = 0;
	}

	pMeshContainer->MeshData.Type=D3DXMESHTYPE_MESH;
	
	// Get the number of Faces for adjacency
	DWORD dwFaces = pMeshData->pMesh->GetNumFaces();

	//Get Initcilize all the other data
	pMeshContainer->NumMaterials = NumMaterials;

	//Create the arrays for the materials and the textures (Unsure if it works, might need fix)
	pMeshContainer->pMaterials = new D3DXMATERIAL;
	D3DMATERIAL9* pTempMat = new D3DMATERIAL9[pMeshContainer->NumMaterials];
	pMeshContainer->pMaterials->MatD3D = *pTempMat;

	// Multiply by 3 because there are three adjacent triangles
	pMeshContainer->pAdjacency = new DWORD[dwFaces*3];
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwFaces*3);

	//Get the device to use
	LPDIRECT3DDEVICE9 pD3DXDevice = 0;// Direct3D Rendering device
	pMeshData->pMesh->GetDevice(&pD3DXDevice);

	pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED, 
		pMeshData->pMesh->GetFVF(), pD3DXDevice, 
		&pMeshContainer->MeshData.pMesh);
	
	//Not sure if we need Texture thingy here. Would need a new MeshData struct.
	//Fingers crossed.

	if(pSkinInfo)
	{
		// Set Skin Info
	    pMeshContainer->pSkinInfo = pSkinInfo;
	    pSkinInfo->AddRef();
	}
	else	
	{
		pMeshContainer->pSkinInfo = 0;
	}

	// Set the output mesh container to the temp one
	*ppNewMeshContainer = pMeshContainer;
    pMeshContainer = 0;

	return D3D_OK;
}

HRESULT AllocateHierarchy::DestroyFrame(D3DXFRAME* pFrameToFree) 
{
	if(pFrameToFree->Name) delete[] pFrameToFree->Name;
    if(pFrameToFree) delete pFrameToFree;

    return D3D_OK; 
}

HRESULT AllocateHierarchy::DestroyMeshContainer(D3DXMESHCONTAINER* pMeshContainerToFree)
{	
	// if there is a name
	if(pMeshContainerToFree->Name) delete[] pMeshContainerToFree->Name;

	// if there is Adjacency
	if(pMeshContainerToFree->pAdjacency) delete[] pMeshContainerToFree->pAdjacency;
	
	// if there is Mesh Data
	if(pMeshContainerToFree->MeshData.pMesh) delete pMeshContainerToFree->MeshData.pMesh;
	
	// if there is skin information
	if(pMeshContainerToFree->pSkinInfo) delete pMeshContainerToFree->pSkinInfo;
	
	//Delete the whole thing
	if(pMeshContainerToFree) delete pMeshContainerToFree;
	
    return D3D_OK;
}