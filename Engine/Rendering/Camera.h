#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObject.h"

namespace engine {

//=============================================================================
// CLASS ICamera
//=============================================================================
class ICamera: virtual public IGameObject
{
public:
	static IGameObject::IdType TypeId();
};
} // namespace engine

