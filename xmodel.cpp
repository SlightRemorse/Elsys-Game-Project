//.x Model
#include "xmodel.h"

//Constructor (Get the D3DX device we'll be working with)
XModel::XModel(IDirect3DDevice9* device) 
{
	pD3DXDevice=device;
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

	hresult=D3DXLoadMeshHierarchyFromX(filename, //name of the .x file
										D3DXMESH_MANAGED, //Load the Options
										pD3DXDevice, //Use the correct device
										&HAlloc, //Allocation Heirarchy interface
										0, //No effects :(
										&pFrameRoot, //Frame heirarchy
										&pAnimController); // Animation controller
	
	if(FAILED(hresult)) // couldn't load.
	{
		return false;
	}

	if(pAnimController) //Getting all the animation sets.
	{
		pAnimController->GetMaxNumAnimationSets();
	}

	if(pFrameRoot)
	{
		//Set the bones up
		SetupBoneMatrices((D3DXFRAME_EX*)pFrameRoot, 0);

		//Setup the bone matrices array 
		pBoneMatrices  = new D3DXMATRIX[uMaxBones];
		ZeroMemory(pBoneMatrices, sizeof(D3DXMATRIX)*uMaxBones);

		//Calculate the Bounding Sphere
		D3DXFrameCalculateBoundingSphere(pFrameRoot, &vecCenter, &fRadius);
	}

	return true;
}

void XModel::SetupBoneMatrices(D3DXFRAME_EX* pFrame, D3DXMATRIX* pParentMatrix)
{
	D3DXMESHCONTAINER_EX* pMesh = (D3DXMESHCONTAINER_EX*)pFrame->pMeshContainer;

	//Set up the bones on the mesh (if it exists)
	if(pMesh)
	{
		if(pFirstMesh)
			pFirstMesh = pMesh;
		
		// if there is a skinmesh, then setup the bone matrices
		if(pMesh->pSkinInfo)
		{
			//Create a copy of the mesh
			pMesh->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED, 
				pMesh->MeshData.pMesh->GetFVF(), pD3DXDevice, 
				&pMesh->pSkinMesh);

			if(uMaxBones < pMesh->pSkinInfo->GetNumBones())
			{
				//Get the number of bones
				uMaxBones = pMesh->pSkinInfo->GetNumBones();
			}

			D3DXFRAME_EX* pTempFrame = 0;

			//For each bone 
			for (UINT i = 0; i < pMesh->pSkinInfo->GetNumBones(); i++)
			{   
				// Find the frame
				pTempFrame = (D3DXFRAME_EX*)D3DXFrameFind(pFrameRoot, 
						pMesh->pSkinInfo->GetBoneName(i));

				//set the bone part
				pMesh->ppFrameMatrices[i] = &pTempFrame->matCombined;
			}
		}
	}

	//Check your sibling
	if(pFrame->pFrameSibling)
		SetupBoneMatrices((D3DXFRAME_EX*)pFrame->pFrameSibling, pParentMatrix);

	//Check your first child
	if(pFrame->pFrameFirstChild)
		SetupBoneMatrices((D3DXFRAME_EX*)pFrame->pFrameFirstChild, &pFrame->matCombined);
}

void XModel::SetCurrentAnimation(DWORD dwAnimationFlag)
{
	//Check if we're not already on this animation or if the passed animation doesn't exist
	if((dwAnimationFlag != dwCurrentAnimation) && (dwAnimationFlag < dwAnimationSetCount)) 
	{ 
		dwCurrentAnimation = dwAnimationFlag;
		ID3DXAnimationSet* AnimSet = 0;
		
		pAnimController->GetAnimationSet(dwCurrentAnimation, &AnimSet);
		pAnimController->SetTrackAnimationSet(0, AnimSet);
		pAnimController->SetTrackPosition(0, 0); // reset the time to 0
		
		if(AnimSet) delete AnimSet; // release the animation set
	}
}

//Draw functions

