#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ModelFactory.h"
#include <PxPhysicsAPI.h>
#include <d3d9.h>
#include <d3dx9mesh.h>
#include "Core/Game/Game.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/GameManagers/ISimulationManager.h"
#include <vector>
#include "Assets/Models/MeshModel.h"
#include "Core/physx/PxPhysicsAPI.forward.h"

using namespace physx;

namespace engine {

//=============================================================================
// class MemoryStream
//=============================================================================
class MemoryStream: public PxOutputStream, public PxInputStream
{
public:
	virtual PxU32 write(const void* src, PxU32 count) override
	{
		size_t oldSize = _data.size();
		_data.resize(_data.size() + count);
		memcpy(&_data[oldSize], src, count);
		return count;
	}

	virtual PxU32 read(void* dest, PxU32 count) override
	{
		if (count > (PxU32)_data.size())
			count = (PxU32)_data.size();
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
static physx::unique_ptr<PxConvexMesh> GenerateConvexFromDXMesh(PxPhysics &iPhysics, ID3DXMesh *iMesh)
{
	//Used to retrieve information from X file
	struct Mesh_FVF {
		D3DXVECTOR3 VertexPos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TexCoord;
	};

	int aNumVerticies = iMesh->GetNumVertices();
	DWORD FVFSize = D3DXGetFVFVertexSize(iMesh->GetFVF());

	//Create pointer for vertices
	PxVec3* verts = new PxVec3[aNumVerticies];

	char *DXMeshPtr;
	iMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&DXMeshPtr);
	for(int i = 0; i < aNumVerticies; i++)
	{
		Mesh_FVF *DXMeshFVF = (Mesh_FVF*)DXMeshPtr;
		verts[i] = PxVec3(DXMeshFVF->VertexPos.x, DXMeshFVF->VertexPos.y, DXMeshFVF->VertexPos.z);
		DXMeshPtr += FVFSize;
	}
	iMesh->UnlockVertexBuffer();

	// Create descriptor for convex mesh
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count		= aNumVerticies;
	convexDesc.points.stride	= sizeof(PxVec3);
	convexDesc.points.data		= verts;
	convexDesc.flags			= PxConvexFlag::eCOMPUTE_CONVEX;

	PxTolerancesScale toleranceScale;
	toleranceScale.length = 1.0f;
	toleranceScale.mass = 1000.0f;
	toleranceScale.speed = 9.8f;

	assert(toleranceScale.isValid());

	physx::unique_ptr<PxCooking> cooker = physx::unique_ptr<PxCooking>(
		PxCreateCooking(PX_PHYSICS_VERSION, iPhysics.getFoundation(), PxCookingParams(toleranceScale))
		);

	// Cooking from memory
	MemoryStream buf;
	physx::unique_ptr<PxConvexMesh> convexMesh;
	if(cooker->cookConvexMesh(convexDesc, buf))
	{
		convexMesh = physx::unique_ptr<PxConvexMesh>(iPhysics.createConvexMesh(buf));
	}	

	delete[] verts;

	return convexMesh;
}

//=============================================================================
// CLASS ModelFactory
//=============================================================================
std::unique_ptr<MeshModel> ModelFactory::createSphere( float iRadius )
{
	LPDIRECT3DDEVICE9 d3dDevice = Game<IRenderManager>()->d3dDevice();
	LPD3DXMESH wD3DMesh = nullptr;;
	D3DXCreateSphere(d3dDevice, iRadius, 8, 8, &wD3DMesh, nullptr);
	return std::make_unique<MeshModel>(wD3DMesh);
}

//-----------------------------------------------------------------------------
//
physx::unique_ptr<PxConvexMesh> ModelFactory::convexMeshFromModel(const MeshModel &iModel)
{
	return GenerateConvexFromDXMesh(Game<ISimulationManager>()->physics(), iModel.mesh());
}

} // namespace engine
