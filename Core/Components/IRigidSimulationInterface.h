#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "IPoseInterface.h"
#include "Core/physx/PxPhysicsAPI.forward.h"

namespace engine
{

//=============================================================================
// INTERFACE ISimulationInterface
//=============================================================================
class IRigidSimulationInterface : virtual public IComponentInterface
{
public:
	static IdType TypeId();

public:
	virtual physx::PxRigidActor& pxActor() = 0;
};
} // namespace engine
