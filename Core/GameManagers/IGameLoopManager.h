#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================

//=============================================================================
// INTERFACE IRenderManager
//=============================================================================
class IGameLoopManager: virtual public IManager
{
public:
	static IdType TypeId();

public:
	virtual bool exitRequested() = 0;
	virtual void requestExit(bool iRequest) = 0;
};
} // namespace engine
