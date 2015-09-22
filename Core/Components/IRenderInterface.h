#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IComponentInterface.h"

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
	static IdType TypeId();

public:
	virtual void render() = 0;
};

