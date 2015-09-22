#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "Core/GameObjects/IBehaviour.h"

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
	static IdType TypeId();

public:
	virtual void updatePlayer() = 0;
	virtual GameObjectRef gameObject() = 0;
};