void XModel::Draw()
{
	D3DXMESHCONTAINER_EX* pMesh = pFirstMesh;

	//While there is a mesh try to draw it
	while(pMesh)
	{
		//Select the mesh to draw
		ID3DXMesh* pDrawMesh = (pMesh->pSkinInfo)
			? pMesh->pSkinMesh: pMesh->MeshData.pMesh;
		
		//Draw each mesh subset with correct materials and texture
		for (DWORD i = 0; i < pMesh->NumMaterials; ++i)
		{
			pD3DXDevice->SetMaterial(&pMesh->pMaterials[i]);
			pD3DXDevice->SetTexture(0, pMesh->ppTexture[i]);
			pDrawMesh->DrawSubset(i);
		}

		//Go to the next one
		pMesh = (D3DXMESHCONTAINER_EX*)pMesh->pNextMeshContainer;
	}
}

void XModel::DrawFrame(D3DXFRAME_EX* pFrame)
{
	D3DXMESHCONTAINER_EX* pMesh = (D3DXMESHCONTAINER_EX*)pFrame->pMeshContainer;

	//While there is a mesh try to draw it
	while(pMesh)
	{
		//Select the mesh to draw
		LPD3DXMESH pDrawMesh = (pMesh->pSkinInfo)
			? pMesh->pSkinMesh: pMesh->MeshData.pMesh;
		
		//Draw each mesh subset with correct materials and texture
		for (DWORD i = 0; i < pMesh->NumMaterials; ++i)
		{
			pD3DXDevice->SetMaterial(&pMesh->pMaterials[i]);
			pD3DXDevice->SetTexture(0, pMesh->ppTexture[i]);
			pDrawMesh->DrawSubset(i);
		}

		//Go to the next one
		pMesh = (D3DXMESHCONTAINER_EX*)pMesh->pNextMeshContainer;
	}

	//Check your sibling
	if(pFrame->pFrameSibling)
		DrawFrame((D3DXFRAME_EX*)pFrame->pFrameSibling);

	//Check your first child
	if(pFrame->pFrameFirstChild)
		DrawFrame((D3DXFRAME_EX*)pFrame->pFrameFirstChild);
}

//Update functions

void XModel::UpdateFrameMatrices(D3DXFRAME_EX* pFrame, D3DXMATRIX* pParentMatrix)
{	
	//Parent check
	if (pParentMatrix)
	{
		D3DXMatrixMultiply(&pFrame->matCombined, 
							&pFrame->TransformationMatrix, 
							pParentMatrix);
	}
	else
		pFrame->matCombined = pFrame->TransformationMatrix;

	//Sibling check
	if (pFrame->pFrameSibling)
	{
		UpdateFrameMatrices((D3DXFRAME_EX*)pFrame->pFrameSibling, pParentMatrix);
	}

	//make sure you get the first child
	if (pFrame->pFrameFirstChild)
	{
		UpdateFrameMatrices((D3DXFRAME_EX*)pFrame->pFrameFirstChild, 
				&pFrame->matCombined);
	}
}

void XModel::Update(double dElapsedTime)
{
	//Set the time for animation
	if(pAnimController && dwCurrentAnimation != -1)
		pAnimController->AdvanceTime(dElapsedTime, 0);

	//Update the frame hierarchy
	if(pFrameRoot)
	{
		UpdateFrameMatrices((D3DXFRAME_EX*)pFrameRoot, NULL);
		
		D3DXMESHCONTAINER_EX* pMesh = pFirstMesh;
		if(pMesh)
		{
			if(pMesh->pSkinInfo)
			{
				UINT Bones = pMesh->pSkinInfo->GetNumBones();
				for (UINT i = 0; i < Bones; ++i)
				{	
					D3DXMatrixMultiply
					(
						&pBoneMatrices[i],
						&pMesh->pBoneOffsets[i], 
						pMesh->ppFrameMatrices[i]
					);
				}

				// Lock the meshes' vertex buffers
				void *SrcPtr, *DestPtr;
				pMesh->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&SrcPtr);
				pMesh->pSkinMesh->LockVertexBuffer(0, (void**)&DestPtr);

				// Update the skinned mesh using provided transformations
				pMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMatrices, NULL, SrcPtr, DestPtr);

				// Unlock the meshes vertex buffers
				pMesh->pSkinMesh->UnlockVertexBuffer();
				pMesh->MeshData.pMesh->UnlockVertexBuffer();
			}
		}
	}
}