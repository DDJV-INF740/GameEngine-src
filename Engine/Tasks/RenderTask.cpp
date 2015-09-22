//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "RenderTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameRendering.h"
#include "Core/GameManagers/IGameCameras.h"
#include "Core/Components/IRenderViewInterface.h"

#include "Rendering/Camera.h"

//=============================================================================
// CLASS RenderTask
//=============================================================================

//-----------------------------------------------------------------------------
//
void RenderTask::update()
{
	Game<IGameCameras>()->render();
}

//-----------------------------------------------------------------------------
//
void RenderTask::init()
{}

//-----------------------------------------------------------------------------
//
void RenderTask::cleanup()
{}
