#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/Components/IdType.h"

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
	static constexpr IdType TypeId = "IGameLoopManager";

public:
	virtual bool exitRequested() = 0;
	virtual void requestExit(bool iRequest) = 0;
};
} // namespace engine
