#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Tasks/IGameTask.h"

//=============================================================================
// CLASS PhysicsTask
//=============================================================================
class PhysicsTask: public IGameTask
{
public:
	virtual void init() override;
	virtual void cleanup() override;
	virtual void update() override;
};