#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/physx/PxPhysicsAPI.forward.h"
#include "PxPhysicsAPI.h"
#include <memory>

namespace engine
{

//=============================================================================
// INTERFACE IPoseInterface
//=============================================================================
class IPoseInterface: virtual public IComponentInterface
{
public:
	static IdType TypeId();

public:
	virtual physx::PxTransform pose() = 0;
	virtual void setPose(const physx::PxTransform &iPose) = 0;
};

//=============================================================================
// TYPE DEFINITIONS
//=============================================================================
using IPoseInterfaceRef = std::shared_ptr<IPoseInterface>;
using IPoseInterfaceWeakRef = std::weak_ptr<IPoseInterface>;


} // namespace engine
