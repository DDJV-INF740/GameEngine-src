#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Tasks/IGameTask.h"

//=============================================================================
// CLASS PlayerTask
//=============================================================================
class PlayerTask: public IGameTask
{
public:
	virtual void init() override;
	virtual void cleanup() override;
	virtual void update() override;
};