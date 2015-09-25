#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IAIInterface;

//=============================================================================
// INTERFACE IGameRendering
//=============================================================================
class IGameAI: virtual public IGameInterface
{
public:
	static IdType TypeId();

public:
	virtual void addComponent(IAIInterface *iAIInstance) = 0;
	virtual void removeComponent(IAIInterface *iAIInstance) = 0;
	virtual void update() = 0;
};