#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/physx/PxPhysicsAPI.forward.h"
#include "PxPhysicsAPI.h"
#include <memory>

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
typedef std::shared_ptr<IPoseInterface> IPoseInterfaceRef;
typedef std::weak_ptr<IPoseInterface> IPoseInterfaceWeakRef;


