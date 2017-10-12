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
