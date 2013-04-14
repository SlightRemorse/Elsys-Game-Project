//Allocate Hierarchy (Implements ID3DXAllocateHierarchy)
#include "AllocateHierarchy.h"

HRESULT AllocateHierarchy::CreateFrame(LPCSTR Name, D3DXFRAME** ppNewFrame)
{
	//Creating a Frame and Zeroing the memory
	D3DXFRAME_EX* pFrame = new D3DXFRAME_EX; //Could later create an Extended version
	ZeroMemory(pFrame, sizeof(D3DXFRAME_EX));

	//Zeroing the New Frame (output value)
	*ppNewFrame = 0;

	//Initializing Frame Name
	if(Name)
	{
		int NameSize = strlen(Name)+1; //Gets Name lenght
		pFrame->Name = new char[NameSize];
		memcpy(pFrame->Name, Name, NameSize*sizeof(char)); //Copies Name to Frame->Name
	}
	else
	{
		pFrame->Name = 0;
	}

	//NULL-ing pointers
	pFrame->pFrameFirstChild = 0;
	pFrame->pFrameSibling = 0;
	pFrame->pMeshContainer = 0;
	D3DXMatrixIdentity(&pFrame->matCombined);
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);

	//Copy the created frame to the new frame.
	*ppNewFrame = pFrame;
	pFrame=0;

	return D3D_OK;
};

HRESULT AllocateHierarchy::CreateMeshContainer(LPCSTR Name,CONST D3DXMESHDATA* pMeshData,CONST D3DXMATERIAL* pMaterials, 
									CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials,CONST DWORD* pAdjacency, 
									ID3DXSkinInfo* pSkinInfo, D3DXMESHCONTAINER** ppNewMeshContainer)
{
	//Create a Mesh Container and Zero it's memory
	D3DXMESHCONTAINER_EX* pMeshContainer = new D3DXMESHCONTAINER_EX; //Could later create Extended Version
	ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER_EX));

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
	pMeshContainer->pMaterials = new D3DMATERIAL9[pMeshContainer->NumMaterials];

	// Multiply by 3 because there are three adjacent triangles
	pMeshContainer->pAdjacency = new DWORD[dwFaces*3];
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwFaces*3);

	//Get the device to use
	IDirect3DDevice9* pD3DXDevice = 0;// Direct3D Rendering device
	pMeshData->pMesh->GetDevice(&pD3DXDevice);

	pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED, 
		pMeshData->pMesh->GetFVF(), pD3DXDevice, 
		&pMeshContainer->MeshData.pMesh);
	
	pMeshContainer->ppTexture  = new IDirect3DTexture9*[NumMaterials];
	for(DWORD dw = 0; dw < NumMaterials; ++dw)
	{
		pMeshContainer->ppTexture[dw] = 0;

		if(pMaterials[dw].pTextureFilename && strlen(pMaterials[dw].pTextureFilename) > 0)
		{
			if(FAILED(D3DXCreateTextureFromFile(pD3DXDevice, 
				CharSTRToLPWSTR(pMaterials[dw].pTextureFilename), &pMeshContainer->ppTexture[dw])))
					pMeshContainer->ppTexture[dw] = 0;
		}
	}

	//Release the device
	if(pD3DXDevice) delete pD3DXDevice;
	pD3DXDevice=0;

	if(pSkinInfo)
	{
		// Set Skin Info
	    pMeshContainer->pSkinInfo = pSkinInfo;
	    pSkinInfo->AddRef();

		// Setup bone matrices
	    UINT Bones = pSkinInfo->GetNumBones();
	    pMeshContainer->pBoneOffsets = new D3DXMATRIX[Bones];

		//Create the arrays for the bones and the frame matrices
		pMeshContainer->ppFrameMatrices = new D3DXMATRIX*[Bones];

	    // Setup the bone offset matrices
	    for (UINT i = 0; i < Bones; i++)
			pMeshContainer->pBoneOffsets[i] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i));
	}
	else	
	{
		pMeshContainer->pSkinInfo = 0;
		pMeshContainer->pBoneOffsets = 0;
		pMeshContainer->pSkinMesh = 0;
		pMeshContainer->ppFrameMatrices = 0;
	}

	// Set the output mesh container to the temp one
	*ppNewMeshContainer = pMeshContainer;
    pMeshContainer = 0;

	return D3D_OK;
}

HRESULT AllocateHierarchy::DestroyFrame(D3DXFRAME* pFrameToFree) 
{
	//Convert to our DeDXFRAME Extended
	D3DXFRAME_EX* pFrame = (D3DXFRAME_EX*)pFrameToFree;

	if(pFrame->Name) delete[] pFrame->Name;
    if(pFrame) delete pFrame;

    return D3D_OK; 
}

HRESULT AllocateHierarchy::DestroyMeshContainer(D3DXMESHCONTAINER* pMeshContainerToFree)
{	
	//Convert to our extended container
	D3DXMESHCONTAINER_EX* pMeshContainer = (D3DXMESHCONTAINER_EX*)pMeshContainerToFree;

	// if there is a name
	if(pMeshContainer->Name) delete[] pMeshContainer->Name;

	// if there are materials
	if(pMeshContainer->pMaterials) delete[] pMeshContainer->pMaterials;

	//Release the textures
	if(pMeshContainer->ppTexture)
		for(UINT i = 0; i < pMeshContainer->NumMaterials; ++i)
				if(pMeshContainer->ppTexture[i]) delete pMeshContainer->ppTexture[i];

	//delete the texture pointers
	if(pMeshContainer->ppTexture) delete[] pMeshContainer->ppTexture;

	// if there is Adjacency
	if(pMeshContainer->pAdjacency) delete[] pMeshContainer->pAdjacency;
	
	// if there are bone offset matrices
	if(pMeshContainer->pBoneOffsets) delete[] pMeshContainer->pBoneOffsets;
	
	//if there are frame matrices
	if(pMeshContainer->ppFrameMatrices) delete[] pMeshContainer->ppFrameMatrices;
	
	if(pMeshContainer->pAttributeTable) delete[] pMeshContainer->pAttributeTable;
	
	//if there is a copy of the mesh here
	if(pMeshContainer->pSkinMesh) delete pMeshContainer->pSkinMesh;

	// if there is Mesh Data
	if(pMeshContainer->MeshData.pMesh) delete pMeshContainer->MeshData.pMesh;
	
	// if there is skin information
	if(pMeshContainer->pSkinInfo) delete pMeshContainer->pSkinInfo;
	
	//Delete the whole thing
	if(pMeshContainer) delete pMeshContainer;
	
    return D3D_OK;
}