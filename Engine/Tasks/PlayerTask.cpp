#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "PlayerTask.h"
#include "Managers/PlayerManager.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGamePlayers.h"
//=============================================================================
// CLASS PlayerTask
//=============================================================================
void PlayerTask::init()
{}

//-----------------------------------------------------------------------------
//
void PlayerTask::cleanup()
{}

//-----------------------------------------------------------------------------
//
void PlayerTask::update()
{
	Game<IGamePlayers>()->update();
}
