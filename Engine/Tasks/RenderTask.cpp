//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "RenderTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IRenderManager.h"
#include "Core/GameManagers/ICameraManager.h"
#include "Core/Components/IRenderViewInterface.h"

#include "Rendering/Camera.h"

//=============================================================================
// CLASS RenderTask
//=============================================================================

//-----------------------------------------------------------------------------
//
void RenderTask::update()
{
	Game<ICameraManager>()->render();
}

//-----------------------------------------------------------------------------
//
void RenderTask::init()
{}

//-----------------------------------------------------------------------------
//
void RenderTask::cleanup()
{}
