#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <vector>
#include "Engine/Components/PlayerComponent.h"
#include "Engine/Game/GameComponent.h"
#include "Core/GameManagers/IPlayerManager.h"

namespace engine {

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;
class Controller;

class GameObjectProxy;
typedef std::shared_ptr<GameObjectProxy> GameObjectProxyRef;
typedef std::weak_ptr<GameObjectProxy> GameObjectProxyWeakRef;

class IGameEngine;
typedef std::shared_ptr<IGameEngine> GameEngineRef;
typedef std::weak_ptr<IGameEngine> GameEngineWeakRef;

//=============================================================================
// CLASS PlayerManager
//=============================================================================
class PlayerManager
	: public GameComponent<PlayerManager>
	, public IPlayerManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IPlayerManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IPlayerManager
	virtual int playerCount() override;
	virtual IPlayerInterface* player(int index) override;
	virtual IPlayerInterface* mainController() override;
	virtual GameObjectProxyRef mainGameObject() override;
	virtual void addPlayer(IPlayerInterface *aPlayer) override;
	virtual void removePlayer(IPlayerInterface *aPlayer) override;
	virtual void update() override;

public:
	PlayerManager();

private:
	std::vector<IPlayerInterface*> _player;
	GameObjectProxyRef _mainGameObjectProxy;

};
} // namespace engine
