#include "Precompiled.h"
#include "SpawnTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/ISpawnManager.h"

void SpawnTask::update()
{
	Game<ISpawnManager>()->update();
}
