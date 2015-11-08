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
// INTERFACE IStaticSimulationInterface
//=============================================================================
class IStaticSimulationInterface : public IRigidSimulationInterface
{
public:
	static IdType TypeId();

public:
	virtual physx::PxRigidStatic& pxActor() = 0;
};
}  // namespace engine
