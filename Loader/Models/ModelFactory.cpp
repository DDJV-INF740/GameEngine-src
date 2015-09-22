#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ModelFactory.h"
#include <PxPhysicsAPI.h>
#include <d3d9.h>
#include <d3dx9mesh.h>
#include "GameCore/Game/Game.h"
#include "GameCore/GameManagers/IGameRendering.h"
#include "GameCore/GameManagers/IGameSimulation.h"
#include <vector>
#include "GameAssets/Models/MeshModel.h"

using namespace physx;

//=============================================================================
// class MemoryStream
//=============================================================================
class MemoryStream: public PxOutputStream, public PxInputStream
{
public:
	virtual PxU32 write(const void* src, PxU32 count)
	{
		int oldSize = _data.size();
		_data.resize(_data.size() + count);
		memcpy(&_data[oldSize], src, count);
		return count;
	}

	virtual PxU32 read(void* dest, PxU32 count)
	{
		if (count > _data.size())
			count = _data.size();
		memcpy(dest, &_data[0], count);
		_data.erase(_data.begin(), _data.begin()+count);
		return count;
	}

public:
	std::vector<unsigned char> _data;
};


//=============================================================================
// PRIVATE FUNCTIONS
//=============================================================================
static PxConvexMesh* GenerateConvexFromDXMesh(PxPhysics &physics, ID3DXMesh *mesh)
{
	//Used to retrieve information from X file
	typedef struct {
		D3DXVECTOR3 VertexPos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TexCoord;
	} Mesh_FVF;

	int NumVerticies = mesh->GetNumVertices();
	DWORD FVFSize = D3DXGetFVFVertexSize(mesh->GetFVF());

	//Create pointer for vertices
	PxVec3* verts = new PxVec3[NumVerticies];

	char *DXMeshPtr;
	mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&DXMeshPtr);
	for(int i = 0; i < NumVerticies; i++)
	{
		Mesh_FVF *DXMeshFVF = (Mesh_FVF*)DXMeshPtr;
		verts[i] = PxVec3(DXMeshFVF->VertexPos.x, DXMeshFVF->VertexPos.y, DXMeshFVF->VertexPos.z);
		DXMeshPtr += FVFSize;
	}
	mesh->UnlockVertexBuffer();

	// Create descriptor for convex mesh
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count		= NumVerticies;
	convexDesc.points.stride	= sizeof(PxVec3);
	convexDesc.points.data		= verts;
	convexDesc.flags			= PxConvexFlag::eCOMPUTE_CONVEX;

	PxTolerancesScale toleranceScale;
	toleranceScale.length = 1.0f;
	toleranceScale.mass = 1000.0f;
	toleranceScale.speed = 9.8f;

	assert(toleranceScale.isValid());

	PxCooking *cooker = PxCreateCooking(PX_PHYSICS_VERSION, physics.getFoundation(), PxCookingParams(toleranceScale));

	// Cooking from memory
	MemoryStream buf;
	PxConvexMesh *convexMesh = nullptr;
	if(cooker->cookConvexMesh(convexDesc, buf))
	{
		convexMesh = physics.createConvexMesh(buf);
	}	
	cooker->release();

	delete[] verts;

	return convexMesh;
}

//=============================================================================
// CLASS ModelFactory
//=============================================================================
MeshModel* ModelFactory::createSphere( float iRadius )
{
	LPDIRECT3DDEVICE9 d3dDevice = Game<IGameRendering>()->d3dDevice();
	LPD3DXMESH wD3DMesh = nullptr;;
	D3DXCreateSphere(d3dDevice, iRadius, 8, 8, &wD3DMesh, nullptr);
	return new MeshModel(wD3DMesh);
}

//-----------------------------------------------------------------------------
//
PxConvexMesh* ModelFactory::convexMeshFromModel(const MeshModel &iModel)
{
	return GenerateConvexFromDXMesh(Game<IGameSimulation>()->physics(), iModel.mesh());
}

