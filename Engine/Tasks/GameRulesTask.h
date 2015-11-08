#pragma once

#include "Core/Tasks/IGameTask.h"

namespace engine {

//=============================================================================
// CLASS GameRulesTask
//=============================================================================
class GameRulesTask: public IGameTask
{
public:
	virtual void init()
	{}

	virtual void cleanup()
	{}

	virtual void update()
	{}
};
} // namespace engine
