#include "Precompiled.h"
#include "SpawnTask.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameSpawner.h"

void SpawnTask::update()
{
	Game<IGameSpawner>()->update();
}
