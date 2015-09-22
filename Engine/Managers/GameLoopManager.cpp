#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "GameLoopManager.h"


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

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Managers/GameManagerFactory.h"
IComponent::IdType GameLoopManager::TypeId() { return "GameLoopManager"; }
static RegisterGameManagerType<GameLoopManager> gRegisteredComponent;
