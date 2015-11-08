#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "GameLoopManager.h"

namespace engine {

//=============================================================================
// CLASS GameLoopManager
//=============================================================================

//-----------------------------------------------------------------------------
//
bool GameLoopManager::exitRequested()
{
	return _exitRequested;
}

//-----------------------------------------------------------------------------
//
void GameLoopManager::requestExit( bool iRequest )
{
	_exitRequested = iRequest;
}
} // namespace engine

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Managers/GameManagerFactory.h"
namespace engine {

IComponent::IdType GameLoopManager::TypeId() { return "GameLoopManager"; }
static RegisterGameManagerType<GameLoopManager> gRegisteredComponent;
} // namespace engine
