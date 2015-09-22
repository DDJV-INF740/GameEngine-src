#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Tasks/IGameTask.h"

//=============================================================================
// CLASS InputTask
//=============================================================================
class InputTask: public IGameTask
{
public:
	virtual void init() override;
	virtual void cleanup() override;
	virtual void update() override;
};