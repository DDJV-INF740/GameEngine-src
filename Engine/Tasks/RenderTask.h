#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Tasks/IGameTask.h"

//=============================================================================
// CLASS RenderTask
//=============================================================================
class RenderTask: public IGameTask
{
public:
	virtual void init() override;
	virtual void cleanup() override;
	virtual void update() override;

private:
	class RenderTaskImp;
	RenderTaskImp *_imp;
};