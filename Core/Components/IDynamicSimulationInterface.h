#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "IRigidSimulationInterface.h"
#include "PxPhysicsAPI.h"

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
