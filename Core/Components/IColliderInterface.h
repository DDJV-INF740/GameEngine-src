#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/physx/PxPhysicsAPI.forward.h"
#include "Core/Components/ICollisionHandler.h"
#include "Core/Components/IComponentInterface.h"
#include "Core/Components/IdType.h"

namespace engine
{

//=============================================================================
// INTERFACE IColliderInterface
//=============================================================================
class IColliderInterface: virtual public IComponentInterface
{
public:
	static constexpr IdType TypeId = "IColliderInterface";

public:
	virtual void onContact(const physx::PxContactPair &aContactPair) = 0;
	virtual void onTrigger(bool triggerEnter, physx::PxShape *actorShape, physx::PxShape *contactShape) = 0;
	virtual void setHandler(ICollisionHandlerRef ICollisionHandler) = 0;
};

} // namespace engine
