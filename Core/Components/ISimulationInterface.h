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
class ISimulationInterface : virtual public IComponentInterface, virtual public IPoseInterface
{
public:
	static constexpr IdType TypeId = "ISimulationInterface";

public:
	virtual physx::PxActor& pxActor() = 0;
	virtual void setPxActor(physx::PxActor *iPxActor) = 0;
};
} // namespace engine
