#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/physx/PxPhysicsAPI.forward.h"
#include <memory>

namespace engine {

//=============================================================================
// FORWARD DEFINITIONS
//=============================================================================
class MeshModel;

class ModelFactory
{
public:
	static std::unique_ptr<MeshModel> createSphere(float iRadius);
	static physx::unique_ptr<physx::PxConvexMesh> convexMeshFromModel(const MeshModel &iMeshModel);
};
} // namespace engine