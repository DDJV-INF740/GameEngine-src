#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Tasks/IGameTask.h"

namespace engine {

//=============================================================================
// CLASS RenderTask
//=============================================================================
class SpawnTask: public IGameTask
{
public:
	virtual void init() override {}
	virtual void cleanup() override {}
	virtual void update() override;
};
} // namespace engine