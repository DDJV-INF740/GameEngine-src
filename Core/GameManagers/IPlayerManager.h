#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/Components/IdType.h"
#include <memory>

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IPlayerInterface;
class GameObjectProxy;
using GameObjectProxyRef = std::shared_ptr<GameObjectProxy>;
using GameObjectProxyWeakRef = std::weak_ptr<GameObjectProxy>;

//=============================================================================
// CLASS IPlayerManager
//=============================================================================
class IPlayerManager: virtual public IManager
{
public:
	static constexpr IdType TypeId = "IPlayerManager";

public:
	virtual int playerCount() = 0;
	virtual IPlayerInterface* player(int index) = 0;
	virtual IPlayerInterface* mainController() = 0;
	virtual GameObjectProxyRef mainGameObject() = 0;
	virtual void addPlayer(IPlayerInterface *aPlayer) = 0;
	virtual void removePlayer(IPlayerInterface *aPlayer) = 0;
	virtual void update() = 0;
};
} // namespace engine
