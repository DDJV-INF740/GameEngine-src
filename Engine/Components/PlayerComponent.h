#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameObjects/IBehaviour.h"
#include "Core/Components/IPlayerInterface.h"
#include "Engine/GameObjects/GameObjectComponent.h"

//=============================================================================
// CLASS PlayerComponent
//=============================================================================
class PlayerComponent
	: public GameObjectComponent<PlayerComponent>
	, public IPlayerInterface
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IPlayerInterface::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;

public: // IPlayerInterface
	virtual GameObjectRef gameObject() override;
	virtual void updatePlayer() override;

public:
	virtual void setBehaviour(IBehaviourRef iBehaviour);

private:
	GameObjectWeakRef _go;
	IBehaviourRef _behaviour;
};