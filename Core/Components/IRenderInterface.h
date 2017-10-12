#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"
#include "Core/Components/IdType.h"

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IRenderViewInterface;

//=============================================================================
// INTERFACE IRenderInterface 
//=============================================================================
class IRenderInterface : virtual public IComponentInterface
{
public:
	static constexpr IdType TypeId = "IRenderInterface";

public:
	virtual void render() = 0;
};

} // namespace engine
