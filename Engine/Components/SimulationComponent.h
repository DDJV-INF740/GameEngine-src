#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/ISimulationInterface.h"
#include "Core/Components/IDynamicSimulationInterface.h"
#include "Core/Components/IStaticSimulationComponent.h"
#include "Core/Components/ICollisionHandler.h"
#include "Core/Components/IColliderInterface.h"
#include "Engine/GameObjects/GameObjectComponent.h"
#include "Core/GameObjects/IGameObject.h"

#include <memory>

#pragma warning( disable : 4250 )

//=============================================================================
// CLASS SimulationComponentBase
//=============================================================================
template<class TDerived>
class SimulationComponentBase : 
	public GameObjectComponent<TDerived>,
 	public IRigidSimulationInterface,
 	public IColliderInterface,
 	public IPoseInterface,
	virtual public IComponentInterface
{
public:
	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;
	virtual void onContact(const physx::PxContactPair &aContactPair) override;
	virtual void onTrigger(bool triggerEnter, physx::PxShape *actorShape, physx::PxShape *contactShape) override;
	virtual void setHandler(ICollisionHandlerRef iHandler) override;

protected:
	GameObjectWeakRef _go;
	physx::PxActor* _pxActor;
	ICollisionHandlerRef _collisionHandler;
};

//=============================================================================
// CLASS DynamicSimulationComponent
//=============================================================================
class DynamicSimulationComponent : 
	public SimulationComponentBase<DynamicSimulationComponent>, 
	public IDynamicSimulationInterface
{
private:
	typedef SimulationComponentBase base;

public:
	static IComponent::IdType TypeId();

	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IPoseInterface::TypeId(),
			IColliderInterface::TypeId(),
			ISimulationInterface::TypeId(),
			IRigidSimulationInterface::TypeId(),
			IDynamicSimulationInterface::TypeId(),
			0
		};

		return sInterfaces;
	}

public:
	static physx::PxRigidDynamic* createPxActor();

	virtual physx::PxTransform pose() override;
	virtual void setPose(const physx::PxTransform &iPose) override;

public:
	virtual physx::PxRigidDynamic& pxActor() override;
};

//=============================================================================
// CLASS StaticSimulationComponent
//=============================================================================
class StaticSimulationComponent : 
	public SimulationComponentBase<StaticSimulationComponent>,
	public IStaticSimulationInterface
{
private:
	typedef SimulationComponentBase base;

public:
	static IComponent::IdType TypeId();

	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IPoseInterface::TypeId(),
			IColliderInterface::TypeId(),
			ISimulationInterface::TypeId(), 
			IRigidSimulationInterface::TypeId(),
			IStaticSimulationInterface::TypeId(),
			0
		};

		return sInterfaces;
	}

public:
	static physx::PxRigidStatic* createPxActor();

public: // IStaticSimulationInterface
	virtual physx::PxRigidStatic& pxActor() override;

public: // IPoseInterface
	virtual physx::PxTransform pose() override;
	virtual void setPose(const physx::PxTransform &iPose) override;
};

#include "SimulationComponent.inline.h"
