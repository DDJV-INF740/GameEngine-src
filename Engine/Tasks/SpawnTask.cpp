#include "Precompiled.h"
#include "SpawnTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/ISpawnManager.h"

namespace engine {

void SpawnTask::update()
{
	Game<ISpawnManager>()->update();
}
} // namespace engine
