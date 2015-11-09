#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/physx/PxPhysicsAPI.forward.h"
#include <memory>

namespace engine
{

//=============================================================================
// INTERFACE ICollisionHandler
//=============================================================================
class ICollisionHandler
{
public:
	virtual void onContact(const physx::PxContactPair &aContactPair) = 0;
	virtual void onTrigger(bool triggerEnter, physx::PxShape *actorShape, physx::PxShape *contactShape) = 0;
};

using ICollisionHandlerRef = std::shared_ptr<ICollisionHandler>;

} // namespace engine
