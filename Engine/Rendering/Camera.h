#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObject.h"

//=============================================================================
// CLASS ICamera
//=============================================================================
class ICamera: virtual public IGameObject
{
public:
	static IGameObject::IdType TypeId();
};

