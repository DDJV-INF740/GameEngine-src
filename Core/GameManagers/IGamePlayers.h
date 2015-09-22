#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"
#include <memory>

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IPlayerInterface;
class GameObjectProxy;
typedef std::shared_ptr<GameObjectProxy> GameObjectProxyRef;
typedef std::weak_ptr<GameObjectProxy> GameObjectProxyWeakRef;

//=============================================================================
// CLASS IGamePlayers
//=============================================================================
class IGamePlayers: virtual public IGameInterface
{
public:
	static IdType TypeId();

public:
	virtual int playerCount() = 0;
	virtual IPlayerInterface* player(int index) = 0;
	virtual IPlayerInterface* mainController() = 0;
	virtual GameObjectProxyRef mainGameObject() = 0;
	virtual void addPlayer(IPlayerInterface *aPlayer) = 0;
	virtual void removePlayer(IPlayerInterface *aPlayer) = 0;
	virtual void update() = 0;
};