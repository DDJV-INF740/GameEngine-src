#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IPoseInterface.h"
#include "Core/d3d/d3d9.forward.h"

namespace engine
{

//=============================================================================
// INTERFACE IRenderViewInterface
//=============================================================================
class IRenderViewInterface: virtual public IComponentInterface
{
public:
	static IdType TypeId();

public:
	virtual void renderView() = 0;
};
} // namespace engine
