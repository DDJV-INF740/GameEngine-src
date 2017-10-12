#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "PlayerManager.h"
#include "Core/GameObjects/GameObjectProxy.h"
#include <algorithm>
#include <assert.h>

namespace engine {

//=============================================================================
// CLASS PlayerManager
//=============================================================================


void PlayerManager::removePlayer( IPlayerInterface *aPlayer )
{
	auto wFound = std::find(_player.begin(), _player.end(), aPlayer);
	ASSERT(wFound != _player.end());
	if (wFound != _player.end())
	{
		_player.erase(wFound);
		if (_player.empty())
		{
			_mainGameObjectProxy->setProxy(nullptr);
		}
	}
}

void PlayerManager::addPlayer( IPlayerInterface *aPlayer )
{
	_player.emplace_back(aPlayer);

	if (_player.size() == 1)
	{
		_mainGameObjectProxy->setProxy(aPlayer->gameObject());
	}
}

void PlayerManager::update()
{
	for (int i = 0; i < playerCount(); ++i)
	{
		_player[i]->updatePlayer();
	}
}

IPlayerInterface* PlayerManager::mainController()
{
	return player(0);
}

GameObjectProxyRef PlayerManager::mainGameObject()
{
	return _mainGameObjectProxy;
}

IPlayerInterface* PlayerManager::player( int index )
{
	return _player[index];
}

int PlayerManager::playerCount()
{
	return (int)_player.size();
}

PlayerManager::PlayerManager()
	: _player()
	, _mainGameObjectProxy(new GameObjectProxy)
{}
} // namespace engine

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Managers/GameManagerFactory.h"

