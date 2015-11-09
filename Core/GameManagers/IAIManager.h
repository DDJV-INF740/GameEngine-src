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
class IAIInterface;

//=============================================================================
// INTERFACE IRenderManager
//=============================================================================
class IAIManager: virtual public IManager
{
public:
	static IdType TypeId();

public:
	virtual void createComponent(IAIInterface *iAIInstance) = 0;
	virtual void removeComponent(IAIInterface *iAIInstance) = 0;
	virtual void update() = 0;
};
} // namespace engine
