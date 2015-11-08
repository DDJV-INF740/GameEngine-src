#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "PlayerComponent.h"
#include "Core/GameManagers/IPlayerManager.h"
#include "Core/Game/Game.h"
#include "Engine/Components/ComponentFactory.h"

#include <algorithm>
#include <assert.h>

namespace engine {

//=============================================================================
// CLASS PlayerComponent
//=============================================================================

//-----------------------------------------------------------------------------
//
void PlayerComponent::onDetached( const GameObjectRef &iGameObject )
{
	Game<IPlayerManager>()->removePlayer(this);
	_go.reset();
}

//-----------------------------------------------------------------------------
//
void PlayerComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
	Game<IPlayerManager>()->addPlayer(this);
}

//-----------------------------------------------------------------------------
//
GameObjectRef PlayerComponent::gameObject()
{
	return _go.lock();
}

//-----------------------------------------------------------------------------
//
void PlayerComponent::updatePlayer()
{
	_behaviour->update(_go.lock());
}

//-----------------------------------------------------------------------------
//
void PlayerComponent::setBehaviour( IBehaviourRef iBehaviour )
{
	_behaviour = iBehaviour;
}

} // namespace engine

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
namespace engine {
IComponent::IdType PlayerComponent::TypeId() { return "PlayerComponent"; }
RegisterComponentType<PlayerComponent> *gRegisterPlayerComponent = new RegisterComponentType<PlayerComponent>();
}