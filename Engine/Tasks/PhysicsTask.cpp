#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "PhysicsTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameSimulation.h"

//-----------------------------------------------------------------------------
//
void PhysicsTask::init()
{
}

//-----------------------------------------------------------------------------
//
void PhysicsTask::cleanup()
{
}

//-----------------------------------------------------------------------------
//
void PhysicsTask::update()
{
	Game<IGameSimulation>()->update();
}
