#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "AIComponent.h"
#include "ComponentFactory.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameAI.h"

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
	Game<IGameAI>()->addComponent(this);
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
	Game<IGameAI>()->removeComponent(this);
}

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
IComponent::IdType AIComponent::TypeId() { return "AIComponent"; }
RegisterComponentType<AIComponent> *gRegisterAIComponent = new RegisterComponentType<AIComponent>();

