#include "Precompiled.h"
#include "TimeTask.h"
#include "Core/GameManagers/ITimeManager.h"
#include "Core/Game/Game.h"

namespace engine {

void TimeTask::update()
{
	Game<ITimeManager>()->startFrame();
}
} // namespace engine
