#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"
#include "Core/Components/IdType.h"

namespace engine
{

//=============================================================================
// INTERFACE IAIInterface
//=============================================================================
class IAIInterface: virtual public IComponentInterface
{
public:
	static constexpr IdType TypeId = "IAIInterface";
	virtual void updateAI() = 0;
};
} // namespace engine
