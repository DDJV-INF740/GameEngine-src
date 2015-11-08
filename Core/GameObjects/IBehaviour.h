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
class IBehaviour
{
public:
	virtual void update(const GameObjectRef &iGameObject) = 0;
};

//=============================================================================
// TYPE DEFINITIONS
//=============================================================================
typedef std::shared_ptr<IBehaviour> IBehaviourRef;
} // namespace engine
