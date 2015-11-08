#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentObject.h"
#include "Core/Components/IComponent.h"
#include "Core/PhysX/PxPhysicsAPI.forward.h"
#include <memory>

namespace engine
{
//=============================================================================
// INTERFACE IGameObject
//=============================================================================
typedef std::shared_ptr<IGameObject> GameObjectRef;
typedef std::weak_ptr<IGameObject> GameObjectWeakRef;

class IGameObject: virtual public IComponentObject<IComponent, IComponentInterface>
{
public:
	typedef const char * IdType;

public:
	virtual ~IGameObject() {}

	virtual void onSpawn(const physx::PxTransform &aPose) = 0;
	virtual void onUnspawn() = 0;
	virtual IdType typeId() const = 0;

	virtual GameObjectRef ref() = 0;
	virtual void setRef(const GameObjectRef &aRef) = 0;

	virtual const char *debugName() const = 0;
};

} // namespace engine
