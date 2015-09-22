#include "Precompiled.h"
#include "TimeTask.h"
#include "Core/GameManagers/IGameTime.h"
#include "Core/Game/Game.h"

void TimeTask::update()
{
	Game<IGameTime>()->startFrame();
}
