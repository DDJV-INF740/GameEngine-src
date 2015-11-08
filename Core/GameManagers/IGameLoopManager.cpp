#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IGameLoopManager.h"

namespace engine
{

//=============================================================================
// INTERFACE IRenderManager
//=============================================================================
IGameLoopManager::IdType IGameLoopManager::TypeId() { return "IGameLoopManager"; }

} // namespace engine
