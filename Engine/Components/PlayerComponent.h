#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameObjects/IBehaviour.h"
#include "Core/Components/IPlayerInterface.h"
#include "Engine/GameObjects/GameObjectComponent.h"

namespace engine {

//=============================================================================
// CLASS PlayerComponent
//=============================================================================
class PlayerComponent
	: public GameObjectComponent<PlayerComponent>
	, public IPlayerInterface
{
public:
	static constexpr IdType TypeId = "PlayerComponent";
	static constexpr IdType Interfaces[] =  {
			IPlayerInterface::TypeId
	};


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
} // namespace engine
