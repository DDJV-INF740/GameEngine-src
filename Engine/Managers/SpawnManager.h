#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/ISpawnManager.h"
#include "Core/Game/IManagerComponent.h"
#include "Engine/Game/GameComponent.h"

namespace engine {

//=============================================================================
// CLASS SpawnManager
//=============================================================================
class SpawnManager
	: public GameComponent<SpawnManager>
	, public ISpawnManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			ISpawnManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public:
	virtual void update() override;
	virtual void unspawn(const GameObjectRef &aGameObjectToUnspawn);
	virtual void unspawnAll() override;
	virtual GameObjectRef spawn(const IGameObject::IdType &aGameObjectId, const physx::PxTransform &aPose) override;
	virtual const std::set<GameObjectRef>& gameObjects() override;

	template<class T>
	T* spawn(const physx::PxTransform &aInitialPose)
	{	return dynamic_cast<T*>(spawn(T::typeId(), aInitialPose)); }

public:
	SpawnManager();
	~SpawnManager();

private:
	class SpawnManagerImp;
	SpawnManagerImp *_imp;
};



} // namespace engine
