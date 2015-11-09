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
// Game<> provides a convenient access to the IGameEngine managers. The
// registered managers can be obtained using Game<...>() - for example, the
// IRenderManager can be accessed using Game<IRenderManager>().
template<class T>
std::shared_ptr<T> Game()
{
	return IGameEngine::Instance()->as<T>();
}

} // namespace engine
