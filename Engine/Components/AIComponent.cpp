#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "AIComponent.h"
#include "ComponentFactory.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IAIManager.h"

namespace engine
{ 

//=============================================================================
// CLASS AIComponent
//=============================================================================

//-----------------------------------------------------------------------------
//
void AIComponent::setBehaviour(const IBehaviourRef &iBehaviour)
{
	_behaviour = iBehaviour;
}

//-----------------------------------------------------------------------------
//
void AIComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
	Game<IAIManager>()->createComponent(this);
}

//-----------------------------------------------------------------------------
//
void AIComponent::updateAI()
{
	_behaviour->update(_go.lock());
}

//-----------------------------------------------------------------------------
//
void AIComponent::onDetached( const GameObjectRef &iGameObject )
{
	Game<IAIManager>()->removeComponent(this);
}

} // namespace engine