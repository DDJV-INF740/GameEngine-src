#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"

namespace engine
{

//=============================================================================
// INTERFACE IAIInterface
//=============================================================================
class IAIInterface: virtual public IComponentInterface
{
public:
	static IdType TypeId();
	virtual void updateAI() = 0;
};
} // namespace engine
