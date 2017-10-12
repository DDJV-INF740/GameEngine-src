#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "Core/GameObjects/IBehaviour.h"

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameObject;

//=============================================================================
// INTERFACE IPlayerInterface
//=============================================================================
class IPlayerInterface: virtual public IComponentInterface
{
public:
	static constexpr IdType TypeId = "IPlayerInterface";

public:
	virtual void updatePlayer() = 0;
	virtual GameObjectRef gameObject() = 0;
};
} // namespace engine
