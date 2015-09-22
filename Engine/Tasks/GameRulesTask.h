#pragma once

#include "Core/Tasks/IGameTask.h"

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