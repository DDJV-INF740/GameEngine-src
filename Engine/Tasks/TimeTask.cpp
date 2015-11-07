#include "Precompiled.h"
#include "TimeTask.h"
#include "Core/GameManagers/ITimeManager.h"
#include "Core/Game/Game.h"

void TimeTask::update()
{
	Game<ITimeManager>()->startFrame();
}
