#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"

//=============================================================================
// INTERFACE IAIInterface
//=============================================================================
class IAIInterface: virtual public IComponentInterface
{
public:
	static IdType TypeId();
	virtual void updateAI() = 0;
};
