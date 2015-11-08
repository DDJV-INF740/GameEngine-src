#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameEngine.h"

namespace engine
{ 

//=============================================================================
// GLOBAL Game<>()
//=============================================================================
template<class T>
std::shared_ptr<T> Game()
{
	return IGameEngine::Instance()->as<T>();
}
} // namespace engine
