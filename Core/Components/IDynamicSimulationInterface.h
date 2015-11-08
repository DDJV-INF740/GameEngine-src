#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "IRigidSimulationInterface.h"
#include "PxPhysicsAPI.h"

namespace engine
{
//=============================================================================
// INTERFACE IDynamicSimulationInterface
//=============================================================================
class IDynamicSimulationInterface : virtual public IRigidSimulationInterface
{
public:
	static IdType TypeId();

public:
	virtual physx::PxRigidDynamic& pxActor() = 0;
};

} // namespace engine
