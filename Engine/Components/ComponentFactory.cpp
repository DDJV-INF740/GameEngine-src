//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "ComponentFactory.h"
#include <map>

//=============================================================================
// CLASS ComponentFactory
//=============================================================================
ComponentFactory& ComponentFactory::Instance()
{
	static ComponentFactory sInstance;
	return sInstance;
}


