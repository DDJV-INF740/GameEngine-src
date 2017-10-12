#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <vector>
#include "Engine/Components/PlayerComponent.h"
#include "Engine/Game/GameManager.h"
#include "Core/GameManagers/IPlayerManager.h"

namespace engine {

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;
class Controller;

class GameObjectProxy;
using GameObjectProxyRef = std::shared_ptr<GameObjectProxy>;
using GameObjectProxyWeakRef = std::weak_ptr<GameObjectProxy>;

class IGameEngine;
using GameEngineRef = std::shared_ptr<IGameEngine>;
using GameEngineWeakRef = std::weak_ptr<IGameEngine>;

//=============================================================================
// CLASS PlayerManager
//=============================================================================
class PlayerManager
	: public GameManager<PlayerManager>
	, public IPlayerManager
{
public:
	static constexpr IdType TypeId = "PlayerManager";
	static constexpr IdType Interfaces[] = {
		IPlayerManager::TypeId,
	};

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
