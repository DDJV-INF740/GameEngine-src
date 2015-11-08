#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "PlayerTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IPlayerManager.h"

namespace engine {

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
	Game<IPlayerManager>()->update();
}

} // namespace engine
