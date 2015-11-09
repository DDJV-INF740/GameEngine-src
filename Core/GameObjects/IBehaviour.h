#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObject.h"
#include <memory>

namespace engine
{
//=============================================================================
// INTERFACE IBehaviour
//=============================================================================
// A Behaviour is a callback which acts on a GameObject. It can use used
// to customize the inner workings of a component. For instance, the AIComponent
// or the PlayerComponent may be configured with custom behaviours that can be
// changed at runtime - making some AI smarter or faster at specific moments.
class IBehaviour
{
public:
	virtual void update(const GameObjectRef &iGameObject) = 0;
};

//=============================================================================
// TYPE DEFINITIONS
//=============================================================================
using IBehaviourRef = std::shared_ptr<IBehaviour>;

} // namespace engine
