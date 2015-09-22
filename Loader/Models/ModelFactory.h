#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "GameCore/physx/PxPhysicsAPI.forward.h"

//=============================================================================
// FORWARD DEFINITIONS
//=============================================================================
class MeshModel;

class ModelFactory
{
public:
	static MeshModel* createSphere(float iRadius);
	static physx::PxConvexMesh* convexMeshFromModel(const MeshModel &iMeshModel);
};