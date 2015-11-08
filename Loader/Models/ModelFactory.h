#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/physx/PxPhysicsAPI.forward.h"

namespace engine {

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
} // namespace engine